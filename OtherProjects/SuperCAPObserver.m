clear all;close all;
t = 0:1/12000:30;                    % ����ʱ��
C_real = 9;                          % ʵ�ʵ�����ֵ 9F
r_real = 0.3;                        % ʵ�ʵ��������� 0.3 ŷķ
C = 7;                               % ���������ֵ
r = 2;                               % ��������������ֵ
r_max_set = 3;                       % ����������������ֵ
r_min_set = 0.05;                    % ���������������Сֵ
UCAP_Init_real = 2;                  % ʵ�ʵ��ݵ�ѹ�ĳ�ʼֵ
UCAP_Init_set = 5;                   % ������ݵ�ѹ�ĳ�ʼֵ
Uo_set_bias = 0.2*sin(2*t);          % ��ѹ����ƫ��
Uo_set_noise_var = 0.1;              % ��ѹ������������
I_measure_bias = 0.5*sin(3*t)';      % ��������ƫ��
I_measure_noise_var = 0.5;           % ����������������
alpha_max = 0.1;                     % ���ѧϰ��
alpha_min = 0.001;                   % ��Сѧϰ��
deltaU_max = 0.01;                   % ��ѹ���仯ֵ

% �������������ѹ
Uo_ideal=5+exp(-0.15*t).*sin(5*t)+t;
tempIndex = floor(length(Uo_ideal)/3*2);
Uo_ideal(tempIndex:length(Uo_ideal))=...
    12*ones(size(Uo_ideal(tempIndex:length(Uo_ideal))));
clear tempIndex;


% ����ϵͳ�����
Uo_real = Uo_ideal + Uo_set_bias + Uo_set_noise_var * rand(size(Uo_ideal));
[Real_UCAP, Real_I] = calcRealSystem(Uo_real, C_real, r_real, UCAP_Init_real, t);
% ��Ӳ�������
Measure_I = Real_I + I_measure_bias + I_measure_noise_var * rand(size(Real_I));
% ����ͼ��
figure(1);plot(t,Uo_real,t,Real_UCAP,t,Real_I,t,Measure_I);
legend('����Uo(V)','״̬UCAP(V)','���I(A)','��������(A)');
title('����������ϵͳ����Ӧ');
% ����ƽ���۲����Ĺ۲���
[UCAP_Obs_Ordinary,I_Obs_Ordinary] = calcOrdinaryObserver(Uo_ideal, C, ...
    r, UCAP_Init_set, 1/12000);
% ����ͼ��
figure(2);plot(t,Real_UCAP,t,UCAP_Obs_Ordinary,t,I_Obs_Ordinary,t,Real_I);
legend('ʵ��״̬UCAP(V)','�۲�״̬UCAP(V)','�۲����ֵ(A)','ʵ�ʵ���ֵ(A)');
title('ƽ��״̬�۲����Ĺ۲���');
clear UCAP_Obs_Ordinary I_Obs_Ordinary;
% ����������۲����Ĺ۲���
[UCAP_Obs_Luenberger,I_Obs_Luenberger] = calcLuenbergerObserver(Uo_ideal, ...
    Measure_I, C, r, UCAP_Init_set, 1/12000, -0.5);
% ����ͼ��
figure(3);plot(t,Real_UCAP,t,UCAP_Obs_Luenberger,t,I_Obs_Luenberger,...
    t,Real_I,t,Measure_I);
legend('ʵ��״̬UCAP(V)','�۲�״̬UCAP(V)','�۲����ֵ(A)','ʵ�ʵ���ֵ(A)',...
    '��������ֵ(A)');
title('������״̬�۲����Ĺ۲���');
clear UCAP_Obs_Luenberger I_Obs_Luenberger;
% ƽ���۲������������Ż�
[UCAP_Obs_Ordinary_Optimized, I_Obs_Ordinary_Optimized,...
    r_Obs_Ordinary_Optimized, alpha_Ordinary_Optimized] = ...
    calcOrdinaryObserver_Optimized(Uo_ideal, Measure_I, C, r, ...
    UCAP_Init_set, 1/12000, 50, 20);
