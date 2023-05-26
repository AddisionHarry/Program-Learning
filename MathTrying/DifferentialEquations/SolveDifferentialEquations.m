syms k m g;
v=dsolve('Dv+k/m*v-g=0','v(0)=0','t');

v1=matlabFunction(subs(v,[k m g],[0.07 1 9.8]));
v2=matlabFunction(subs(v,[k m g],[0.1 1 9.8]));
v3=matlabFunction(subs(v,[k m g],[0.2 1 9.8]));
v4=matlabFunction(subs(v,[k m g],[0.5 1 9.8]));
v5=matlabFunction(subs(v,[k m g],[1 1 9.8]));

time=0:0.01:100;
v1plot=v1(time);
v2plot=v2(time);
v3plot=v3(time);
v4plot=v4(time);
v5plot=v5(time);

plot(v1plot,'r');hold on
plot(v2plot,'b');hold on
plot(v3plot,'g');hold on
plot(v4plot,'k');hold on
plot(v5plot,'c');hold on
grid on;
hold off;
xlim([0 11000])
ylim([0 150])
xticks([0 20 40 60 80 100]*100)
xticklabels({0 20 40 60 80 100})
yticks([0 25 50 75 100 125 150])
str={'\tau=0.07','\tau=0.1','\tau=0.2','\tau=0.5','\tau=1'};
legend(str,'fontsize',10);
title('不同时间常数下的运动速度-时间曲线','fontsize',12)
xlabel('运动时间t/s','fontsize',12);
ylabel('运动速度v/(m/s)','fontsize',12);
