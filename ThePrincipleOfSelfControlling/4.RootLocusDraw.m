clear all;
% Give the open-loop transfer function.
s=tf('s');
Gopen=(s+2.04)/(s*(s+1)*(s+8.18))
% Draw the root locus of the system.
rlocus(Gopen.Numerator{1},Gopen.Denominator{1});sgrid;

% Find the Root-Locus Gain and poles of the system at the specific point.
[K,p]=rlocfind(Gopen.Numerator{1},Gopen.Denominator{1})

% Give the poles of the closed system at the given toot locus gain K.
K=264;
poles=rlocus(Gopen.Numerator{1},Gopen.Denominator{1},K)

% Give the gain and poles of the closed system with the given closed pole.
ClosedPole=200000000;
[K,Poles]=rlocfind(Gopen.Numerator{1},Gopen.Denominator{1},ClosedPole)