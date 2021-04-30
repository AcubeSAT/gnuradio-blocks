
#include "ldpc_check_decoder.h"

bool check_decoder(int *output, const int position_Columns[], int number_of_columns, int block_rows, int limit){
    int test = 0;

    for (int i = 0; i < number_of_columns; i++){
        int column_index = i * block_rows;
        int this_parity = position_Columns[column_index];
        int next_parity = position_Columns[column_index + block_rows];
        int length_of_parity = next_parity - this_parity;
        int total_sum = length_of_parity*output[i];
        test += total_sum % 2;
    }
    bool check;
    check = test > limit;
    return check;
}