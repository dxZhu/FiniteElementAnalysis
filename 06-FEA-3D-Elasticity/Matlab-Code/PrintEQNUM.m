function PrintEQNUM(EQ_NUM)

fout = fopen('EQNUM.dat','w');
for i = 1:size(EQ_NUM,1)
    fprintf(fout, '%12.8f', EQ_NUM(i,:));
    fprintf(fout, '\n');
end
fclose(fout); 

end