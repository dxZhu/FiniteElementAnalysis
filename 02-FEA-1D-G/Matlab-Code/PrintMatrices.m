function PrintMatrices(KPP,KPF,KFP,KFF)

fout = fopen('KPP_Matrix.dat','w');
for i = 1:size(KPP,1)
    fprintf(fout, '%12.8f ', KPP(i,:));
    fprintf(fout, '\n');
end
fclose(fout); 

fout = fopen('KPF_Matrix.dat','w');
for i = 1:size(KPF,1)
    fprintf(fout, '%12.8f ', KPF(i,:));
    fprintf(fout, '\n');
end
fclose(fout); 

fout = fopen('KFP_Matrix.dat','w');
for i = 1:size(KFP,1)
    fprintf(fout, '%12.8f ', KFP(i,:));
    fprintf(fout, '\n');
end
fclose(fout); 

fout = fopen('KFF_Matrix.dat','w');
for i = 1:size(KFF,1)
    fprintf(fout, '%12.8f ', KFF(i,:));
    fprintf(fout, '\n');
end
fclose(fout); 

end