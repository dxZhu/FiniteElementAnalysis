 function [N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       NNODE_ELE, DOF_NODE, EDOF, Ng, ShapeOrder] = ReadInput(filen)

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

% read first line
A = fscanf(fid,'%i %i %i %i %i %i /n', 6);
N_NODE = A(1);
N_ELEM = A(2);    
N_LOAD = A(3); 
N_PRE_DISP = A(4);
Ng = A(5);
ShapeOrder = A(6);

if (ShapeOrder == 1) NNODE_ELE = 2; %Number of nodes per element
elseif (ShapeOrder == 2) NNODE_ELE = 3;
elseif (ShapeOrder == 3) NNODE_ELE = 4;
else disp('Only linear, quadratic and cubic functions are implemented. Exit');return;
end

if (Ng > 4) disp('Max Ng = 4. Exit');return;
end
DOF_NODE = 1; %Number of degrees of freedom per node
EDOF = NNODE_ELE*DOF_NODE; %number of degrees of freedom per element


% initialize vectors
COORDS = zeros(N_NODE,1);
ELEM_NODE = zeros(NNODE_ELE,N_ELEM); 
ELEM_STIFF = zeros(N_ELEM,1);
ELEM_LOAD = zeros(N_ELEM,1);
FORCE_NODE = zeros(N_LOAD,1); 
FORCE_VAL = zeros(N_LOAD,1);
DISP_NODE = zeros(N_PRE_DISP,1); 
DISP_VAL = zeros(N_PRE_DISP,1); 

for i=1:N_NODE
   line = fscanf(fid, '%f %f /n',1);
   COORDS(i,1) = line(1);
end


for i=1:N_ELEM
   
   for j=1:NNODE_ELE
        line = fscanf(fid, '%f',1);
        ELEM_NODE(j,i)=line(1);
   end
   
   line = fgetl(fid);
   linet = regexp(line, '[  |\t]', 'split');
   [a,b]=size(linet);

   j = 1;
   pos = 1;
   while j<=b
       
        string = linet{j};
        if isempty(string) 
            j=j+1;
            continue; 
        end
        if (pos==1)
            if strcmp('UMAT',string)
                ELEM_STIFF(i,1) = sqrt(-1); 
            else
                ELEM_STIFF(i,1) = str2double(string);
            end  
            pos = pos +1;
            j = j +1;
        elseif (pos==2)
            if strcmp('DLOAD',string)
                ELEM_LOAD(i,1) = sqrt(-1); 
            else
                ELEM_LOAD(i,1) = str2double(string);
            end  
            pos = pos +1;
            j = j + 1;
        end    
   end
   
end


% get prescribed force values and corresponding node num
for i=1:N_LOAD
   line = fscanf(fid, '%i %f /n',2);
   FORCE_NODE(i,1)=line(1);
   FORCE_VAL(i,1)=line(2);
end
% get prescribed displacement values and corresponding node num
for i=1:N_PRE_DISP
   line = fscanf(fid, '%i %f /n',2);  
   DISP_NODE(i,1)=line(1);
   DISP_VAL(i,1)=line(2);
end                         

fclose(fid);
end


