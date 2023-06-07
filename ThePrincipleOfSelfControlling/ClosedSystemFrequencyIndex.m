clear all;close all;
% Create the closed system transfer function.
s=tf('s');
Gopen=4*6.25*(s+0.5)*(s+0.1)/(s*(s+0.5)*(s+5)*(s+0.01));
Gclosed=feedback(Gopen,1,-1);

% Draw the bode chart of the system
figure(1);
w=logspace(-1,2,100);
bode(Gclosed,w);
grid on;

% Calculate the bandwith of the closed system.
wb=bandwidth(Gclosed);
j=sqrt(-1);
% To prove this frequency is exactly the bandwidth frequency.
abs(polyval(Gclosed.Numerator{1},j*wb)/polyval(Gclosed.Denominator{1},j*wb))
fprintf('The bandwidth of the system is %f rad/s.\n',wb)

% Calculate the peak gain and peak frequency.
% Mr --- The peak gain of the closed system
% Wr --- The peak frequency of the closed system
[Mr,Wr]=getPeakGain(Gclosed);
fprintf("The peak gain of the closed system is %f.\n",Mr);
fprintf("The peak frequency of the closed system is %f rad/s.\n",Wr);

% Give the poles of the closed system.
poles=roots(Gclosed.Denominator{1});
fprintf("The poles of the close-loop system are:\n");
disp(poles);

% Calculate the step response.
t=[0:0.000001:20];
y=step(Gclosed,t);
% Plot the step response.
figure(2);
plot(t,y);
title('Unit Step Response of the Closed-Loop System');
grid on;
[OSValue,OSIndex]=max(y);
ys=y(length(t));
% Get the peak parameters.
Mp=(OSValue-ys)/ys*100;
tp=t(OSIndex);
fprintf('The unit step response overshoot is %f%%.\n',Mp);
fprintf('The unit step response peak time is %fs.\n',tp);
% Get the raise time of the step response.
tr=t(find(y>=ys,1,'first')); % From the index 1.
fprintf('The unit step response raise time is %fs.\n',tr);

% Give the impulse response.
yi=impulse(Gclosed,t);
% Plot the step response.
figure(3);
plot(t,yi);
title('Unit Impulse Response of the Closed-Loop System');
grid on;