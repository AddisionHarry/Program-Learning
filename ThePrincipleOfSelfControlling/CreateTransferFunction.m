% The numenator of the system transfer function
num=[1];
% The denominator of the system
den=[1,4,6,0];
% The Transder function of the system
G0=tf(num,den)

% Create transfer function from rational fractional
s=tf('s');
G1=5*(s+1)/(s+5)

% Multiply the funsfer functions.
G2=G0*G1

% Create the tranfer function from Rational integer multiplication
p=conv([1,2],[3,4]);
G3=tf([1],conv(p,[0,1,2]))

% Create transfer function from zeros and poles.
z=[1,2,3];
p=[4,4,8,9];
k=1;
G4=zpk(z,p,k)

% Invert between the forms.
[z,p,k]=tf2zp(num,den);
zpk(z,p,k)

% Convert the transfer function into time domain
num=[2 1 6 10 24];
den=[1 10 35 50 24];
tf(num,den)
[r,p,k]=residue(num,den) % The time domain is c(t) = k + \sum r_k * \exp{p_k*t}.
[r,p,k]=residue(1,[conv(conv([1 -1],[1 4]),[2 3 1])]) % 1/((s-1)(s+4)(2s^2+3s+1))