"""
This file reads SNR-BER values from two .txt files and generates the BER curves
"""
import matplotlib.pyplot as plt


def generate_BER_curves(file_name_1, label_1, file_name_2, label_2, title):
    f_1 = open(file_name_1, "r")  # Change name of file to read here
    f_2 = open(file_name_2, "r")  # Change name of file to read here
    SNR_1 = []
    BER_1 = []
    SNR_2 = []
    BER_2 = []
    while True:
        vals_str = f_1.readline().split()
        if len(vals_str) != 2:  # If read last line
            break
        SNR_1.append(float(vals_str[0]))
        BER_1.append(float(vals_str[1]))

    while True:
        vals_str = f_2.readline().split()
        if len(vals_str) != 2:  # If read last line
            break
        SNR_2.append(float(vals_str[0]))
        BER_2.append(float(vals_str[1]))

    plt.semilogy(SNR_1, BER_1, 'r', label=label_1)
    plt.semilogy(SNR_2, BER_2, 'b', label=label_2)
    plt.title(title)
    plt.legend()
    plt.xlabel('E_b / S_0 (dB)')
    plt.ylabel('BIT ERROR RATE')
    plt.grid()
    plt.show()


generate_BER_curves("convolutional_BER_data.txt", "gr-a3sat", "theoretical_BER_data.txt", "theoretical",
                    "Convolutional")
