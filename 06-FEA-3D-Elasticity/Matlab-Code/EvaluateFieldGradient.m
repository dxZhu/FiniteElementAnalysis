function [StressAtIntegrationPoints, StrainAtIntegrationPoints, ...
        StressAtCentroid, StrainAtCentroid,StressAtNodes ,StrainAtNodes, ...
        TpAtIntegrationPoints,VMAtIntegrationPoints, TpAtCentroid, TpAtNodes, VMAtNodes] = ...
            EvaluateFieldGradient(N_ELEM, N_NODE, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, Model2D,  UUR)

%% Get the Flux at the integration points and also the principal stresses
location = 1; % evaluate at the gauss points used for the solution
StressAtIntegrationPoints = zeros(N_ELEM*Ng*Ng,NDIM*NDIM);
StrainAtIntegrationPoints = zeros(N_ELEM*Ng*Ng,NDIM*NDIM);
TpAtIntegrationPoints = zeros(N_ELEM*Ng*Ng,3);
VMAtIntegrationPoints = zeros(N_ELEM*Ng*Ng,1);

for I_ELEM=1:N_ELEM
    [stress, strain] = GetElementFluxVector(I_ELEM, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, ... 
            Model2D,  location, UUR);
        
     e = ELEM_STIFF(I_ELEM,1);
     nu = ELEM_STIFF(I_ELEM,2);
     lambda = e*nu/((1+nu)*(1-2.*nu));
       
     for j=1:Ng*Ng
       pos =  (I_ELEM-1)*Ng*Ng + j;
       StressAtIntegrationPoints(pos,:)=stress(:,j);
       StrainAtIntegrationPoints(pos,:)=strain(:,j); 
       
       sigave = (stress(1,j)+stress(4,j))/2;
       radius = sqrt( ((stress(1,j)-stress(4,j))/2)^2 + stress(2,j)^2);
       
       TpAtIntegrationPoints(pos,1)=  sigave + radius;
       TpAtIntegrationPoints(pos,2)=  sigave - radius;
       if (Model2D == 1) 
            TpAtIntegrationPoints(pos,3)=0;
        elseif (Model2D == 2)        
            TpAtIntegrationPoints(pos,3)=lambda*(strain(1,j)+strain(4,j));
       end
        
       VMAtIntegrationPoints(pos) = sqrt( 0.5*(  (TpAtIntegrationPoints(pos,1)-TpAtIntegrationPoints(pos,2))^2 + ...
                                (TpAtIntegrationPoints(pos,1)-TpAtIntegrationPoints(pos,3))^2 + ...
                                (TpAtIntegrationPoints(pos,3)-TpAtIntegrationPoints(pos,2))^2   ) );
     end   
   
end

%% Get the Flux at the centroid for extrapolation to nodes
% Also evaluates the principal stresses and von mises stress at the
% centroid
location = 0; % evaluate at the center of the element
StrainAtCentroid = zeros(N_ELEM,NDIM*NDIM);
StressAtCentroid = zeros(N_ELEM,NDIM*NDIM);
TpAtCentroid = zeros(N_ELEM,3);

for I_ELEM=1:N_ELEM
    [stress, strain] = GetElementFluxVector(I_ELEM, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, ... 
            Model2D, location, UUR);
    StrainAtCentroid(I_ELEM,:)=strain'; 
    StressAtCentroid(I_ELEM,:)=stress'; 
    % principal stresses
    TpAtCentroid(I_ELEM,1)=(stress(1)+stress(4))/2 + sqrt( ((stress(1)-stress(4))/2)^2 + stress(2)^2);
    TpAtCentroid(I_ELEM,2)=(stress(1)+stress(4))/2 - sqrt( ((stress(1)-stress(4))/2)^2 + stress(2)^2);
    if (Model2D == 1) 
        TpAtCentroid(I_ELEM,3)=0;
    elseif (Model2D == 2)
        e = ELEM_STIFF(I_ELEM,1);
        nu = ELEM_STIFF(I_ELEM,2); 
        lambda = e*nu/((1+nu)*(1-2.*nu));
        TpAtCentroid(I_ELEM,3)=lambda*(strain(1)+strain(4));
    end
        
end

%% Extrapolate flux at nodes

scale = zeros(N_NODE,1); % vector containing the number of elements attached to each node
StressAtNodes = zeros(N_NODE,NDIM*NDIM); % matrix with the nodal values of the heat flux vector
StrainAtNodes = zeros(N_NODE,NDIM*NDIM);
TpAtNodes = zeros(N_NODE,3);
VMAtNodes = zeros(N_NODE,1);

for I_ELEM=1:N_ELEM
    for j=1:NNODE_ELE
        node = ELEM_NODE(j,I_ELEM);
        scale(node) = scale(node) + 1;
        StressAtNodes(node,:) = StressAtNodes(node,:) + StressAtCentroid(I_ELEM,:);
        StrainAtNodes(node,:)  = StrainAtNodes(node,:)  + StrainAtCentroid(I_ELEM,:);
        TpAtNodes(node,:) = TpAtNodes(node,:)+ TpAtCentroid(I_ELEM,:);
    end
end


for i=1:N_NODE
    for j=1:NDIM*NDIM
       StressAtNodes(i,j) = StressAtNodes(i,j)/scale(i);
       StrainAtNodes (i,j) = StrainAtNodes(i,j)/scale(i);       
    end
    TpAtNodes (i,:) = TpAtNodes(i,:)./scale(i);
    VMAtNodes(i) = sqrt( 0.5*(  (TpAtNodes(i,1)-TpAtNodes(i,2))^2 + ...
                                (TpAtNodes(i,1)-TpAtNodes(i,3))^2 + ...
                                (TpAtNodes(i,3)-TpAtNodes(i,2))^2   ) );
end

%%



