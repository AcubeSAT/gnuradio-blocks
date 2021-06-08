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