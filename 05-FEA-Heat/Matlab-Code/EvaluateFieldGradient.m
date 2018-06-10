function [FluxAtIntegrationPoints, ElementFlux, NodalFlux, MagnitudeNodalFlux,...
            NodalGradT, MagnitudeGradT] = ...
            EvaluateFieldGradient(N_ELEM, N_NODE, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, UUR)

%% Get the Flux at the integration points
location = 1; % evaluate at the gauss points used for the solution
FluxAtIntegrationPoints = zeros(N_ELEM*NDIM*Ng,NDIM);

for I_ELEM=1:N_ELEM
    [flux, gradT] = GetElementHeatFluxVector(I_ELEM, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, location, UUR);
        for j=1:NDIM*Ng
        pos =  (I_ELEM-1)*NDIM*Ng + j;
        FluxAtIntegrationPoints(pos,:)=flux(:,j);
     end
end

%% Get the Flux at the centroid for extrapolation to nodes
location = 0; % evaluate at the center of the element
ElementFlux = zeros(N_ELEM,NDIM);

for I_ELEM=1:N_ELEM
    [flux, gradT] = GetElementHeatFluxVector(I_ELEM, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, location, UUR);
    ElementFlux(I_ELEM,:)=flux'; 
    ElementGradT(I_ELEM,:)=gradT';
end

%% Extrapolate flux at nodes

scale = zeros(N_NODE,1); % vector containing the number of elements attached to each node
NodalFlux = zeros(N_NODE,NDIM); % matrix with the nodal values of the heat flux vector
NodalGradT = zeros(N_NODE,NDIM);
MagnitudeNodalFlux = zeros(N_NODE,1);
MagnitudeGradT = zeros(N_NODE,1);

for I_ELEM=1:N_ELEM
    for j=1:NNODE_ELE
        node = ELEM_NODE(j,I_ELEM);
        scale(node) = scale(node) + 1;
        NodalFlux(node,:) = NodalFlux(node,:) + ElementFlux(I_ELEM,:);
        NodalGradT(node,:)  = NodalGradT(node,:)  + ElementGradT(I_ELEM,:);
    end
end


for i=1:N_NODE
    for j=1:NDIM
        NodalFlux(i,j) = NodalFlux(i,j)/scale(i);
        NodalGradT(i,j) = NodalGradT(i,j)/scale(i);
    end
    MagnitudeNodalFlux(i) = sqrt(NodalFlux(i,1)^2+NodalFlux(i,2)^2);
    MagnitudeGradT(i) = sqrt(NodalGradT(i,1)^2+NodalGradT(i,2)^2);
end

