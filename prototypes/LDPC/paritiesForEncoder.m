hex2binary

matlab_to_cpp = 1;
block_column = 8;
block_row = 32;
size_quasi_cycle = 128;

number_of_1s = sum(sum(binary_matrix));
Rows_Parity_bits = 0;
position_Rows = 0;
row_control = 1;
for i=1:length(final_binary_matrix(:,1))
    column_control = mod(i-1,block_column);
    position_Rows = [position_Rows, length(Rows_Parity_bits)];
    temp = find(final_binary_matrix(i,:)==1)+(column_control)*size_quasi_cycle; 
    Rows_Parity_bits = [Rows_Parity_bits temp];
end
Rows_Parity_bits = Rows_Parity_bits(2:end) - matlab_to_cpp;
position_Rows = position_Rows(2:end) - matlab_to_cpp;