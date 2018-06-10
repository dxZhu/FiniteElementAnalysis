  function [N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ELEM_AREA,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       N_TRAC, TRAC_ELE, TRAC_VAL,  ...
       NNODE_ELE, DOF_NODE, EDOF, Ng, ShapeOrder, Model2D] = ReadInput(filen,NDIM)

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
% First line of input file

% N_NODE N_ELEM  N_LOAD  N_PRE_DISP  N_TRAC  N_MAT  N_BLOAD  Model2D 

% Open input file
fid=fopen(filen,'r');

% read first line
A = fscanf(fid,'%i %i %i %i %i %i %i %i %i\n', 8);
N_NODE = A(1);
N_ELEM = A(2);    
N_LOAD = A(3); 
N_PRE_DISP = A(4);
N_TRAC = A(5);
N_MAT = A(6);
N_BLOAD = A(7);
Model2D = A(8); % Model2D = 1: Plane Stress; Model2D = 2: Plane Strain

Ng = 2;
ShapeOrder = 1;

NNODE_ELE = 4;
DOF_NODE = 2; %Number of degrees of freedom per node
EDOF = NNODE_ELE*DOF_NODE; %number of degrees of freedom per element

% initialize vectors
COORDS = zeros(N_NODE,NDIM);
ELEM_NODE = zeros(NNODE_ELE,N_ELEM); 
ELEM_STIFF = zeros(N_ELEM,2); % (E,nu)    
material = zeros(N_MAT,3); %(index, E,nu,t)
ELEM_AREA = zeros(N_ELEM,1); % t
ELEM_LOAD = zeros(N_ELEM,2); % (bx, by)
bodyload = zeros(N_BLOAD,2); % (bx, by)
FORCE_NODE = zeros(N_LOAD,NDIM); % first entry is the node, second entry is the DOF
FORCE_VAL = zeros(N_LOAD,1);
DISP_NODE = zeros(N_PRE_DISP,NDIM);  % first entry is the node, second entry is the DOF
DISP_VAL = zeros(N_PRE_DISP,1); 
TRAC_ELE = zeros(N_TRAC,2); % first entry is the element, second entry is the local edge number
TRAC_VAL = zeros(N_TRAC,3); % first entry is the magnitude, the other two entries correspond to the direction unit vector (ex, ey)

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
    val = fscanf(fid,'%f %f \n',2);
    bodyload(i,1) = val(1); 
    bodyload(i,2) = val(2); 
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
   for j=1:2
        ELEM_STIFF(i,j) = material(line(1),j);
   end
   ELEM_LOAD(i,1) = bodyload(line(2),1);
   ELEM_LOAD(i,2) = bodyload(line(2),2);
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

% get prescribed traction (convection)
for i=1:N_TRAC
   line = fscanf(fid, '%i %i %f %f %f \n',5);
   TRAC_ELE(i,1)=line(1);
   TRAC_ELE(i,2)=line(2);
   TRAC_VAL(i,1)=line(3);
   TRAC_VAL(i,2)=line(4);   
   TRAC_VAL(i,3)=line(5);   
end 

fclose(fid);
end


