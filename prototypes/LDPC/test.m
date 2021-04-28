 sum1 = 0;
for i=1:8:248
%     if i == 1
%         temp = position_Rows(i+7);
%     else
    temp = position_Rows(i+8) - position_Rows(i);
    %end
    sum1 =[sum1 temp];

end
% sum2 = 0;
% 
% for i=1:8
%     if i==1
%         temp = position_Column(i+31)';
%     else
%         temp = position_Column(i+31)' - position_Column(i)';
%     end
%     sum2 = [sum2 temp];
% end
% 
sum1 = sum1(2:end)
% sum2 = sum2(2:end)

sum3 = 0;

for i=1:8
    sum3 = sum3 + sum(final_binary_matrix(i+184,:));
end
sum3