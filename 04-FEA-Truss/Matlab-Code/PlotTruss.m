
function PlotTruss(N_ELEM,COORDS,ELEM_NODE,UUR)

% 2) plot undeformed and deformed shape of truss
figure(1);
clf;
disp_max=sum(max(abs(UUR)));        % maximum displacement value
bar_lengthv=zeros(N_ELEM,1);       % list of undeformed element lengths
for i=1:N_ELEM
	x1=COORDS(ELEM_NODE(1,i),1);
	y1=COORDS(ELEM_NODE(1,i),2);
	x2=COORDS(ELEM_NODE(2,i),1);
	y2=COORDS(ELEM_NODE(2,i),2);
	bar_lengthv(i)=sqrt((x2-x1)^2+(y2-y1)^2);
end
bar_length_max=max(bar_lengthv);    % maximum element length
ampli=0.2*bar_length_max/disp_max;  % "pre-computed" displacement amplification factor
%sprintf(' suggested amplification factor = %10.4f\n',ampli)
%ampli2=input(' enter the amplification factor (enter 0 to leave unchanged) ...')
%if ampli2 > 0
%	ampli=ampli2;
%end
axis equal;             % use same scale for x- and y-axes
xlabel('x (m)')
ylabel('y (m)')
title(strcat(' undeformed and deformed shapes - disp. amplification factor = ',num2str(ampli)))
hold on;
for i=1:N_ELEM  % loop over elements and display undeformed (blue-dashed) and deformed (red-solid) shapes
	xx_undef(1)=  COORDS(ELEM_NODE(1,i),1);      % undeformed x-coordinate of node 1
	xx_undef(2)=  COORDS(ELEM_NODE(2,i),1);     % undeformed x-coordinate of node 2
	yy_undef(1)=  COORDS(ELEM_NODE(1,i),2);     % undeformed y-coordinate of node 1
	yy_undef(2)=  COORDS(ELEM_NODE(2,i),2);      % undeformed y-coordinate of node 2
	xx_def(1)=xx_undef(1) + ampli*UUR(ELEM_NODE(1,i),1);   % deformed x-coordinate of node 1
	xx_def(2)=xx_undef(2) + ampli*UUR(ELEM_NODE(2,i),1);   % deformed x-coordinate of node 2
	yy_def(1)=yy_undef(1) + ampli*UUR(ELEM_NODE(1,i),2);   % deformed y-coordinate of node 1
	yy_def(2)=yy_undef(2) + ampli*UUR(ELEM_NODE(2,i),2);   % deformed y-coordinate of node 2
	plot(xx_undef,yy_undef,'bo--',xx_def,yy_def,'ro-','linewidth',2)
end
hold off;

end