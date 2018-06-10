function [EQ_NUM,KPP,KPF,KFP,KFF,UF,PP,UUR,PUR] =  ExampleFunctions(N_NODE, ELEM_STIFF, ELEM_NODE)
                                       
%% Just some "random" calculations...
N_DOF = 5;
TOTAL_DOF = 7;

EQ_NUM = zeros(N_NODE,1);
UF = ones(N_DOF, 1); 
KPP = zeros(TOTAL_DOF-N_DOF, TOTAL_DOF-N_DOF); 
KFF = ones(N_DOF, N_DOF);
KPF = zeros(TOTAL_DOF-N_DOF,N_DOF); 
KFP = ones(N_DOF, TOTAL_DOF-N_DOF); 

UF = ELEM_STIFF(3)*UF;

for i=1:TOTAL_DOF-N_DOF
    for j=1:N_DOF
        if (i<j) 
            KFP(j,i) = ELEM_STIFF(j);            
            KPF(i,j) = ELEM_NODE(1,j);
        end
     end
end 
PP = KFP\UF;

UUR = ones(N_NODE,1);
PUR = zeros(N_NODE,1);



    