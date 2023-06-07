% �����ͻ����ԣ��趨���Ҳ�����
close all;
t=0:0.01:20;
A=[5;10;20;40];
y=A.*sin(t); % ����������ֵ��ͬ�������ź�
hysteresis = 8;
out = zeros(length(A),length(t));
% ��������ź��µ����
for index = 1:length(A)
    out(index,1)=0;
    in_last = 0;
    for tk = 2:length(t)
        if tk == 2
            [out(index,tk), in_last, out(index,tk-1)] = Hysteresis(...
                y(index,tk), in_last, out(index,tk-1), 0, hysteresis);
        else
            [out(index,tk), in_last, out(index,tk-1)] = Hysteresis(...
                y(index,tk), in_last, out(index,tk-1), out(index,tk-2), hysteresis);
        end
    end
end
figure(1);
for index = 1:length(A)
    subplot(2,2,index);plot(t,y(index,:),t,out(index,:));
    ylim([-45 45]);legend('����', '���');
end
suptitle('���Ҳ����ź����ͻ����Ե������������');
figure(2);
for index = 1:length(A)
    subplot(2,2,index);plot(y(index,:), out(index,:));
    xlabel('����');ylabel('���');xlim([-45 45]);ylim([-45 45]);
end
suptitle('�ͻ����Ե����������ϵ');


% ADDME: This function could simulate system with hysteresis feature
function [now, in_last, now_last] = Hysteresis(in, in_last, now, now_last, hysteresis)
    if in > in_last
        if now > now_last
            now = in - hysteresis / 2;
        elseif in > now_last + hysteresis / 2
            now = in - hysteresis / 2;
        else
            now = now_last;
        end
    elseif in < in_last
        if now < now_last
            now = in + hysteresis / 2;
        elseif in < now_last - hysteresis / 2
            now = in + hysteresis / 2;
        else
            now = now_last;
        end
    end
    in_last = in;
    now_last = now;
end