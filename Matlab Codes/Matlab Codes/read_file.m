function output = read_file(address,len)
m=fopen(address,'r');
for i=1:len
s=fgetl(m);
a1=s(4);
a2=s(5);
if(a1>='0' && a1<='9')
a1=a1-48;end
if( a1=='A') a1=10;end
if( a1=='B') a1=11;end
if( a1=='C') a1=12;end
if( a1=='D') a1=13;end
if( a1=='E') a1=14;end
if( a1=='F') a1=15;end
if(a2>='0' && a2<='9')
a2=a2-48;end
if( a2=='A') a2=10;end
if( a2=='B') a2=11;end
if( a2=='C') a2=12;end
if( a2=='D') a2=13;end
if( a2=='E') a2=14;end
if( a2=='F') a2=15;end
output(i) = a1*16+a2;
end
fclose(m);

end

