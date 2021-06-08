hex2binary

size_quasi_cycle = 128;

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
