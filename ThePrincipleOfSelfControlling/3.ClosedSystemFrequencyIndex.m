clear all;
% Create the closed system transfer function.
s=tf('s');
Gopen=6.78/(s*(s^2+4*s+8))
Gclosed=feedback(Gopen,1,-1);

% Draw the bode chart of the system
w=logspace(-1,2,100);
bode(Gclosed,w);
grid on;

% Calculate the bandwith of the closed system.
wb=bandwidth(Gclosed);
j=sqrt(-1);
abs(polyval(Gclosed.Numerator{1},j*wb)/polyval(Gclosed.Denominator{1},j*wb))
fprintf('The bandwidth of the system is %f rad/s.\n',wb)

% Calculate the peak gain and peak frequency.
% Mr --- The peak gain of the closed system
% Wr --- The peak frequency of the closed system
[Mr,Wr]=getPeakGain(Gclosed);
fprintf("The peak gain of the closed system is %f.\n",Mr);
fprintf("The peak frequency of the closed system is %f rad/s.\n",Wr);

% Give the poles of the closed system.
roots(Gclosed.Denominator{1})

% Calculate the step response.
t=[0:0.000001:20];
y=step(Gclosed,t);
% Plot the step response.
figure;
plot(t,y);
grid on;
[OSValue,OSIndex]=max(y);
ys=y(length(t));
% Get the peak parameters.
Mp=(OSValue-ys)/ys*100;
tp=t(OSIndex);
fprintf('The unit step response overshoot is %f%%.',Mp);
fprintf('The unit step response peak time is %fs\n.',tp);
% Get the raise time of the step response.
tr=t(find(y>=ys,1,'first')); % From the index 1.
fprintf('The unit step response raise time is %fs\n.',tr);

% Give the impulse response.
yi=impulse(Gclosed,t);
% Plot the step response.
figure;
plot(t,yi);
grid on;