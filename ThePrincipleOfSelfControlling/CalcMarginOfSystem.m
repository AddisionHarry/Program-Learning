clear all;close all;
% Create tranfer function.
s = tf('s');
Gopen = 4*6.25*(s+0.5)*(s+0.1)/(s*(s+0.5)*(s+5)*(s+0.01));

% Am --- Ampitude margin
% Pm --- Phase margin
% Wg --- Traverse frequency
% Wc --- Cutoff frequency
[Am,Pm,Wg,Wc]=margin(Gopen);
% Calculate where the logspace should be
Min=0;
Max=2;
if isfinite(Wg) && ~isequal(Wg,0)
    Min=min([Min,floor(log10(Wg))-1]);
    Max=max([Max,ceil(log10(Wg))+1]);
end
if isfinite(Wc) && ~isequal(Wc,0)
    Min=min([Min,floor(log10(Wc))-1]);
    Max=max([Max,ceil(log10(Wc))+1]);
end
[z,p]=tf2zp(Gopen.Numerator{1,1},Gopen.Denominator{1,1});
temp=-real([z',p']);
temp(temp==0)=[];
Min=min([Min,floor(log10(temp)-1)]);
Max=max([Max,ceil(log10(temp)+1)]);

fprintf('The ampitude margin of the system is %f dB\n', 20*log10(Am));
fprintf('\tThe cutoff frequency is %f rad/s\n', Wc);
fprintf('The phase margin of the system is %f degrees\n', Pm);
fprintf('\tThe traverse frequency is %f rad/s\n', Wg);

% Create a list of number with 100 numbers 
% arrange evenly between 10^0 and 10^4 in log space
w=logspace(Min,Max,100);

% Draw the bode chart of the system
figure(1);
bode(Gopen,w);
grid on;
% Draw the Nyquist of the system
figure(2);
nyquist(Gopen,w);
grid on;
% Draw the Root-Locus of the system
figure(3);
rlocus(Gopen);
grid on;
