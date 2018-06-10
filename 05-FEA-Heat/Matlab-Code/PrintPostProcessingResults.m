function PrintPostProcessingResults(FluxAtIntegrationPoints,...
    FluxAtCentroid, NodalFlux,MagnitudeNodalFlux)

fprintf('FLUX AT INTEGRATION POINTS\n')
disp(FluxAtIntegrationPoints);
fout = fopen('FluxAtIntegrationPoints.dat','w');
for i = 1:size(FluxAtIntegrationPoints,1)
    fprintf(fout, '%12.8f ', FluxAtIntegrationPoints(i,:));
    fprintf(fout, '\n');
end


fprintf('FLUX AT CENTROID\n')
disp(FluxAtCentroid);
fout = fopen('FluxAtCentroid.dat','w');
for i = 1:size(FluxAtCentroid,1)
    fprintf(fout, '%12.8f ', FluxAtCentroid(i,:));
    fprintf(fout, '\n');
end

fprintf('FLUX AT NODES\n')
disp(NodalFlux);
fout = fopen('FluxAtNodes.dat','w');
for i = 1:size(NodalFlux,1)
    fprintf(fout, '%12.8f ', NodalFlux(i,:));
    fprintf(fout, '\n');
end

fprintf('FLUX MAGNITUDE AT NODES\n')
disp(MagnitudeNodalFlux);
fout = fopen('FluxMagnitudeAtNodes.dat','w');
for i = 1:size(MagnitudeNodalFlux,1)
    fprintf(fout, '%12.8f ', MagnitudeNodalFlux(i,:));
    fprintf(fout, '\n');
end

end
