H = Num;
fid = fopen('filter.dat','wb');
fwrite(fid,H,'double');
fclose(fid);

x = wavread('hw1_noisy.wav');
fid = fopen('noisy.dat','wb');
fwrite(fid,x,'double');
fclose(fid);