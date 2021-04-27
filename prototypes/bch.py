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

# error location based on calculated syndrome
syndromes_hash = {
    98: 0, 49: 1, 122: 2, 61: 3, 124: 4, 62: 5, 31: 6, 109: 7, 84: 8, 42: 9, 21: 10, 104: 11, 52: 12,
    26: 13, 13: 14, 100: 15, 50: 16, 25: 17, 110: 18, 55: 19, 121: 20, 94: 21, 47: 22, 117: 23, 88: 24,
    44: 25, 22: 26, 11: 27, 103: 28, 81: 29, 74: 30, 37: 31, 112: 32, 56: 33, 28: 34, 14: 35, 7: 36, 97: 37,
    82: 38, 41: 39, 118: 40, 59: 41, 127: 42, 93: 43, 76: 44, 38: 45, 19: 46, 107: 47, 87: 48, 73: 49, 70: 50,
    35: 51, 115: 52, 91: 53, 79: 54, 69: 55, 64: 56, 32: 57, 16: 58, 8: 59, 4: 60, 2: 61, 1: 62
    }

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
        return 0, b

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

    return a, q << (deg_r - 1)

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

def decode_bch_63_56(c):
    """
    Decodes a BCH codeword with at most 1 error using a hash table. For the general case,
    the Berlekamp - Massey algorithm over a Galois field of characteristic 2 can be used.
    The problem is equivalent to determining an LFSR of minimal degree that finds the coefficients
    for the linear sum of the syndromes which results in 0.
    """
    s1 = calc_syndromes_63_56(c)[0]
    # No detectable errors
    if s1 == 0:
        return bin(c)
    elif s1 in syndromes_hash:
        c ^= 2**(63 - syndromes_hash[s1]-1)
        return bin(c)
    # Can't decode
    else:
        return -1