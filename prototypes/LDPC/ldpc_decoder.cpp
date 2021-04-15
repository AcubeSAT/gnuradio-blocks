#include <iostream>
#include <valarray>

void decoder(int * output, const int parity_rows[], int position_rows[], int size_parity, int parity_columns[], int position_columns[], const double received_message[], int block_rows, int block_columns, int size_message, double noise_variance){
    double decoded_message[size_message];
    for (int i=0; i<size_message; i++){
        double temp = exp(-received_message[i]/noise_variance);
        temp += temp;
        decoded_message[i] = 1/temp;
    }
    double q_0[size_parity];
    double q_1[size_parity];
    double r_0[size_parity];
    double r_1[size_parity];
    double Q_0[size_message];
    double Q_1[size_message];
    for (int i=0; i<size_parity; i++){
        int temp = parity_rows[i];
        q_1[i] = decoded_message[temp];
    }

    while (CHECK){
        int check_nodes[1024];
        for (int i = 0; i<1024; i++){
            check_nodes[i] = 0;
        }
        int parity_nodes[4096];
        for (int i = 0; i<4096; i++){
            parity_nodes[i] = 0;
        }

        for (int i = 0; i<size_parity; i++){
            int position_of_parity = parity_columns[i];
            int this_parity = position_rows[position_of_parity*block_columns];
            int next_parity = position_rows[(position_of_parity+1)*block_columns];
            int length_vector = next_parity - this_parity;
            double vector_with_q_1[length_vector];
            for (int j = 0; j<length_vector; j++){
                vector_with_q_1[j] = q_1[this_parity+j];
            }
            double temp = 1;
            for (int k = 0; k < length_vector; k++) {
                if (k != check_nodes[position_of_parity]){
                    double pos = 1 - 2*vector_with_q_1[k];
                    temp *= pos;
                }
            }
            check_nodes[position_of_parity] ++;
            r_0[i] = 0.5 + 0.5*temp;
            r_1[i] = 1 - r_0[i];
        }

        for (int i = 0; i < size_parity; i++) {
            int position_of_parity = parity_rows[i];
            double Possibility_1 = decoded_message[position_of_parity];
            int this_parity = position_columns[position_of_parity*block_rows];
            int next_parity = position_columns[(position_of_parity+1)*block_columns];
            int length_vector;
            length_vector = next_parity - this_parity;
            double vector_with_r_0[length_vector];
            double vector_with_r_1[length_vector];
            for (int j = 0; j<length_vector; j++){
                vector_with_r_0[j] = r_0[this_parity+j];
                vector_with_r_1[j] = r_1[this_parity+j];
            }
            double temp_0 = 1;
            double temp_1 = 1;
            for (int k = 0; k < length_vector; k++) {
                if (k != parity_nodes[position_of_parity]){
                    temp_0 *= vector_with_r_0[k];
                    temp_1 *= vector_with_r_1[k];
                }
            }
            parity_nodes[position_of_parity]++;
            q_1[i] = Possibility_1*temp_1;
            q_0[i] = (1 - Possibility_1)*temp_0;
            double K = 1/(q_1[i] + q_0[i]);
            q_1[i] *= K;
            q_0[i] *= K;
        }

        for (int i = 0; i < size_message; i++) {
            int position_of_parity = parity_rows[i];
            double Possibility_1 = decoded_message[position_of_parity];
            int this_parity = position_columns[i]; // check index!
            int next_parity = position_columns[i+1]; // check index
            int length_vector;
            length_vector = next_parity - this_parity;
            double vector_with_r_0[length_vector];
            double vector_with_r_1[length_vector];
            for (int j = 0; j<length_vector; j++){
                vector_with_r_0[j] = r_0[this_parity+j];
                vector_with_r_1[j] = r_1[this_parity+j];
            }
            double temp_0 = 1;
            double temp_1 = 1;
            for (int k = 0; k < length_vector; k++) {
                temp_0 *= vector_with_r_0[k];
                temp_1 *= vector_with_r_1[k];
            }

            Q_1[i] = Possibility_1*temp_1;
            Q_0[i] = (1 - Possibility_1)*temp_0;
            double K = 1/(Q_1[i] + Q_0[i]);
            Q_1[i] *= K;
            Q_0[i] *= K;
            if (Q_0[i] > Q_1[i]){
                output[i] = 0;
            } else {
                output[i] = 1;
            }
        }
    }
}