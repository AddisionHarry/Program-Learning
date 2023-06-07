clear all;close all;
% 以匿名函数形式定义微分方程, 注意是列向量
f = @(t,x) [x(2); (1-x(1)^2)*x(2)-x(1)];
[t,x]=ode45(f,[0,50],[1;0]);
% 绘制解曲线
figure(1);
plot(t,x(:,1),t,x(:,2));xlabel('t');ylabel('x(t)');
title('微分方程的解曲线');legend('x(t)', 'x''(t)');
% 绘制相平面曲线
figure(2);
plot(x(:,1),x(:,2));xlabel('x(t)');ylabel('x''(t)');
title('微分方程的相平面曲线');
