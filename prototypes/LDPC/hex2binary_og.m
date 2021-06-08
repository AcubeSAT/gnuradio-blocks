%% ========================================================================
% This program's purpose is to create the Parity Matrix that will be used
% in the LDPC System. The hexadecimal words are receive by the following
% file: https://github.com/adamgreig/labrador-ldpc/blob/master/src/codes/compact_generators.rs
% We use the elements for the 4096x1024 Generator Matrix.
% The data was given in u64, however we require square matrices 128x128, 
% hence we simply combine two u64 matrices in a row to create the final
% matrices. Note that since we have quasi cycle matrices we only need to
% keep the first row of the Generator Matrix for the Encoder


matlab_to_cpp = 1;
block_column = 8;
block_row = 32;
size_quasi_cycle = 128;

fileName = 'hex.txt';
FID = fopen(fileName);
data = textscan(FID,'%s');
fclose(FID);
stringData = string(data{:});
size_vector = zeros(512,1);
binary_matrix = zeros(512,64);
for i=1:length(stringData)
    stringData(i) = regexprep(stringData(i),",","");
    a = hexToBinaryVector(stringData(i));
    size_vector(i) = length(a);
    zero_padding = 64-size_vector(i);
    binary_matrix(i,:) = [zeros(1,zero_padding),a];
end


final_binary_matrix = zeros(size(binary_matrix,1)/2, size(binary_matrix,2)*2);
for i = 1:2:size(binary_matrix,1)
    final_binary_matrix(ceil(i/2),:) = [binary_matrix(i,:), binary_matrix(i+1,:)];
end


    
%% Create the matrix with the positions of 1s in the Generator Matrix

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

%full_Rows_Parity_bits = 0;

% for i=1:block_column:length(position_Rows)-7
%     this_parity = position_Rows(i);
%     end_parity = position_Rows(i+block_column);
%     parity_position = position_Rows(i:i+7);
%     full_Rows_Parity_bits = [full_Rows_Parity_bits, Rows_Parity_bits(this_parity:end_parity-1)];
%     for j=1:size_quasi_cycle - 1
%         for k = 0:7
%             temp_vector = Rows_Parity_bits(position_Rows(i+k):position_Rows(i+k+1)-1) + j;
%             fulfilment = (temp_vector > (k+1)*size_quasi_cycle)*(-size_quasi_cycle*(k+1));
%             temp_vector = temp_vector + fulfilment;
%             final_vector = sort(temp_vector);
%             full_Rows_Parity_bits = [full_Rows_Parity_bits, final_vector];
%         end
%         position_Rows = [position_Rows, parity_position];
%     end
% end
% 
% full_Rows_Parity_bits = full_Rows_Parity_bits(2:end) - matlab_to_cpp;
% Rows_Parity_bits = Rows_Parity_bits - matlab_to_cpp;
% position_Rows = position_Rows - matlab_to_cpp;








length_of_parity = length(final_binary_matrix(:,1));
B = zeros(size_quasi_cycle, size_quasi_cycle, length_of_parity);

for i=1:length_of_parity
    B(1,:,i) = final_binary_matrix(i,:);
    for j=1:size_quasi_cycle - 1
        B(j+1,:,i) = circshift(B(j,:,i),1);
    end
end


Parity = zeros(4096, 1024);

for i = 1:32
    for j = 1:8
        Parity(((i-1)*128+1:i*128),((j-1)*128+1:j*128)) = B(:,:,(i-1)*8 + j);
    end
end


Generator_Matrix = [eye(4096), Parity];

Parity_transpose = Parity';

H = [Parity_transpose, eye(1024)];


Column_Parity_bits = 0;
full_Column_Parity_bits = 0;
position_full_Column = 0;
position_Column = 0;
for column=1:block_column
    for row=1:block_row
        position_Column = [position_Column, length(Column_Parity_bits)];
        temp = find(B(:,1,((row-1)*block_column+column))==1) + size_quasi_cycle*(row-1);
        Column_Parity_bits = [Column_Parity_bits; temp];
        position_full_Column = [position_full_Column, length(full_Column_Parity_bits)];
        full_Column_Parity_bits = [full_Column_Parity_bits; temp];
        for i=2:size_quasi_cycle
            position_full_Column = [position_full_Column, length(full_Column_Parity_bits)];
            temp = find(B(:,i,((row-1)*block_column+column))==1) + size_quasi_cycle*(row-1);
            full_Column_Parity_bits = [full_Column_Parity_bits; temp];
        end
    end
end
 
Column_Parity_bits = Column_Parity_bits(2:end)'-matlab_to_cpp;
position_Column = position_Column(2:end)-matlab_to_cpp;
full_Column_Parity_bits = full_Column_Parity_bits(2:end)'-matlab_to_cpp;
position_full_Column = position_full_Column(2:end)-matlab_to_cpp;

position_full_Rows = 0;
full_Rows_Parity_bits = 0;

for row = 1:block_row
    for column = 1:block_column
        for i=1:size_quasi_cycle
            position_full_Rows = [position_full_Rows, length(full_Rows_Parity_bits)];
            temp = find(B(i,:,((row-1)*block_column+column))==1) + size_quasi_cycle*(column-1);
            full_Rows_Parity_bits = [full_Rows_Parity_bits, temp];
        end
    end
end

full_Rows_Parity_bits = full_Rows_Parity_bits(2:end) - matlab_to_cpp;
position_full_Rows = position_full_Rows(2:end) - matlab_to_cpp;
