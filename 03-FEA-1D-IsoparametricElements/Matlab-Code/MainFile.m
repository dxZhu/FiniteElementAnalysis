
clc; clear all;

%% ME 471 / AE 420 / 
% Programming Assignment #2: 1D elastostatic FE code
% includes: 
% - isoparametric linear and quadratic elements
% - numerical integration using Ng = 1,2,3,4 gauss points
% - DLOAD function for user-defined body load b(x)
% - UMAT function for user-defined elasticity modulus E(x)


% Variables definition

% nnode_ele, the (integer) number of nodes per element
% node_dof, the (integer) number of degrees of freedom per node
% edof, the (integer) number of degrees of freedom per element


filename = 'input.dat'; 
%% Read Input File
    
[N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
        NNODE_ELE, DOF_NODE, EDOF, Ng,ShapeOrder] = ReadInput(filename);
    
%%  Equation Module
% Your code here




%% Print EQ_NUM
% DO NOT MODIFY!
PrintEQNUM(EQ_NUM);

%% Assemble Module 
% Your code here




%% Print Matrices
% DO NOT MODIFY!
PrintMatrices(KPP,KPF,KFP,KFF);

%% Solve Module
% Your code here




%% Print Solution
% DO NOT MODIFY!
PrintSolution(UF,PP,UUR,PUR);
