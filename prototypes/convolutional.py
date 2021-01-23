"""
Python prototype for convolutional encoder/decoder
"""
N = 3
q = 2

import numpy as np

generator_polynomials =  [(1, 1, 1), (1, 1, 0)]
b = len(generator_polynomials)
puncturing_patterns = [(1, 1, 1), (1, 1, 1)]

rate_e, rate_d = 1, 1

def convolutional_encode(word):
    encoded = []

    for k in range(1,  N):
        for generator_poly in generator_polynomials:
            encoded.append(np.mod(np.dot(generator_poly[N-k:], word[:k]), q))
        
    for i in range(0, len(word)-N+1):
        for j, generator_poly in enumerate(generator_polynomials):
            if puncturing_patterns[j][i%N] == 1:
                encoded.append(np.mod(np.dot(generator_poly, word[i:i+N]), q))
    return encoded

def hamming_distance(w1, w2):
    return sum([c1 != c2 for c1, c2 in zip(w1, w2)])

# Convolutional decoder based on Viterbi algorithm
# Assumes binary code (can be modified fairly easily for arbitrary q)
def convolutional_decode(word):
    # "de-puncture" codeword
    codeword = ""
    j = 0
    for i in range((len(word)*rate_d)//rate_e):
        k = puncturing_patterns[i%b][(i//b)%N]
        if k == 0:
            codeword += "X"
        else:
            codeword += word[j]
            j += 1
    print(codeword)
    
    pm = [float('inf') for i in range(2**(N-1))] # path metric
    pm[0] = 0
    paths = ["" for _ in range(2**(N-1))] # max likelihood path for each state
    
    for t in range(len(codeword)//b):
        t_pm = [float('inf') for i in range(2**(N-1))]
        t_paths = ["" for _ in range(2**(N-1))]
        
        transmitted_symbol = codeword[b*t:b*(t+1)]

        for state in range(2**(N-1)):
            if pm[state] != float('inf'):
                bin_state = bin(state)[2:].zfill(N - 1)

                # 1 is transmitted
                tr_one = list(map(int, list("1" + bin_state)))
                # 0 is transmitted
                tr_zero = list(map(int, list("0" + bin_state)))

                pm_one = 0
                pm_zero = 0

                for i_gen, gen in enumerate(generator_polynomials):
                    # Calculate path metric
                    # It's probably far more efficient to hard-code the transition matrix for relatively low
                    # values of N
                    par = np.mod(np.dot(gen, tr_one), q)
                    if par != int(transmitted_symbol[i_gen]):
                        pm_one += 1
                    par = np.mod(np.dot(gen, tr_zero), q) 
                    if par != int(transmitted_symbol[i_gen]):
                        pm_zero += 1
                        
                # Update paths
                tot_pm_one = pm_one + pm[state]                
                next_state = int("".join( list("1" + bin_state)[:-1]), 2)

                if t_pm[next_state] > tot_pm_one:
                    t_pm[next_state] = tot_pm_one
                    t_paths[next_state] = paths[state] + "1"

                tot_pm_zero = pm_zero + pm[state]
                next_state = int("".join( list("0" + bin_state)[:-1]), 2)
                if t_pm[next_state] > tot_pm_zero:
                    t_pm[next_state] = tot_pm_zero
                    t_paths[next_state] = paths[state] + "0"
        pm = list(t_pm)
        paths = list(t_paths)
    return paths
