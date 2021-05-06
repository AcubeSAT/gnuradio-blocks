hex2binary

message = ones(4096,1);
out = encoder_ldpc_test(message, Generator_Matrix);


function [encoded_message] = encoder_ldpc_test(message, Generator)
encoded_message = message'*Generator;
end