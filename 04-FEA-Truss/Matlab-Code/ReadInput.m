  function [N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ELEM_AREA,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       NNODE_ELE, DOF_NODE, EDOF] = ReadInput(filen,NDIM)

% INPUT:
% filen: name of the file with input values
% nnode_ele: number of nodes per element

% OUTPUT: 
% N_NODE, the (integer) number of nodes
% N_ELEM, the (integer) number of elements
% N_LOAD, the (integer) number of nonzero nodal forces, i.e. Pf
% N_PRE_DISP, the (integer) number of nodes with prescribed displacement, i.e. Up
% ELEM_NODE(nnode_ele, N_ELEM), matrix that contains node numbers (integers) for each element
% ELEM_STIFF(N_ELEM,2), vector that contains stiffness value (real) and thermal expansion coefficient for each element
% ELEM_LOAD(N_ELEM,2), vector that contains specific weight (real) and change in temperature for each element
% FORCE_NODE(N_LOAD), vector that contains the node numbers (integer) where forces are applied
% FORCE_VAL(N_LOAD), vector that contains the value of the forces (real) corresponding to the numbers in FORCE_NODE
% DISP_NODE(N_PRE_DISP), vector that contains the node numbers (integer) where boundary conditions are imposed
% DISP_VAL(N_PRE_DISP),  vector that contains the value of the forces (real) corresponding to the numbers in DISP_NODE

                        
% This function reads the input file.

% Open input file
fid=fopen(filen,'r');

% read first line
A = fscanf(fid,'%i %i %i %i \n', 4);
N_NODE = A(1);
N_ELEM = A(2);    
N_LOAD = A(3); 
N_PRE_DISP = A(4);

NNODE_ELE = 2;
DOF_NODE = 2; %Number of degrees of freedom per node
EDOF = NNODE_ELE*DOF_NODE; %number of degrees of freedom per element


% initialize vectors
COORDS = zeros(N_NODE,NDIM);
ELEM_NODE = zeros(NNODE_ELE,N_ELEM); 
ELEM_STIFF = zeros(N_ELEM,2);
ELEM_AREA = zeros(N_ELEM,1);
ELEM_LOAD = zeros(N_ELEM,2); % this will store the specific weight (gamma) of the material, 
                            %  used to calculate the load due to gravity
                            %  and the change in temperature, for the
                            %  thermal loading
FORCE_NODE = zeros(N_LOAD,NDIM); % first entry is the node, second entry is the DOF
FORCE_VAL = zeros(N_LOAD,1);
DISP_NODE = zeros(N_PRE_DISP,NDIM);  % first entry is the node, second entry is the DOF
DISP_VAL = zeros(N_PRE_DISP,1); 

for i=1:N_NODE
   for j=1:NDIM    
        val  = fscanf(fid, '%f\n' ,1);
        COORDS(i,j) = val;
   end
end


for i=1:N_ELEM  

   for j=1:NNODE_ELE
        line = fscanf(fid, '%i',1);   
        ELEM_NODE(j,i)=line(1);
   end
   line = fscanf(fid, '%f %f %f\n',5);
   ELEM_STIFF(i,1)= line(1);
   ELEM_LOAD(i,1) = line(2);
   ELEM_AREA(i,1) = line(3);  
   ELEM_STIFF(i,2) = line(4);
   ELEM_LOAD(i,2) = line(5);
   
end


% get prescribed force values and corresponding node num
for i=1:N_LOAD
   line = fscanf(fid, '%i %i %f \n',3);
   FORCE_NODE(i,1)=line(1);
   FORCE_NODE(i,2)=line(2);
   FORCE_VAL(i,1)=line(3);
end


% get prescribed displacement values and corresponding node num
for i=1:N_PRE_DISP
   line = fscanf(fid, '%i %i %f \n',3);
   DISP_NODE(i,1)=line(1);
   DISP_NODE(i,2)=line(2);
   DISP_VAL(i,1)=line(3);
end                         

fclose(fid);
end


