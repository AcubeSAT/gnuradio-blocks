%% ========================================================================
% This program's purpose is to create the Parity Matrix that will be used
% in the LDPC System. The hexadecimal words are receive by the following
% file: https://github.com/adamgreig/labrador-ldpc/blob/master/src/codes/compact_generators.rs
% We use the elements for the 4096x1024 Parity Matrix.


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

    
%% Create the matrix with the positions of 1s in the Generator Matrix

number_of_1s = sum(sum(binary_matrix));
C = 0;
position = zeros(32,1);
position(1) = 1;
for i=1:length(binary_matrix(:,1))
    control = mod(i,16);
    if control ~= 0
        temp = find(binary_matrix(i,:)==1)+(control-1)*64; 
        C = [C temp];
    else
        temp = find(binary_matrix(i,:)==1)+15*64; 
        C = [C temp];
        temp2 = length(C);
        position(i/16+1) = temp2; %Now we now from  which element of C the next row begins
    end
end
C = C(2:end); %size(C) must equal number_of_1s!

%% Create the quasicycle submatrices. 
%It is implemeted just for practice and is not used by the LDPC encoded

size = 512/2;
B = zeros(128,128,size);

for i=1:size
    B(1,:,i) = binary_matrix(i);
    for j=1:127
        B(j+1,:,i) = circshift(B(j,:,i),1);
    end
end
    