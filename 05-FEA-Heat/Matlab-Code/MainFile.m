%clc; clear all;close all

%% ME 471 / AE 420 / 
% Programming Assignment #5: 2D Heat Transfer


% Variables definition

% nnode_ele, the (integer) number of nodes per element
% node_dof, the (integer) number of degrees of freedom per node
% edof, the (integer) number of degrees of freedom per element

% filename = 'input_Incropera_4_3.dat'; % Model does not use symmetry (Example 1)
%filename = 'inputExample10_4_QUAD.dat'; %Lecture notes
%filename = 'Example4-4-Incropera.dat'; %(Example 2)
%filename = 'LShapeMesh.dat'; %(Example 3)
%filename = 'ChimneyNew.dat'; %(Example4)
%filename = 'inputhw7.dat'; % Homework 7 input file

%% BEFORE COMMITING YOUR CODE: comment all lines above and keep the line below uncommented!
%% We will modify the line below to read our test input file
filename = 'input.dat';
NDIM = 2; % Dimension of the problem (NDIM =2 geometry varying in x and y)

%% Read Input File
[N_NODE,N_ELEM,N_LOAD,N_PRE_DISP,...
       COORDS, ELEM_LOAD, ELEM_NODE,ELEM_STIFF, ELEM_AREA,...
       FORCE_NODE,FORCE_VAL,DISP_NODE,DISP_VAL, ...
       N_TRAC_c, TRAC_c_ELE, TRAC_c_VAL, N_TRAC_q, TRAC_q_ELE, TRAC_q_VAL, ...
       NNODE_ELE, DOF_NODE, EDOF, Ng, ShapeOrder] = ReadInput(filename,NDIM); 

%%  Equation Module
% Your code here

%% Assemble Module 


% %% Solve Module

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
[FluxAtIntegrationPoints, FluxAtCentroid, NodalFlux, MagnitudeNodalFlux, ...
    NodalGradT, MagnitudeGradT] = EvaluateFieldGradient(N_ELEM, N_NODE, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, UUR);
        
%% Print Post Processing Results
% DO NOT MODIFY
PrintPostProcessingResults(FluxAtIntegrationPoints,...
    FluxAtCentroid, NodalFlux,MagnitudeNodalFlux)

%% IMPORTANT INFORMATION: YOU HAVE TO DELETE OR COMMENT THE FOLLOWING LINE BEFORE COMMIT

% PlotVectors
%  
% PlotFieldonMesh(COORDS',ELEM_NODE, UUR, 'Temperature');
%  
% PlotFieldonMesh(COORDS',ELEM_NODE, MagnitudeNodalFlux, 'Magnitude Nodal Flux (Extrapolated)');

