"""Binary BCH encoder/decoder prototype"""

import numpy as np
import math


g = int("11000101", 2) # generator polynomial for BCH(63, 56)
# x^7 + x^6 + x^2 + 1 = 0
n = 63
k = 56

# Pre-compute the powers of the primitive elements so they are expressed
# in the basis {α, α^2, ..., α^k}
# For example if the generator polynomial is x^7 + x^6 + x^2 + 1 => α^7 + α^6 + α^2 + 1 = 0 =>
# α^7 = α^6 + α^2 + 1

primitive_elements_bch_63_54 = [1, 2, 4, 8, 16, 32, 64, 69, 79, 91, 115, 35, 70, 73, 87, 107,
                                19, 38, 76, 93, 127, 59, 118, 41, 82, 97, 7, 14, 28, 56, 112,
                                37, 74, 81, 103, 11, 22, 44, 88, 117, 47, 94, 121, 55, 110, 25,
                                50, 100, 13, 26, 52, 104, 21, 42, 84, 109, 31, 62, 124, 61, 122,
                                49, 98, 1]

def binary_poly_division(a, b):
    """
    Does polynomial division in GF(2) - essentially long binary division.
    In this context, a and b are integers the binary representation of which
    indicates their coefficients.

    TODO? We could unroll and get rid of the extra conditional checks if we know
    the generator beforehand.
    """
    if b == 0:
        return
    if a == 0:
        return (0, b)

    # TODO: Too expensive for no reason. Why log when you can shift??
    deg_a = math.floor(math.log(a, 2)) + 1
    deg_b = math.floor(math.log(b, 2)) + 1

    k = 0
    q = 0
    
    while a >= b:
        q <<= 1
        if a >> (deg_a - k - 1) & 1 == 1:        
            a ^= b << (deg_a - deg_b - k)
            q += 1
        k += 1
    deg_r = math.floor(math.log(a, 2)) + 1

    return (a, q << (deg_r - 1))

def encode_bch(m):
    """
    Implements a systematic binary BCH encoder. Assumes block size fits into supported data types
    """
    # Shift the message polynomial
    p = m << (n-k)

    # get remainder of division of message polynomial with generator
    r = binary_poly_division(p, g)[0]
    
    # add parity bits to the message polynomial
    # TODO (here?) - BCH(63, 56) is normally padded to 64 bits so a left shift might be needed
    # in the encoder and a right shift in the decoder to follow the standard
    return p | r

def calc_syndromes_63_56(r):
    """
    Calculate syndromes given the received message r for BCH(63, 56)
    """
    # Initialize syndromes
    s1 = s2 = 0
    i = 0
    while r:
        b = r & 1
        if b == 1:
            s1 ^= primitive_elements_bch_63_54[(i)%63]
            s2 ^= primitive_elements_bch_63_54[(2*i)%63] 
        i += 1
        r >>= 1

    s1 = binary_poly_division(s1, g)[0]
    s2 = binary_poly_division(s2, g)[0]
    return [s1, s2]

