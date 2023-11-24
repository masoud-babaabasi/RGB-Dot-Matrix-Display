len=length(milad);
my_file=fopen('milad_24hex.txt','w');
for i=1:len
    for j=1:8
    if(get_mode(milad(i))==1) fprintf(my_file,'0xff0000,');
    else fprintf(my_file,'0x000000,');
    end
    milad(i)=floor(milad(i)/2);
    end
    fprintf(my_file,'\n');
end
fclose(my_file);