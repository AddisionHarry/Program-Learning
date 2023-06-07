% ����ϵͳ��״̬�ռ���ʽ
A=[0,1;20.6,0];
B=[0;1];
C=[1,0];
D=0;
open_sys=ss(A,B,C,D);
% ��������λ��
p1 = [-1.8+2.4i,-1.8-2.4i]; % ֱ��ʹ��״̬����ʱ�ķ���ϵͳ����
p2 = [-8,-8];               % ʹ��״̬�۲���ʱ�Ĺ۲�������
% �ж�ϵͳ�ܿء��ܹ���
flag_controllable=(length(A)==rank(ctrb(A,B)));
flag_observable=(length(A)==rank(obsv(A,C)));
if flag_controllable
    fprintf("This system is controllable.\n");
else
    fprintf("This system is uncontrollable.\n");
end
if flag_observable
    fprintf("This system is observable.\n");
else
    fprintf("This system is unobservable.\n");
end
% ϵͳ�ɿ�ʱ���������ü���
if flag_controllable
    % ֱ��ʹ��״̬����ʱ����״̬��������
    K = place(A, B, p1);
    fprintf("The state feedback matrix K equals \n\n");
    disp(K);
    if flag_observable
        % ʹ��״̬�۲���ʱ�Ĺ۲�������
        L=acker(A', C', p2)';
        fprintf("The output feedback matrix L equals \n\n");
        disp(L);
    end
end

% place �������ܼ��� SISO ϵͳ�ļ�����������, Ҳ�ܼ��� MIMO ϵͳ
% ��Ҫ���ü����а������� rank(B) �ؼ����ʱ�����ʹ�� acker, ���Ǹú���
%   ֻ�� SISO ϵͳ