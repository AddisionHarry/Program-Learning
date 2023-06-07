% 输入系统的状态空间表达式
A=[0,1;20.6,0];
B=[0;1];
C=[1,0];
D=0;
open_sys=ss(A,B,C,D);
% 期望极点位置
p1 = [-1.8+2.4i,-1.8-2.4i]; % 直接使用状态反馈时的反馈系统极点
p2 = [-8,-8];               % 使用状态观测器时的观测器极点
% 判断系统能控、能观性
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
% 系统可控时可随意配置极点
if flag_controllable
    % 直接使用状态反馈时计算状态反馈矩阵
    K = place(A, B, p1);
    fprintf("The state feedback matrix K equals \n\n");
    disp(K);
    if flag_observable
        % 使用状态观测器时的观测器极点
        L=acker(A', C', p2)';
        fprintf("The output feedback matrix L equals \n\n");
        disp(L);
    end
end

% place 函数既能计算 SISO 系统的极点配置问题, 也能计算 MIMO 系统
% 当要配置极点中包含多于 rank(B) 重极点的时候必须使用 acker, 但是该函数
%   只用 SISO 系统