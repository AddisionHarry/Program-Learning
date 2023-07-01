clear all;close all;
t = 0:1/12000:30;                    % 仿真时间
C_real = 9;                          % 实际电容容值 9F
r_real = 0.3;                        % 实际电容组内阻 0.3 欧姆
C = 7;                               % 程序电容容值
r = 2;                               % 程序电容组内阻初值
r_max_set = 3;                       % 程序电容组内阻最大值
r_min_set = 0.05;                    % 程序电容组内阻最小值
UCAP_Init_real = 2;                  % 实际电容电压的初始值
UCAP_Init_set = 5;                   % 软件电容电压的初始值
Uo_set_bias = 0.2*sin(2*t);          % 电压设置偏置
Uo_set_noise_var = 0.1;              % 电压设置噪声方差
I_measure_bias = 0.5*sin(3*t)';      % 电流测量偏置
I_measure_noise_var = 0.5;           % 电流测量噪声方差
alpha_max = 0.1;                     % 最大学习率
alpha_min = 0.001;                   % 最小学习率
deltaU_max = 0.01;                   % 电压最大变化值

% 给定理论输入电压
Uo_ideal=5+exp(-0.15*t).*sin(5*t)+t;
tempIndex = floor(length(Uo_ideal)/3*2);
Uo_ideal(tempIndex:length(Uo_ideal))=...
    12*ones(size(Uo_ideal(tempIndex:length(Uo_ideal))));
clear tempIndex;


% 计算系统的输出
Uo_real = Uo_ideal + Uo_set_bias + Uo_set_noise_var * rand(size(Uo_ideal));
[Real_UCAP, Real_I] = calcRealSystem(Uo_real, C_real, r_real, UCAP_Init_real, t);
% 添加测量噪声
Measure_I = Real_I + I_measure_bias + I_measure_noise_var * rand(size(Real_I));
% 绘制图像
figure(1);plot(t,Uo_real,t,Real_UCAP,t,Real_I,t,Measure_I);
legend('输入Uo(V)','状态UCAP(V)','输出I(A)','测量电流(A)');
title('给定输入下系统的响应');
% 计算平凡观测器的观测结果
[UCAP_Obs_Ordinary,I_Obs_Ordinary] = calcOrdinaryObserver(Uo_ideal, C, ...
    r, UCAP_Init_set, 1/12000);
% 绘制图像
figure(2);plot(t,Real_UCAP,t,UCAP_Obs_Ordinary,t,I_Obs_Ordinary,t,Real_I);
legend('实际状态UCAP(V)','观测状态UCAP(V)','观测电流值(A)','实际电流值(A)');
title('平凡状态观测器的观测结果');
clear UCAP_Obs_Ordinary I_Obs_Ordinary;
% 计算龙伯格观测器的观测结果
[UCAP_Obs_Luenberger,I_Obs_Luenberger] = calcLuenbergerObserver(Uo_ideal, ...
    Measure_I, C, r, UCAP_Init_set, 1/12000, -0.5);
% 绘制图像
figure(3);plot(t,Real_UCAP,t,UCAP_Obs_Luenberger,t,I_Obs_Luenberger,...
    t,Real_I,t,Measure_I);
legend('实际状态UCAP(V)','观测状态UCAP(V)','观测电流值(A)','实际电流值(A)',...
    '测量电流值(A)');
title('龙伯格状态观测器的观测结果');
clear UCAP_Obs_Luenberger I_Obs_Luenberger;
% 平凡观测器离线数据优化
[UCAP_Obs_Ordinary_Optimized, I_Obs_Ordinary_Optimized,...
    r_Obs_Ordinary_Optimized, alpha_Ordinary_Optimized] = ...
    calcOrdinaryObserver_Optimized(Uo_ideal, Measure_I, C, r, ...
    UCAP_Init_set, 1/12000, 50, 20);
% 绘制图像
figure(4);
subplot(3,1,1);
plot(t,Real_UCAP,t,UCAP_Obs_Ordinary_Optimized,...
    t,I_Obs_Ordinary_Optimized,t,Real_I);
