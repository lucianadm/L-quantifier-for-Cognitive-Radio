clear
clc
E=0.1;
N = 1e6; % note the large sample size.

for i=1:10000
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z1=ceil(E-abs(X1-X2));
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z2=ceil(E-abs(X1-X2));
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z3=ceil(E-abs(X1-X2));
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z5=ceil(E-abs(X1-X2));
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z6=ceil(E-abs(X1-X2));
X1 = rand(N,1); % UNIFORM samples
X2 = rand(N,1);
Z7=ceil(E-abs(X1-X2));

y1=(2*Z1-Z2).*Z3.*Z1;
y2=(Z5-Z6).*Z7.*Z5;

yy1=sum(y1);
yy2=sum(y2);
yy(i)=yy1./yy2;
end
histogram(yy)