
function PlotFieldonMesh(coords,elem_node,data, name)

%  data:  array containing the node data to plot

nel = length(elem_node(1,:)) ;                  % number of elements
nnel = 4;                                      % number of nodes per element
%
% Initialization of the required matrices
p1 = zeros(nnel,nel) ;
p2 = zeros(nnel,nel) ;
profile = zeros(nnel,nel) ;
nd = zeros(nnel);
%
for iel=1:nel
    for i=1:nnel
        nd(i)=elem_node(i,iel);       % extract connected node for (iel)-th element
        p1(i,iel)=coords(1,nd(i));    % extract x value of the node
        p2(i,iel)=coords(2,nd(i));    % extract y value of the node
        profile(i,iel) = data(nd(i)) ;     % extract  node value
    end
end
% Plotting the FEM mesh and profile of the given component
f3=figure;
set(f3,'name','Postprocessing','numbertitle','off') ;
plot(p1,p2,'k')
patch(p1,p2,profile)
title(name);
%colormap(jet);
colorbar;
daspect([1 1 1]);
axis off
% axes1 = axes('Visible','off','Parent',f3,'DataAspectRatio',[1 1 1],...
%     'CLim',[min(data) max(data)]);
%colorbar('peer',axes1);



return

end


% %% Plot average temperature in each element
% figure(1);
% clf;
% axis off;
% hold on;
% caxis([min(UUR) max(UUR)]);
% 
% for ielem=1:N_ELEM 
%     uavg = 0;
%     for i=1:NNODE_ELE
%         uel(i) = UUR(ELEM_NODE(i,ielem));
%         uavg = uavg + uel(i);
%         x(i) = COORDS(ELEM_NODE(i,ielem),1);
%         y(i) = COORDS(ELEM_NODE(i,ielem),2);      
%     end
%     uavg=uavg/NNODE_ELE;
%     fill(x,y,uavg);
% end
% title('Temperature distribution')
% colorbar;
% axis equal;
% hold on;