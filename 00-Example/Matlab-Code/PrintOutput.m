function PrintOutput(EQ_NUM,KPP,KPF,KFP,KFF,UF,PP,UUR,PUR)
%% This function must not be modified!!! 
%% Autograding script will be using this output format 
%% when grading your assignments

fout = fopen('EQNUM.dat','w');
fprintf(fout, '%12.8f \n', EQ_NUM);
fclose(fout); 

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
