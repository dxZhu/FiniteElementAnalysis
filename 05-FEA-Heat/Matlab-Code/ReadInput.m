  function [N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ELEM_AREA,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       N_TRAC_c, TRAC_c_ELE, TRAC_c_VAL, N_TRAC_q, TRAC_q_ELE, TRAC_q_VAL, ...
       NNODE_ELE, DOF_NODE, EDOF, Ng, ShapeOrder] = ReadInput(filen,NDIM)

% INPUT:
% filen: name of the file with input values
% ndim: problem dimension (ndim=2 -> 2D problem)


% OUTPUT: 
% N_NODE, the (integer) number of nodes
% N_ELEM, the (integer) number of elements
% N_LOAD, the (integer) number of nonzero prescribed concentrated loads
% N_PRE_DISP, the (integer) number prescribed field (essential) BCs
% N_MAT, the (integer) number of material sets 
% N_BLOAD, the (integer) number of body load sets
% N_TRAC, the (integer) number of prescribed flux/traction BCs
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
A = fscanf(fid,'%i %i %i %i %i %i %i %i\n', 8);
N_NODE = A(1);
N_ELEM = A(2);    
N_LOAD = A(3); 
N_PRE_DISP = A(4);
N_TRAC_q = A(5);
N_TRAC_c = A(6);
N_MAT = A(7);
N_BLOAD = A(8);

Ng = 2;
ShapeOrder = 1;


NNODE_ELE = 4;
DOF_NODE = 1; %Number of degrees of freedom per node
EDOF = NNODE_ELE*DOF_NODE; %number of degrees of freedom per element


% initialize vectors
COORDS = zeros(N_NODE,NDIM);
ELEM_NODE = zeros(NNODE_ELE,N_ELEM); 
ELEM_STIFF = zeros(N_ELEM,2); % (kx,ky)
ELEM_AREA = zeros(N_ELEM,1); % t
ELEM_LOAD = zeros(N_ELEM,2); % (Q)
FORCE_NODE = zeros(N_LOAD,NDIM); % first entry is the node, second entry is the DOF
FORCE_VAL = zeros(N_LOAD,1);
DISP_NODE = zeros(N_PRE_DISP,NDIM);  % first entry is the node, second entry is the DOF
DISP_VAL = zeros(N_PRE_DISP,1); 
TRAC_c_ELE = zeros(N_TRAC_c,2); % first entry is the element, second entry is the local edge number
TRAC_c_VAL = zeros(N_TRAC_c,2); % (h, Tinf)
TRAC_q_ELE = zeros(N_TRAC_q,2); % first entry is the element, second entry is the local edge number
TRAC_q_VAL = zeros(N_TRAC_q,1);

material = zeros(N_MAT,3); %(index, kx,ky,t)
bodyload = zeros(N_BLOAD,1);

for i=1:N_MAT
    temp = fscanf(fid,'%i',1);
    for j=1:3
        val = fscanf(fid,'%f',1);
        material(i,j) = val;
    end
    fscanf(fid,'\n');
end
for i=1:N_BLOAD
    temp = fscanf(fid,'%i',1);
    val = fscanf(fid,'%f \n',1);
    bodyload(i,1) = val;   
 end

for i=1:N_NODE
   fscanf(fid,'%i',1);
   for j=1:NDIM    
        val  = fscanf(fid, '%f\n' ,1);
        COORDS(i,j) = val;
   end
end


for i=1:N_ELEM  
   fscanf(fid,'%i',1);
   for j=1:NNODE_ELE
        line = fscanf(fid, '%i',1);   
        ELEM_NODE(j,i)=line(1);
   end
   line = fscanf(fid, '%i %i \n',2);
   ELEM_STIFF(i,1) = material(line(1),1);
   ELEM_STIFF(i,2) = material(line(1),2);  
   ELEM_LOAD(i,1) = bodyload(line(2),1);
   ELEM_AREA(i,1) =  material(line(1),3);
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


% get prescribed traction (heat flux)
for i=1:N_TRAC_q
   line = fscanf(fid, '%i %i %f \n',3);
   TRAC_q_ELE(i,1)=line(1);
   TRAC_q_ELE(i,2)=line(2);
   TRAC_q_VAL(i,1)=line(3);
end  

% get prescribed traction (convection)
for i=1:N_TRAC_c
   line = fscanf(fid, '%i %i %f %f \n',4);
   TRAC_c_ELE(i,1)=line(1);
   TRAC_c_ELE(i,2)=line(2);
   TRAC_c_VAL(i,1)=line(3);
   TRAC_c_VAL(i,2)=line(4);   
end 

fclose(fid);
end


