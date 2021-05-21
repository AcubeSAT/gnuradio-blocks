"""
Python prototype for convolutional encoder/decoder of rate 1/2 as specified in CCSDS 131.0-B-3.
The generator polynomials of the encoder are g1(x) = x^6 + x^5 + x^4 + x^3 + 1    &   g2(x) = x^6 + x^4 + x^3 + x + 1

Punctured convolutional encoder/decoder is also implemented, but puncturing patterns array is initialized to 1, because
it is not going to be used for the AcubeSAT Project.
"""

import numpy as np

constraint_length = 7
q = 2
num_of_generator_polynomials = 2
puncturing_patterns = [(1, 1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1, 1)]

rate_e, rate_d = 1, 1

def convolutional_encode(word):
    """
    Implements a binary convolutional encoder and the puncturing of the encoded word.
    The encoder looks at 7 bits at a time and produces 2 parity bits, 
    by multiplying the message bits with each of the generator polynomials.

    The inversed generator polynomials are used for the encoding.
    """
    generator_polynomials =  [(1, 0, 0, 1, 1, 1, 1), (1, 1, 0, 1, 1, 0, 1)]
    encoded = []

    for k in range(1,  constraint_length):
        for generator_poly in generator_polynomials:
            encoded.append(np.mod(np.dot(generator_poly[constraint_length-k:], word[:k]), q)
        
    for i in range(0, len(word)-constraint_lengthh+1):
        for j, generator_poly in enumerate(generator_polynomials):
            if puncturing_patterns[j][i%constraint_length] == 1:
                encoded.append(np.mod(np.dot(generator_poly, word[i:i+constraint_length]), q))
    return encoded

def hamming_distance(w1, w2):
    """
    Calculates the Hamming Distance between two given codewords.
    """
    return sum([c1 != c2 for c1, c2 in zip(w1, w2)])

def convolutional_decode(word):
    """
    Implements a binary soft decision convolutional decoder based on the Viterbi algorithm. 
    In case of a punctured encoded codeword, depuncturing is implemented.
    The branch metric for each state on the Trellis diagram is calculated and the path metric for the next column is computed.
    The path with the minimum path metric is returned.
    """
    generator_polynomials = [(1, 1, 1, 1, 0, 0, 1),(1, 0, 1, 1, 0, 1, 1)]
    codeword = []
    j = 0

    for i in range((len(word)*rate_d)//rate_e):
        k = puncturing_patterns[i%b][(i//b)%constraint_length]
        if k == 0:
            codeword.append(0.5)
        else:
            codeword.append(word[j])
            j += 1

    path_metric = [float('inf') for i in range(2**(constraint_length-1))] 
    path_metric[0] = 0
    paths = ["" for _ in range(2**(constraint_length-1))] 
    
    for t in range(len(codeword)//b):
        branch_metric = [float('inf') for i in range(2**(constraint_lengthh-1))]
        transmitted_paths = ["" for _ in range(2**(constraint_length-1))]
        
        transmitted_symbol = codeword[b*t:b*(t+1)]

        for state in range(2**(constraint_length-1)):
            if path_metric[state] != float('inf'):
                bin_state = bin(state)[2:].zfill(constraint_length - 1)

                transmitted_one = list(map(int, list("1" + bin_state)))
                transmitted_zero = list(map(int, list("0" + bin_state)))

                path_metric_one = 0
                path_metric_zero = 0

                for i_gen, gen in enumerate(generator_polynomials):
                    parity_bit_one = np.mod(np.dot(gen, transmitted_one), q)
                    path_metric_one += abs(parity_bit_one - transmitted_symbol[i_gen])

                    parity_bit_zero = np.mod(np.dot(gen, transmitted_zero), q) 
                    path_metric_zero += abs(parity_bit_zero - transmitted_symbol[i_gen])
                        
                tobranch_metric_one = path_metric_one**2 + path_metric[state]                
                next_state = int("".join( list("1" + bin_state)[:-1]), 2)

                if branch_metric[next_state] > tobranch_metric_one:
                    branch_metric[next_state] = tobranch_metric_one
                    transmitted_paths[next_state] = paths[state] + "1"

                tobranch_metric_zero = path_metric_zero**2 + path_metric[state]
                next_state = int("".join( list("0" + bin_state)[:-1]), 2)
                if branch_metric[next_state] > tobranch_metric_zero:
                    branch_metric[next_state] = tobranch_metric_zero
                    transmitted_paths[next_state] = paths[state] + "0"

        path_metric = list(branch_metric)
        paths = list(transmitted_paths)

    return min(zip(path_metric, paths))[1]

