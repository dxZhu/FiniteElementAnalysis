%
% Initialization of the required matrices
p1 = zeros(NNODE_ELE+1,N_ELEM) ;
p2 = zeros(NNODE_ELE+1,N_ELEM) ;
nd = zeros(NNODE_ELE);
for iel=1:N_ELEM
    for i=1:NNODE_ELE
        nd(i)=ELEM_NODE(i,iel);       % extract connected node for (iel)-th element
        p1(i,iel)=COORDS(nd(i),1);    % extract x value of the node
        p2(i,iel)=COORDS(nd(i),2);    % extract y value of the node
    end
    p1(i+1,iel) = COORDS(nd(1),1);
    p2(i+1,iel) = COORDS(nd(1),2);
end

%% Plot Flux at the nodes
figure;
plot(p1,p2,'r')
hold on;
quiver(COORDS(:,1),COORDS(:,2),NodalFlux(:,1),NodalFlux(:,2));
title('Nodal Flux vector')
axis equal;
hold on;