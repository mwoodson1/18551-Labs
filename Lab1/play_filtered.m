formatSpec = '%f';
fid = fopen('tmp_modulated.txt','r');
A = fscanf(fid,formatSpec);

soundsc(A);