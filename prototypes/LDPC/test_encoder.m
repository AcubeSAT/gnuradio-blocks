hex2binary

message = (rand(4096,1) > 0.5);
out = encoder_ldpc_test(message, Generator_Matrix);
out = out(4097:end);

function [encoded_message] = encoder_ldpc_test(message, Generator)
encoded_message = message'*Generator;
encoded_message = mod(encoded_message,2);
end