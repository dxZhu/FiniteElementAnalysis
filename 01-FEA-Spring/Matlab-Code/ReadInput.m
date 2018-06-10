 function [N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       ELEM_NODE,ELEM_STIFF,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL] = ReadInput(filen,nnode_ele)

% INPUT:
% filen: name of the file with input values
% nnode_ele: number of nodes per element

% OUTPUT: 
% N_NODE, the (integer) number of nodes
% N_ELEM, the (integer) number of elements
% N_LOAD, the (integer) number of nonzero nodal forces, i.e. Pf
% N_PRE_DISP, the (integer) number of nodes with prescribed displacement, i.e. Up
% ELEM_NODE(nnode_ele, N_ELEM), matrix that contains node numbers (integers) for each element
% ELEM_STIFF(N_ELEM), vector that contains stiffness value (real) for each element
% FORCE_NODE(N_LOAD), vector that contains the node numbers (integer) where forces are applied
% FORCE_VAL(N_LOAD), vector that contains the value of the forces (real) corresponding to the numbers in FORCE_NODE
% DISP_NODE(N_PRE_DISP), vector that contains the node numbers (integer) where boundary conditions are imposed
% DISP_VAL(N_PRE_DISP),  vector that contains the value of the forces (real) corresponding to the numbers in DISP_NODE

% Open input file
fid=fopen(filen,'r');
A = fscanf(fid,'%f');

% read first line
N_NODE = A(1);
N_ELEM = A(2);    
N_LOAD = A(3); 
N_PRE_DISP = A(4);

% initialize vectors
ELEM_NODE = zeros(nnode_ele,N_ELEM); 
ELEM_STIFF = zeros(N_ELEM,1);
FORCE_NODE = zeros(N_LOAD,1); 
FORCE_VAL = zeros(N_LOAD,1);
DISP_NODE = zeros(N_PRE_DISP,1); 
DISP_VAL = zeros(N_PRE_DISP,1); 

count = 5;
% get node mumbers in each element and element stiffness
for i=1:N_ELEM
   ELEM_NODE(1,i)=A(count);
   ELEM_NODE(2,i)=A(count+1);
   ELEM_STIFF(i,1)=A(count+2);
   count = count + 3;
end
% get prescribed force values and corresponding node num
for i=1:N_LOAD
   FORCE_NODE(i,1)=A(count);
   FORCE_VAL(i,1)=A(count+1);
   count = count + 2;
end
% get prescribed displacement values and corresponding node num
for i=1:N_PRE_DISP
   DISP_NODE(i,1)=A(count);
   DISP_VAL(i,1)=A(count+1);
   count = count + 2;
end                         

fclose(fid);
end


