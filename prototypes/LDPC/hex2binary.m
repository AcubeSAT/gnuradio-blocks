%% ========================================================================
% This program's purpose is to create the Parity Matrix that will be used
% in the LDPC System. The hexadecimal words are receive by the following
% file: https://github.com/adamgreig/labrador-ldpc/blob/master/src/codes/compact_generators.rs
% We use the elements for the 4096x1024 Parity Matrix.
% The data was given in u64, however we require square matrices 128x128, 
% hence we simply combine two u64 matrices in a row to create the final
% matrices. Note that since we have quasi cycle matrices we only need to
% keep the first row of the Parity Matrix for the Encoder and the first
% Column for the Decoder. This means that we do not actually create the
% whole square matrix, but just the first line. Then in the encoder/decoder
% we simply keep the positions of 1s in a vector. We must also keep the
% position of the aforemention matrix that a new quasi matrix is examined.




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

    
%% Create the matrix with the positions of 1s in the Parity Matrix for the Encoder.

number_of_1s = sum(sum(binary_matrix));
Parity_bits_for_Encoder = 0;
position_Encoder = 0;
row_control = 1;
for i=1:length(final_binary_matrix(:,1))
    column_control = mod(i,8);
    if column_control ~= 0
        position_Encoder = [position_Encoder, length(Parity_bits_for_Encoder)];
        temp = find(final_binary_matrix(i,:)==1)+(column_control-1)*128; 
        Parity_bits_for_Encoder = [Parity_bits_for_Encoder temp];
        
    else
        temp = find(final_binary_matrix(i,:)==1)+7*128; 
        Parity_bits_for_Encoder = [Parity_bits_for_Encoder temp];
        position_Encoder = [position_Encoder, length(Parity_bits_for_Encoder)];
        row_control = row_control+1;
    end
end
Rows_Parity_bits = Parity_bits_for_Encoder(2:end); %size() must equal number_of_1s!
position_Rows = position_Encoder(2:end);


%% Parity Matrix for Decoder

length_of_parity = length(final_binary_matrix(:,1));
B = zeros(128,128,length_of_parity);

for i=1:length_of_parity
    B(1,:,i) = final_binary_matrix(i,:);
    for j=1:127
        B(j+1,:,i) = circshift(B(j,:,i),1);
    end
end

Column_Parity_bits = 0;
position_Column = 0;
for column=1:8
    for row=1:32
        if j==1
            temp = find(B(:,1,column)==1);
            Column_Parity_bits = [Column_Parity_bits; temp];
            position_Column = [position_Column, length(Column_Parity_bits)];
        else
            temp = find(B(:,1,1+(row-1)*8)==1) + 128*(row-1);
            Column_Parity_bits = [Column_Parity_bits; temp];
            position_Column = [position_Column, length(Column_Parity_bits)];
        end
    end
end
 
Column_Parity_bits = Column_Parity_bits(2:end)';
position_Column = position_Column(2:end)';

 