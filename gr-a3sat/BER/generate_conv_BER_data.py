"""
This script:
- Generates a pseudorandom bitstream of length 2048
- Encodes the pseudorandom bitstream using the convolutional encoder as implemented in ../lib/conv_enc_impl.cc
- Adds Gaussian Noise to each bit of the codeword with different values of standard deviation
    (which correspond to different values of SNR)
- Decodes the noised codeword using the convolutional soft decoder as implemented in ../lib/conv_dec_impl.cc
- Calculates the number of errors (different bits between original bitstream and the outuput of the decoder)
- Repeats this process test_repetition times and calculates the average Bit Error Rate (BER) for each SNR value
- Prints this data to stdout and how long it takes to calculate BER for each SNR value
- Saves this data in "convolutional_BER_data.txt" (but not how long it takes)
Note:
    "theoretical_BER_data.txt" includes another dataset taken from CCSDS 130.1-G-3 GREEN BOOK JUNE 2020 figure 4-6
    unquantized soft decision using https://automeris.io/WebPlotDigitizer/
    These two data sets are then plotted together using generate_BER_curve.py
"""
import sys

sys.path.append("../build/swig")

from gnuradio import blocks, gr
import a3sat_swig as a3sat

import random
import numpy as np
import time

average = lambda l: sum(l) / len(l)


def conv_BER(test_repetitions):
    INPUT_SIZE = 2048
    if os.path.getsize("convolutional_BER_data.txt"):  # If file is not empty
        with open("convolutional_BER_data.txt", "w"):  # Make sure that the file is empty
            pass
    with open("convolutional_BER_data.txt", "a") as f:
        # Generate different values for the standard deviation of noise to calculate the BER for different values of SNR
        for standard_deviation in list(np.arange(0.27, 0.5, 0.0001)):
            start = time.time()
            error_counter = [0 for _ in range(test_repetitions)]
            for k in range(test_repetitions):
                # Initialise a list of 2048 random "bits" (integers of value 0 or 1)
                random_src = [random.randint(0, 1) for _ in range(INPUT_SIZE)]

                # Encoding routine
                tb_enc = gr.top_block()
                vector_src_enc = blocks.vector_source_b(random_src, False, 1, [])
                conv_enc = a3sat.conv_enc()
                dst_enc = blocks.vector_sink_b()
                tb_enc.connect(vector_src_enc, conv_enc)
                tb_enc.connect(conv_enc, dst_enc)
                tb_enc.run()
                tb_enc.stop()
                encoded_data = dst_enc.data()  # This is a tuple of 4096 bits

                # noised_data is going to be the input to the decoder
                expected_value = 0
                noised_data = [bit + np.random.normal(expected_value, standard_deviation) for bit in encoded_data]
                # Clip noised_data so all values fit in [0, 1] (needed for the decoder)
                noised_data = [0 if value < 0 else 1 if value > 1 else value for value in noised_data]

                # Decoding routine
                tb_dec = gr.top_block()
                vector_src_dec = blocks.vector_source_f(noised_data, False, 1, [])
                conv_dec = a3sat.conv_dec(False)
                tb_dec.connect(vector_src_dec, conv_dec)
                dst_dec = blocks.vector_sink_b()
                tb_dec.connect(conv_dec, dst_dec)
                tb_dec.run()
                tb_dec.stop()
                result_data = dst_dec.data()

                # Count how many bit errors
                error_counter[k] = sum(i != j for i, j in zip(random_src, result_data))

            end = time.time()

            """
            SNR = 10*log10(Px/Pn) where Px is the power of the signal and Pn is the power of the noise.
            In this case the signal is the bitstream meaning it only takes as values 1 and 0 with the same probability
            therefore E[X(n)] = 1/2 (its expected value is 1/2).
            The power of the signal is Px = σ_x^2 = E[(X(n))^2] - E[X(n)]^2 = 1/2 - 1/4 = 1/4.
            Pn is equal to the deviation Pn = σ^2.
            So we have SNR = 10*log10(1/(4*σ^2))
            """
            SNR = 10 * np.log10(1 / (4 * standard_deviation ** 2))
            avg_errors_num = average(error_counter)
            avg_BER = avg_errors_num / INPUT_SIZE
            print(
                f"Seconds Passed = {(end - start)} - For SNR = {SNR} we have {avg_errors_num} errors or, {avg_BER} error rate")
            f.write(str(SNR) + " " + str(avg_BER) + "\n")


"""
Higher test_repetitions values ensure more accurate results.
If test_repetitions is not high enough, then the BER curve might show some spikes which do not correspond
to the actual performance of the encoder/decoder.
Suggested value: test_repetitions > 500
"""
conv_BER(600)
