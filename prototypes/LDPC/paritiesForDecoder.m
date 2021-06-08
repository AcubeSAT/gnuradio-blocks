GeneratorMatrix

matlab_to_cpp = 1;

[rows, columns] = size(H);

Columns_Parity_bits = 0;
position_Columns = zeros(1,columns);

for i = 1:columns
    position_Columns(i) = length(Columns_Parity_bits);
    vector_with_1 = find(H(:,i) == 1);
    Columns_Parity_bits = [Columns_Parity_bits, vector_with_1'];
end
        
Columns_Parity_bits = Columns_Parity_bits(2:end);% - matlab_to_cpp;
%position_Columns = position_Columns-matlab_to_cpp;

Rows_Parity_bits = 0;
position_Rows = zeros(1,rows);

for i = 1:rows
    position_Rows(i) = length(Rows_Parity_bits);
    vector_with_1 = find(H(i,:) == 1);
    Rows_Parity_bits = [Rows_Parity_bits, vector_with_1];
end

Rows_Parity_bits  = Rows_Parity_bits (2:end);% - matlab_to_cpp;
%position_Rows = position_Rows - matlab_to_cpp;