"""Binary BCH encoder/decoder prototype of the BCH(56,63) code that is  specified in CCSDS 231.0-B-3 using the
generator polynomial of the encoder is g(x) = x^7 + x^6 + x^2 + 1. We pre-compute the powers of the primitive
elements so they are expressed in the basis {α, α^2, ..., α^k}. For example if the generator polynomial is x^7 + x^6
+ x^2 + 1 => α^7 + α^6 + α^2 + 1 = 0 =>  α^7 = α^6 + α^2 + 1. Then we find the error location based on the calculated
syndrome with the help of syndromes_hash table that matches the syndrome with the error location on the codeword """

import math

generator_polynomial = int("11000101", 2)
n = 63
k = 56
primitive_elements_bch_63_54 = [1, 2, 4, 8, 16, 32, 64, 69, 79, 91, 115, 35, 70, 73, 87, 107,
                                19, 38, 76, 93, 127, 59, 118, 41, 82, 97, 7, 14, 28, 56, 112,
                                37, 74, 81, 103, 11, 22, 44, 88, 117, 47, 94, 121, 55, 110, 25,
                                50, 100, 13, 26, 52, 104, 21, 42, 84, 109, 31, 62, 124, 61, 122,
                                49, 98, 1]

syndromes_hash = {
    98: 0, 49: 1, 122: 2, 61: 3, 124: 4, 62: 5, 31: 6, 109: 7, 84: 8, 42: 9, 21: 10, 104: 11, 52: 12,
    26: 13, 13: 14, 100: 15, 50: 16, 25: 17, 110: 18, 55: 19, 121: 20, 94: 21, 47: 22, 117: 23, 88: 24,
    44: 25, 22: 26, 11: 27, 103: 28, 81: 29, 74: 30, 37: 31, 112: 32, 56: 33, 28: 34, 14: 35, 7: 36, 97: 37,
    82: 38, 41: 39, 118: 40, 59: 41, 127: 42, 93: 43, 76: 44, 38: 45, 19: 46, 107: 47, 87: 48, 73: 49, 70: 50,
    35: 51, 115: 52, 91: 53, 79: 54, 69: 55, 64: 56, 32: 57, 16: 58, 8: 59, 4: 60, 2: 61, 1: 62
}


def binary_polynomial_division(dividend, divisor):
    """
    Performs polynomial division in GF(2) - essentially long binary division.
    In this context, a and b are integers the binary representation of which
    indicates their coefficients. The remainder is saved in the dividend variable in the
    end of the process.
    """
    # TODO? We could unroll and get rid of the extra conditional checks if we know the generator beforehand.
    if divisor == 0:
        return
    if dividend == 0:
        return 0, divisor

    # TODO: Too expensive for no reason. Why log when you can shift??
    dividend_degree = math.floor(math.log(dividend, 2)) + 1
    divisor_degree = math.floor(math.log(divisor, 2)) + 1
    bit_position = 0
    quotient = 0
    while dividend >= divisor:
        quotient <<= 1
        if dividend >> (dividend_degree - bit_position - 1) & 1 == 1:
            dividend ^= divisor << (dividend_degree - divisor_degree - bit_position)
            quotient += 1
        bit_position += 1
    deg_r = math.floor(math.log(dividend, 2)) + 1

    return dividend, quotient << (deg_r - 1)


def encode_bch(message):
    """
    Implements a systematic binary BCH encoder. Assumes block size fits into supported data types.
    We get the remainder of the division of the message polynomial with the generator and add parity
    bits to the message polynomial.
    """
    p = message << (n - k)
    remainder = binary_polynomial_division(p, generator_polynomial)[0]

    # TODO (here?) - BCH(63, 56) is normally padded to 64 bits so a left shift might be needed
    # in the encoder and a right shift in the decoder to follow the standard
    return p | remainder


def calc_syndromes_63_56(received_message):
    """
    Calculate syndromes given the received message r for BCH(63, 56)
    """
    syndrome1 = syndrome2 = 0
    index = 0
    while received_message:
        current_bit = received_message & 1
        if current_bit == 1:
            syndrome1 ^= primitive_elements_bch_63_54[index % 63]
            syndrome2 ^= primitive_elements_bch_63_54[(2 * index) % 63]
        index += 1
        received_message >>= 1
    syndrome1 = binary_polynomial_division(syndrome1, generator_polynomial)[0]
    syndrome2 = binary_polynomial_division(syndrome2, generator_polynomial)[0]
    return [syndrome1, syndrome2]


def decode_bch_63_56(codeword):
    """
    Decodes a BCH codeword with at most 1 error using a hash table. For the general case,
    the Berlekamp - Massey algorithm over a Galois field of characteristic 2 can be used.
    The problem is equivalent to determining an LFSR of minimal degree that finds the coefficients
    for the linear sum of the syndromes which results in 0. If there are no detectable errors, it returns
    the sent data. If there is at most one error it corrects it and returns the sent data. If there is more
    than one errors it can't decode the codeword.
    """
    syndrome1 = calc_syndromes_63_56(codeword)[0]
    if syndrome1 == 0:
        return bin(codeword)
    elif syndrome1 in syndromes_hash:
        codeword ^= 2 ** (63 - syndromes_hash[syndrome1] - 1)
        return bin(codeword)
    else:
        return -1
