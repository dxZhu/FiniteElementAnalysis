function PlotDeformedConfiguration(NNODE_ELE, N_ELEM,COORDS,ELEM_NODE,UUR)

% 2) plot undeformed and deformed shape of truss
figure(1);
clf;
disp_max=sum(max(abs(UUR)));        % maximum displacement value
elsize=zeros(N_ELEM,1);       % list of undeformed element lengths

% Initialization of the required matrices
p1 = zeros(NNODE_ELE+1,N_ELEM) ;
p2 = zeros(NNODE_ELE+1,N_ELEM) ;
p1d = zeros(NNODE_ELE+1,N_ELEM) ;
p2d = zeros(NNODE_ELE+1,N_ELEM) ;
nd = zeros(NNODE_ELE);
for iel=1:N_ELEM
    for i=1:NNODE_ELE
        nd(i)=ELEM_NODE(i,iel);       % extract connected node for (iel)-th element
        p1(i,iel)=COORDS(nd(i),1);    % extract x value of the node
        p2(i,iel)=COORDS(nd(i),2);    % extract y value of the node
    end
    p1(i+1,iel) = COORDS(nd(1),1);
    p2(i+1,iel) = COORDS(nd(1),2);
    elsize(iel) = sqrt( (p1(2,iel)-p1(1,iel))^2 + (p2(2,iel)-p2(1,iel))^2 );
end

ampli=0.2*max(elsize)/disp_max;  
axis equal;             % use same scale for x- and y-axes
xlabel('x (m)')
ylabel('y (m)')
title(strcat(' undeformed and deformed shapes - disp. amplification factor = ',num2str(ampli)))
hold on;
for iel=1:N_ELEM  % loop over elements and display undeformed (blue-dashed) and deformed (red-solid) shapes
    for i=1:NNODE_ELE
        nd(i)=ELEM_NODE(i,iel);       % extract connected node for (iel)-th element
        p1d(i,iel)=COORDS(nd(i),1) + ampli* UUR(nd(i),1);    % extract x value of the node
        p2d(i,iel)=COORDS(nd(i),2) + ampli* UUR(nd(i),2);    % extract y value of the node
    end
    p1d(i+1,iel) = COORDS(nd(1),1) + ampli* UUR(nd(1),1);
    p2d(i+1,iel) = COORDS(nd(1),2) + ampli* UUR(nd(1),2);
end


plot(p1,p2,'bo--')
plot(p1d,p2d,'ro-','linewidth',2)


end