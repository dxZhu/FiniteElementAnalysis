clc; clear all;close all

%% ME 471 / AE 420 / 
% Programming Assignment #6: 3D Elasticity
% Prof. Mariana Silva

% Variables definition

% nnode_ele, the (integer) number of nodes per element
% node_dof, the (integer) number of degrees of freedom per node
% edof, the (integer) number of degrees of freedom per element



%%To give to students
filename='Patch.dat'; %Example1
%filename = 'inputTortoTextBook.dat';%Example2
%filename='PatchPointForce.dat';%Example3
%filename='Patch-1Element.dat';%Example4
%filename='CantileverFine.dat';

%% BEFORE COMMITING YOUR CODE: comment all lines above and keep the line below uncommented!
%% We will modify the line below to read our test input file
% filename = 'input.dat';
NDIM = 2; % Dimension of the problem (NDIM =2 geometry varying in x and y)


%% Read Input File
[N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ELEM_AREA,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       N_TRAC, TRAC_ELE, TRAC_VAL, ...
       NNODE_ELE, DOF_NODE, EDOF, Ng, ShapeOrder, Model2D] = ReadInput(filename,NDIM); 


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
   
   

%% Post-Processing
[StressAtIntegrationPoints, StrainAtIntegrationPoints, StressAtCentroid, StrainAtCentroid,...
    StressAtNodes, StrainAtNodes, TpAtIntegrationPoints,VMAtIntegrationPoints, TpAtCentroid, TpAtNodes, VMAtNodes] ...
    = EvaluateFieldGradient(N_ELEM, N_NODE, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, Model2D, UUR);

%% Print Post Processing Results
% DO NOT MODIFY

PrintPostProcessingResults(StressAtIntegrationPoints, ...
    StrainAtIntegrationPoints, StressAtCentroid, StrainAtCentroid, ...
    StressAtNodes, StrainAtNodes, TpAtIntegrationPoints, ...
    VMAtIntegrationPoints, TpAtCentroid, TpAtNodes, VMAtNodes)

%% IMPORTANT INFORMATION: YOU HAVE TO DELETE OR COMMENT THE FOLLOWING LINE BEFORE COMMIT
% PlotDeformedConfiguration(NNODE_ELE, N_ELEM,COORDS,ELEM_NODE,UUR);  
% PlotVectors(NNODE_ELE, N_ELEM, ELEM_NODE, COORDS, UUR)
% 
% PlotFieldonMesh(COORDS',ELEM_NODE, StressAtNodes(:,1), 'sigma x');
% PlotFieldonMesh(COORDS',ELEM_NODE, StressAtNodes(:,4), 'sigma y');
% PlotFieldonMesh(COORDS',ELEM_NODE, VMAtNodes(:), 'Von Mises');
% 