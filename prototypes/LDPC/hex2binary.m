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
% To do that we 



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
        temp = find(binary_matrix(i,:)==1)+(column_control-1)*128; 
        Parity_bits_for_Encoder = [Parity_bits_for_Encoder temp];
        
    else
        temp = find(binary_matrix(i,:)==1)+7*128; 
        Parity_bits_for_Encoder = [Parity_bits_for_Encoder temp];
        position_Encoder = [position_Encoder, length(Parity_bits_for_Encoder)];
        row_control = row_control+1;
    end
end
Parity_bits_for_Encoder = Parity_bits_for_Encoder(2:end); %size() must equal number_of_1s!
position_Encoder = position_Encoder(2:end);


%% WIP: IGNORE
% %% Create the Parity Matrix 
% 
% 
% 
% Parity_matrix = circshift(final_binary_matrix(1,:),1);
% 
% for i=2:length(final_binary_matrix(:,1))
%     
%     square_i_matrix = circshift(final_binary_matrix(i,:),1);
% 
% 
% 
% 
% 
% 
% 
% 
% 
% 
% 
% 
% %% Create the quasicycle submatrices. 
% %It is implemeted just for practice and is not used by the LDPC encoded
% 
% size_of = 512/2;
% B = zeros(128,128,size_of);
% 
% for i=1:size_of
%     B(1,:,i) = binary_matrix(i);
%     for j=1:127
%         B(j+1,:,i) = circshift(B(j,:,i),1);
%     end
% end
%     