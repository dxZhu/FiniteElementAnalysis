function PrintEQNUM(EQ_NUM)

fout = fopen('EQNUM.dat','w');
fprintf(fout, '%12.8f \n', EQ_NUM);
fclose(fout); 

end