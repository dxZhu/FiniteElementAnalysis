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
fprintf( '%12.8f \n', UUR);
fprintf('NODE FORCE\n')
fprintf( '%12.8f \n', PUR);


end