% ����ͼ��
figure(4);
subplot(3,1,1);
plot(t,Real_UCAP,t,UCAP_Obs_Ordinary_Optimized,...
    t,I_Obs_Ordinary_Optimized,t,Real_I);
legend('ʵ��״̬UCAP(V)','�۲�״̬UCAP(V)','�۲����ֵ(A)','ʵ�ʵ���ֵ(A)');
title('״̬�۲����Ĺ۲��������ֵ֮��Ĳ��');
subplot(3,1,2);
plot(t,r_real*ones(size(Real_UCAP)),t,r_Obs_Ordinary_Optimized);
legend('��ʵ����','�۲�����');ylim([0 3.2]);
title('�Ż����������ʵ����֮��Ĳ��');
subplot(3,1,3);
plot(t,alpha_Ordinary_Optimized);
legend('ѧϰ��');ylim([0 0.1]);title('�Ż�����ѧϰ�ʱ仯���');
suptitle('�����Ż�ƽ��״̬�۲����Ĺ۲���');
% clear UCAP_Obs_Ordinary_Optimized r_Obs_Ordinary_Optimized alpha_Ordinary_Optimized;
% ������۲������������Ż�
[UCAP_Obs_Luenberger_Optimized, I_Obs_Luenberger_Optimized, ...
    r_Obs_Luenberger_Optimized, alpha_Luenberger_Optimized] = ...
    calcLuenbergerObserver_Optimized(Uo_ideal, Measure_I, C, r, ...
    UCAP_Init_set, 1/12000, 50, 20, -0.5);
% ����ͼ��
figure(5);
subplot(3,1,1);
plot(t,Real_UCAP,t,UCAP_Obs_Luenberger_Optimized,...
    t,I_Obs_Luenberger_Optimized,t,Real_I,t,Measure_I);
legend('ʵ��״̬UCAP(V)','�۲�״̬UCAP(V)','�۲����ֵ(A)','ʵ�ʵ���ֵ(A)',...
    '��������ֵ(A)');
title('״̬�۲����Ĺ۲��������ֵ֮��Ĳ��');
subplot(3,1,2);
plot(t,r_real*ones(size(Real_UCAP)),t,r_Obs_Luenberger_Optimized);
legend('��ʵ����','�۲�����');ylim([0 3.2]);
title('�Ż����������ʵ����֮��Ĳ��');
subplot(3,1,3);
plot(t,alpha_Luenberger_Optimized);
legend('ѧϰ��');ylim([0 0.1]);title('�Ż�����ѧϰ�ʱ仯���');
suptitle('�����Ż�������״̬�۲����Ĺ۲���');
clear UCAP_Obs_Luenberger_Optimized I_Obs_Luenberger_Optimized ;
clear r_Obs_Luenberger_Optimized alpha_Luenberger_Optimized;


% ����ʵ��ϵͳ��Ϊ
function [UCAP, I] = calcRealSystem(Uo_real, C_real, r_real, UCAP_Init, t)
    % ��Σ�  ʵ�������ѹ������ֵ������ֵ�����ݵ�ѹ�ĳ�ʼֵ�����ݶ�Ӧʱ���
    % ����ֵ�����ݵ�ѹ������
    if length(Uo_real) ~= length(t)
        disp(length(Uo_real));
        disp(length(t));
        error('Please set the length of Uo and t as the same!');
    end
    % ����״̬�ռ���ʽ
    A = -1/(r_real*C_real);B=-A;C=-1/r_real;D=-C;
    sys = ss(A,B,C,D);
    % ������Ӧ
    [I,~,UCAP]=lsim(sys,Uo_real,t,UCAP_Init);
