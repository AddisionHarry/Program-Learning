clear all;close all;
% ������������ʽ����΢�ַ���, ע����������
f = @(t,x) [x(2); (1-x(1)^2)*x(2)-x(1)];
[t,x]=ode45(f,[0,50],[1;0]);
% ���ƽ�����
figure(1);
plot(t,x(:,1),t,x(:,2));xlabel('t');ylabel('x(t)');
title('΢�ַ��̵Ľ�����');legend('x(t)', 'x''(t)');
% ������ƽ������
figure(2);
plot(x(:,1),x(:,2));xlabel('x(t)');ylabel('x''(t)');
title('΢�ַ��̵���ƽ������');
