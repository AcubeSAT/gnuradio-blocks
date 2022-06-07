"""
This file reads SNR-BER values from two .txt files and generates the BER curves
"""
import matplotlib.pyplot as plt


def read_SNR_BER_values(file_name):
    with open(file_name) as f:
        SNR = []
        BER = []
        while True:
            vals_str = f.readline().split()
            if len(vals_str) != 2:  # If read last line
                break
            SNR.append(float(vals_str[0]))
            BER.append(float(vals_str[1]))
    return SNR, BER


def generate_BER_curves(file_name_1, label_1, file_name_2, label_2, title):
    SNR_1, BER_1 = read_SNR_BER_values(file_name_1);
    SNR_2, BER_2 = read_SNR_BER_values(file_name_2);
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