end
% ����ƽ���۲������
function [UCAP_obs, I_obs] = calcOrdinaryObserver(Uo_ideal, C, ...
    r, UCAP_Init, deltaT)
    % ��Σ�  ���������ѹ������ֵ������ֵ�����ݵ�ѹ�ĳ�ʼֵ�����㲽��
    % ����ֵ�����ݵ�ѹ�۲�ֵ�������۲�ֵ
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    I_obs(1) = 0;
    % ����۲���
    for index = 1:length(Uo_ideal)-1
        ucap_dot = (Uo_ideal(index)-UCAP_obs(index))/(r*C);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1) = (Uo_ideal(index)-UCAP_obs(index))/r;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
    end
end
% �޷�����
function x = clamp(x1,min_x,max_x)
    if x1 < min_x
        x = min_x;
    else
        if x1 > max_x
            x = max_x;
        else
            x = x1;
        end
    end
end
% ���������Ż���ƽ���۲������
function [UCAP_obs, I_obs, r_obs, r_alpha] = calcOrdinaryObserver_Optimized(...
    Uo_ideal,I_measurement, C, r, UCAP_Init, deltaT, sample1, sample2)
    % ��Σ�  ���������ѹ����������ֵ������ֵ������ֵ�����ݵ�ѹ�ĳ�ʼֵ��
    %           ���㲽������¼���ݵ�ļ���������Ż��ļ��
    % ����ֵ�����ݵ�ѹ�۲�ֵ������۲�ֵ��ѧϰ��
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    r_obs = zeros(size(Uo_ideal));
    r_obs(1) = r;
    r_alpha = zeros(size(Uo_ideal));
    r_alpha(1) = 0;
    deltaU = zeros(1, sample2);
    I_sample = zeros(1, sample2);
    % ��ȡ��Ҫʹ�õ�ȫ�ֱ���
    r_max_set = evalin('base', 'r_max_set');
    r_min_set = evalin('base', 'r_min_set');
    alpha_min = evalin('base', 'alpha_min');
    alpha_max = evalin('base', 'alpha_max');
    deltaU_max = evalin('base', 'deltaU_max');
    % ����۲���
    for index = 1:length(Uo_ideal)-1
        ucap_dot = (Uo_ideal(index)-UCAP_obs(index))/(r_obs(index)*C);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1) = ucap_dot * C;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
        r_obs(index+1)=r_obs(index);
        % �ж��Ƿ�ʼ�����Ż�
        if mod(index, sample1) == 0
            % ��¼����
            new_index=mod(index/sample1, sample2);
            if new_index ~= 0
                deltaU(new_index)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(new_index)=I_measurement(index);
            else
                deltaU(sample2)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(sample2)=I_measurement(index);
                % ��Ҫ����һ�������Ż�(������С����)
                r=I_sample*deltaU'/(I_sample*I_sample');
                if r > r_max_set || r < r_min_set
                    r_alpha(index+1) = alpha_min;
                    r = clamp(r,r_min_set,r_max_set);
                else
                    r_alpha(index+1) = alpha_min+(alpha_max-alpha_min)*...
                        clamp(1-(abs(r-r_obs(index)/(r_max_set))),0,1)*...
                        clamp((abs(max(deltaU)-min(deltaU))/deltaU_max),0,1);
                end
                r_obs(index+1)=(1-r_alpha(index+1))*r_obs(index)+...
                    r_alpha(index+1)*r;
                r_obs(index+1) = clamp(r_obs(index+1),r_min_set,r_max_set);
            end
        else
            % ����Ҫ�Ż���������Ҫ����һ�ε�����۲�ֵ�ᵽ��һ��
            r_obs(index+1)=r_obs(index);
            r_alpha(index+1)=r_alpha(index);
        end
    end