legend('实际状态UCAP(V)','观测状态UCAP(V)','观测电流值(A)','实际电流值(A)');
title('状态观测器的观测输出和真值之间的差距');
subplot(3,1,2);
plot(t,r_real*ones(size(Real_UCAP)),t,r_Obs_Ordinary_Optimized);
legend('真实内阻','观测内阻');ylim([0 3.2]);
title('优化后内阻和真实内阻之间的差距');
subplot(3,1,3);
plot(t,alpha_Ordinary_Optimized);
legend('学习率');ylim([0 0.1]);title('优化过程学习率变化情况');
suptitle('离线优化平凡状态观测器的观测结果');
% clear UCAP_Obs_Ordinary_Optimized r_Obs_Ordinary_Optimized alpha_Ordinary_Optimized;
% 龙伯格观测器离线数据优化
[UCAP_Obs_Luenberger_Optimized, I_Obs_Luenberger_Optimized, ...
    r_Obs_Luenberger_Optimized, alpha_Luenberger_Optimized] = ...
    calcLuenbergerObserver_Optimized(Uo_ideal, Measure_I, C, r, ...
    UCAP_Init_set, 1/12000, 50, 20, -0.5);
% 绘制图像
figure(5);
subplot(3,1,1);
plot(t,Real_UCAP,t,UCAP_Obs_Luenberger_Optimized,...
    t,I_Obs_Luenberger_Optimized,t,Real_I,t,Measure_I);
legend('实际状态UCAP(V)','观测状态UCAP(V)','观测电流值(A)','实际电流值(A)',...
    '测量电流值(A)');
title('状态观测器的观测输出和真值之间的差距');
subplot(3,1,2);
plot(t,r_real*ones(size(Real_UCAP)),t,r_Obs_Luenberger_Optimized);
legend('真实内阻','观测内阻');ylim([0 3.2]);
title('优化后内阻和真实内阻之间的差距');
subplot(3,1,3);
plot(t,alpha_Luenberger_Optimized);
legend('学习率');ylim([0 0.1]);title('优化过程学习率变化情况');
suptitle('离线优化龙伯格状态观测器的观测结果');
clear UCAP_Obs_Luenberger_Optimized I_Obs_Luenberger_Optimized ;
clear r_Obs_Luenberger_Optimized alpha_Luenberger_Optimized;


% 计算实际系统行为
function [UCAP, I] = calcRealSystem(Uo_real, C_real, r_real, UCAP_Init, t)
    % 入参：  实际输入电压、电容值、内阻值、电容电压的初始值、数据对应时间点
    % 返回值：电容电压、电流
    if length(Uo_real) ~= length(t)
        disp(length(Uo_real));
        disp(length(t));
        error('Please set the length of Uo and t as the same!');
    end
    % 构建状态空间表达式
    A = -1/(r_real*C_real);B=-A;C=-1/r_real;D=-C;
    sys = ss(A,B,C,D);
    % 计算响应
    [I,~,UCAP]=lsim(sys,Uo_real,t,UCAP_Init);
end
% 计算平凡观测器输出
function [UCAP_obs, I_obs] = calcOrdinaryObserver(Uo_ideal, C, ...
    r, UCAP_Init, deltaT)
    % 入参：  理论输入电压、电容值、内阻值、电容电压的初始值、运算步长
    % 返回值：电容电压观测值、电流观测值
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    I_obs(1) = 0;
    % 计算观测器
    for index = 1:length(Uo_ideal)-1
        ucap_dot = (Uo_ideal(index)-UCAP_obs(index))/(r*C);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1) = (Uo_ideal(index)-UCAP_obs(index))/r;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
    end
