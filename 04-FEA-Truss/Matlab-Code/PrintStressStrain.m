function PrintStressStrain(stress,strain)

fout = fopen('Stress_Vector.dat','w');
fprintf(fout, '%12.8f \n', stress);
fclose(fout); 

fout = fopen('Strain_Vector.dat','w');
fprintf(fout, '%12.8f \n', strain);
fclose(fout); 

end