end
% ����������۲������
function [UCAP_obs, I_obs] = calcLuenbergerObserver(Uo_ideal, I_measurement, ...
    C, r, UCAP_Init, deltaT, G)
    % ��Σ�  ���������ѹ����������ֵ������ֵ������ֵ�����ݵ�ѹ�ĳ�ʼֵ
    %           ���㲽�����۲�������
    % ����ֵ�����ݵ�ѹ�۲�ֵ�������۲�ֵ
    if length(Uo_ideal) ~= length(I_measurement)
        disp(length(Uo_real));
        disp(length(I_measurement));
        error('Please set the length of Uo and I as the same!');
    end
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    % ����۲���
    sys_A = -1/(r*C);sys_B=-sys_A;sys_C=-1/r;sys_D=-sys_C;
    fprintf("A-GC=\n");disp((sys_A-G*sys_C));
    for index = 1:length(Uo_ideal)-1
        ucap_dot = (sys_A-G*sys_C)*UCAP_obs(index)+ ...
            (sys_B-G*sys_D)*Uo_ideal(index)+G*I_measurement(index);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1)=ucap_dot*C;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
    end
end
% ���������Ż���������۲������
function [UCAP_obs, I_obs, r_obs, r_alpha] = calcLuenbergerObserver_Optimized(...
    Uo_ideal,I_measurement, C, r, UCAP_Init, deltaT, sample1, sample2, G)
    % ��Σ�  ���������ѹ����������ֵ������ֵ������ֵ�����ݵ�ѹ�ĳ�ʼֵ��
    %           ���㲽������¼���ݵ�ļ���������Ż��ļ�����۲�������
    % ����ֵ�����ݵ�ѹ�۲�ֵ�������۲�ֵ������۲�ֵ��ѧϰ��
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    r_obs = zeros(size(Uo_ideal));
    r_obs(1) = r;
    r_alpha = zeros(size(Uo_ideal));
    r_alpha(1) = 0;
    deltaU = zeros(1, sample2);
    I_sample = zeros(1, sample2);
    % ��ȡ��Ҫʹ�õ�ȫ�ֱ���
    r_max_set = evalin('base', 'r_max_set');
    r_min_set = evalin('base', 'r_min_set');
    alpha_min = evalin('base', 'alpha_min');
    alpha_max = evalin('base', 'alpha_max');
    deltaU_max = evalin('base', 'deltaU_max');
    % ����۲���
    for index = 1:length(Uo_ideal)-1
        sys_A = -1/(r_obs(index)*C);sys_B=-sys_A;sys_C=-1/r_obs(index);sys_D=-sys_C;
        ucap_dot = (sys_A-G*sys_C)*UCAP_obs(index)+ ...
            (sys_B-G*sys_D)*Uo_ideal(index)+G*I_measurement(index);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1) = ucap_dot*C;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
        r_obs(index+1)=r_obs(index);
        % �ж��Ƿ�ʼ�����Ż�
        if mod(index, sample1) == 0
            % ��¼����
            new_index=mod(index/sample1, sample2);
            if new_index ~= 0
                deltaU(new_index)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(new_index)=I_measurement(index);
            else
                deltaU(sample2)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(sample2)=I_measurement(index);
                % ��Ҫ����һ�������Ż�(������С����)
                r=I_sample*deltaU'/(I_sample*I_sample');
                if r > r_max_set || r < r_min_set
                    r_alpha(index+1) = alpha_min;
                    r = clamp(r,r_min_set,r_max_set);
                else
                    r_alpha(index+1) = alpha_min+(alpha_max-alpha_min)*...
                        clamp(1-(abs(r-r_obs(index)/(r_max_set))),0,1)*...
                        clamp((abs(max(deltaU)-min(deltaU))/deltaU_max),0,1);
                end
                r_obs(index+1)=(1-r_alpha(index+1))*r_obs(index)+...
                    r_alpha(index+1)*r;
                r_obs(index+1) = clamp(r_obs(index+1),r_min_set,r_max_set);
            end
        else
            % ����Ҫ�Ż���������Ҫ����һ�ε�����۲�ֵ�ᵽ��һ��
            r_obs(index+1)=r_obs(index);
            r_alpha(index+1)=r_alpha(index);
        end
    end
end
