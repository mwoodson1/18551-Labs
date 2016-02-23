function printHyperplane(fileName,model)

weightedSV = bsxfun(@times,model.SupportVectors,model.Alpha);

hyperplane = -sum(weightedSV);
norm(hyperplane)
fp = fopen(fileName,'w');

fprintf(fp,'Bias\n%f\n\nSupport Vector\n',-model.Bias);

for i = 1:length(hyperplane)
    fprintf(fp,'%f ',hyperplane(i));
end

fclose(fp);