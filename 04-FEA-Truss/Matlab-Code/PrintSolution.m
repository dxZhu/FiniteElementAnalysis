function PrintSolution(UF,PP,UUR,PUR)

fout = fopen('UF_Vector.dat','w');
fprintf(fout, '%12.8f \n', UF);
fclose(fout); 

fout = fopen('PP_Vector.dat','w');
fprintf(fout, '%12.8f \n', PP);
fclose(fout); 

fout = fopen('UUR_Vector.dat','w');
fprintf(fout, '%12.8f \n', UUR);
fclose(fout); 

fout = fopen('PUR_Vector.dat','w');
fprintf(fout, '%12.8f \n', PUR);
fclose(fout); 

fprintf('NODE DISPLACEMENT\n')
disp(UUR);
fout = fopen('UUR_Vector.dat','w');
for i = 1:size(UUR,1)
    fprintf(fout, '%12.8f ', UUR(i,:));
    fprintf(fout, '\n');
end

fprintf('NODE FORCE\n')
disp(PUR);
fout = fopen('PUR_Vector.dat','w');
for i = 1:size(PUR,1)
    fprintf(fout, '%12.8f ', PUR(i,:));
    fprintf(fout, '\n');
end


end