end
% 限幅函数
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
% 计算离线优化的平凡观测器输出
function [UCAP_obs, I_obs, r_obs, r_alpha] = calcOrdinaryObserver_Optimized(...
    Uo_ideal,I_measurement, C, r, UCAP_Init, deltaT, sample1, sample2)
    % 入参：  理论输入电压、电流测量值、电容值、内阻值、电容电压的初始值、
    %           运算步长、记录数据点的间隔、离线优化的间隔
    % 返回值：电容电压观测值、内阻观测值、学习率
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    r_obs = zeros(size(Uo_ideal));
    r_obs(1) = r;
    r_alpha = zeros(size(Uo_ideal));
    r_alpha(1) = 0;
    deltaU = zeros(1, sample2);
    I_sample = zeros(1, sample2);
    % 获取想要使用的全局变量
    r_max_set = evalin('base', 'r_max_set');
    r_min_set = evalin('base', 'r_min_set');
    alpha_min = evalin('base', 'alpha_min');
    alpha_max = evalin('base', 'alpha_max');
    deltaU_max = evalin('base', 'deltaU_max');
    % 计算观测器
    for index = 1:length(Uo_ideal)-1
        ucap_dot = (Uo_ideal(index)-UCAP_obs(index))/(r_obs(index)*C);
        UCAP_obs(index+1) = UCAP_obs(index) + ucap_dot * deltaT;
        I_obs(index+1) = ucap_dot * C;
        if UCAP_obs(index+1) < 0
            UCAP_obs(index+1) = 0;
        end
        r_obs(index+1)=r_obs(index);
        % 判断是否开始离线优化
        if mod(index, sample1) == 0
            % 记录数据
            new_index=mod(index/sample1, sample2);
            if new_index ~= 0
                deltaU(new_index)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(new_index)=I_measurement(index);
            else
                deltaU(sample2)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(sample2)=I_measurement(index);
                % 需要进行一次离线优化(线性最小二乘)
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
            % 不需要优化，但是需要把上一次的内阻观测值搬到下一次
            r_obs(index+1)=r_obs(index);
            r_alpha(index+1)=r_alpha(index);
        end
    end
end
% 计算龙伯格观测器输出
function [UCAP_obs, I_obs] = calcLuenbergerObserver(Uo_ideal, I_measurement, ...
    C, r, UCAP_Init, deltaT, G)
    % 入参：  理论输入电压、电流测量值、电容值、内阻值、电容电压的初始值
    %           运算步长、观测器增益
    % 返回值：电容电压观测值、电流观测值
    if length(Uo_ideal) ~= length(I_measurement)
        disp(length(Uo_real));
        disp(length(I_measurement));
        error('Please set the length of Uo and I as the same!');
    end
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    % 计算观测器
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
% 计算离线优化的龙伯格观测器输出
function [UCAP_obs, I_obs, r_obs, r_alpha] = calcLuenbergerObserver_Optimized(...
    Uo_ideal,I_measurement, C, r, UCAP_Init, deltaT, sample1, sample2, G)
    % 入参：  理论输入电压、电流测量值、电容值、内阻值、电容电压的初始值、
    %           运算步长、记录数据点的间隔、离线优化的间隔、观测器增益
    % 返回值：电容电压观测值、电流观测值、内阻观测值、学习率
    UCAP_obs = zeros(size(Uo_ideal));
    UCAP_obs(1) = UCAP_Init;
    I_obs = zeros(size(Uo_ideal));
    r_obs = zeros(size(Uo_ideal));
    r_obs(1) = r;
    r_alpha = zeros(size(Uo_ideal));
    r_alpha(1) = 0;
    deltaU = zeros(1, sample2);
    I_sample = zeros(1, sample2);
    % 获取想要使用的全局变量
    r_max_set = evalin('base', 'r_max_set');
    r_min_set = evalin('base', 'r_min_set');
    alpha_min = evalin('base', 'alpha_min');
    alpha_max = evalin('base', 'alpha_max');
    deltaU_max = evalin('base', 'deltaU_max');
    % 计算观测器
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
        % 判断是否开始离线优化
        if mod(index, sample1) == 0
            % 记录数据
            new_index=mod(index/sample1, sample2);
            if new_index ~= 0
                deltaU(new_index)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(new_index)=I_measurement(index);
            else
                deltaU(sample2)=Uo_ideal(index)-UCAP_obs(index);
                I_sample(sample2)=I_measurement(index);
                % 需要进行一次离线优化(线性最小二乘)
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
            % 不需要优化，但是需要把上一次的内阻观测值搬到下一次
            r_obs(index+1)=r_obs(index);
            r_alpha(index+1)=r_alpha(index);
        end
    end
end
