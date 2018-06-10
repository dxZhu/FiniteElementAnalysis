function [stress, strain] = GetElementFluxVector(I_ELEM, NNODE_ELE, DOF_NODE, ...
            NDIM, COORDS, ELEM_NODE, ELEM_STIFF, ShapeOrder , Ng, ... 
            Model2D,  location, UUR)



if location == 1
    %% Evaluating flux at guass points (same used to obtain field approximation
  
end

if location == 0 
    %% Evaluating flux at the center of isoparametric element
  
    
end
   
end