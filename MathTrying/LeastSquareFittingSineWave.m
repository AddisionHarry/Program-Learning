clear all;close all;
% 实验参数
CurveParam_A = 6;               % 正弦幅值
CurveParam_W = 9;               % 正弦角频率
CurveParam_InitPhase = 2*pi/3;  % 正弦初相位
CurveParam_DC = -2;             % 直流分量
NoiseVariance = 1.5;            % 观测噪声方差
InitParam = [20, 5, -pi, 3];    % 给程序指定的初始值, 顺序A,w,phi,c
lb = [5, 5, -pi, -4];           % 给程序指定的参数下限, 顺序A,w,phi,c
ub = [20, 10, pi, 4];           % 给程序指定的参数上限, 顺序A,w,phi,c

experiment_index = 2; % 输入 1、2 或者 3, 本文件三个实验同时只实现其中一个
figureindex = 1;
if experiment_index == 1
    % 做六次全局拟合实验,效果不好，怀疑是选择的点数、观测周期以及初值不合理
    fit_time = [0.5, 1.2, 1.5, 2, 3, 4];        % 六次比较的观测时长
    fit_pointsnum = [15, 20, 25, 30, 40, 50];   % 六次比较的采样点数
    for index = 1 : length(fit_time)
        figure(figureindex);figureindex = figureindex + 1;
        % 输入一段被观测原始数据
        t = 0 : fit_time(index) / fit_pointsnum(index) : fit_time(index);
        IdealCurve = CurveParam_DC + CurveParam_A * sin(CurveParam_W * t ...
            + CurveParam_InitPhase);
        subplot(3,2,1);plot(t, IdealCurve);title('输入的真实待拟合曲线');
        % 在原始数据上叠加噪声得到观测到的曲线
        ObserveData = IdealCurve + NoiseVariance * randn(size(IdealCurve));
        subplot(3,2,2);plot(t, ObserveData);title('输入的实际被观测曲线');
        % 使用高斯-牛顿法做非线性最小二乘法拟合参数
        error = @(Param) Param(1) * sin(Param(2) * t + Param(3)) + ...
            Param(4) - ObserveData;
        Param = lsqnonlin(error, InitParam, lb, ub);
        disp(Param);
        Curve = Param(1,1) * sin(Param(1,2) * t + Param(1,3)) + Param(1,4);
        subplot(3,2,3);plot(t,Curve,t,ObserveData,t,IdealCurve);
        title('拟合出曲线的效果');
        % 绘制长时间以后两条曲线的误差
        longtime = 0 : 0.01 : 40;
        RealCurve = CurveParam_A * sin(CurveParam_W * longtime + ...
            CurveParam_InitPhase) + CurveParam_DC;
        FittedCurve = Param(1,1) * sin(Param(1,2) * longtime + ...
            Param(1,3)) + Param(1,4);
        subplot(3,2,4);plot(longtime,RealCurve,longtime,FittedCurve);
        title('长时间后理想曲线和拟合取消的误差');
        % 打印信息
        info = ['采样点数', num2str(fit_pointsnum(index)), newline, ...
            '采样时长', num2str(fit_time(index)), 's', newline, ...
            '真实信息 A = ', num2str(CurveParam_A), '   w = ', ...
            num2str(CurveParam_W), newline, ...
            '             InitPhase = ', num2str(CurveParam_InitPhase),...
            '   DC = ', num2str(CurveParam_DC), newline, ...
            '拟合信息 A = ', num2str(Param(1,1)), '   w = ', ...
            num2str(Param(1,2)), newline, ...
            '             InitPhase = ', num2str(Param(1,3)),...
            '   DC = ', num2str(Param(1,4))];
        annotation('textbox', [.2 .05 .6 .3],'String', info);
    end
elseif experiment_index == 2
    % 做一次随时间增长的逐次拟合
    Time = 15;           % 观测总时长
    SamplePoints = 1500; % 总采样点数
    StartPoints = 65;    % 开始拟合的点数位置
    % 生成观测曲线
    t = 0 : Time / SamplePoints : Time;
    IdealCurve = CurveParam_A * sin(CurveParam_W * t + ...
        CurveParam_InitPhase) + CurveParam_DC;
    ObserveCurve = IdealCurve + NoiseVariance * randn(size(IdealCurve));
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,ObserveCurve,'LineWidth',1);hold on;
    plot(t,IdealCurve,'LineWidth',2);hold off;
    legend('Observe','Real');title('实际曲线和观测曲线');
    % 从指定点点开始逐个增加点进行拟合
    FitCurve = zeros(1, length(t));
    FitCurve(1, 1 : StartPoints) = ObserveCurve(1, 1 : StartPoints);
    % 准备记录拟合参数
    FittedParam = zeros(length(t), 4);
    for index = 2 : StartPoints
        FittedParam(index, :) = InitParam(1, :);
    end
    for iteration = StartPoints : 1 : length(t)
        tempt = t(1, 1 : iteration);
        % 使用观测到的数据做非线性最小二乘拟合
        tempObserveData = ObserveCurve(1, 1 : iteration);
        error = @(Param) Param(1) * sin(Param(2) * tempt + Param(3)) + ...
            Param(4) - tempObserveData;
        % 上一次观测的参数结果可以作为下一次的初始值
        if iteration == StartPoints
            Param = lsqnonlin(error, InitParam, lb, ub);
        else
            Param = lsqnonlin(error, Param, lb, ub);
        end
        % 相位角的角度限制允许跨圈
        lb(1, 3) = Param(1, 3) - pi;ub(1, 3) = Param(1, 3) + pi;
        % 使用拟合出的结果计算下一时刻的函数值，但是最后一个计算周期不需要
        if iteration ~= length(t)
            NextTime = iteration / SamplePoints * Time;
            FitCurve(1, iteration + 1) = Param(1, 1) * sin(Param(1, 2) * ...
                NextTime + Param(1, 3)) + Param(1, 4);
        end
        % 输出 记录本次观测的参数
        disp(Param);
        FittedParam(iteration, :) = Param;
    end
    % 绘制最终的拟合效果
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve,'LineWidth',1.5);hold on;
    plot(t,IdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted','Real');title('实际曲线和拟合曲线');
    % 绘制误差曲线的变化
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve - IdealCurve);title('拟合误差');
    % 拟合结果和期望结果分别积分以后作比较
    figure(figureindex);figureindex = figureindex + 1;
    DerivativedFitCurve = zeros(size(FitCurve));
    DerivativedIdealCurve = zeros(size(IdealCurve));
    for index = 2 : length(IdealCurve)
        DerivativedFitCurve(1, index) = DerivativedFitCurve(1, index - 1)...
            + FitCurve(1, index);
        DerivativedIdealCurve(1, index) = DerivativedIdealCurve(1, index - 1)...
            + IdealCurve(1, index);
    end
    plot(t,DerivativedFitCurve,'LineWidth',1.5);hold on;
    plot(t,DerivativedIdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted-Integrated','Real-Integrated');
    title('实际曲线和拟合曲线分别积分后的结果');
    % 绘制拟合参数的变化
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FittedParam(:,1),t,FittedParam(:,2),...
        t,FittedParam(:,3),t,FittedParam(:,4));
    legend('A','w','phi','c');title('拟合参数的变化');
elseif experiment_index == 3
    % 尝试观测并拟合积分
    Time = 15;           % 观测总时长
    SamplePoints = 1500; % 总采样点数
    StartPoints = 65;    % 开始拟合的点数位置
    % 生成观测曲线
    t = 0 : Time / SamplePoints : Time;
    IdealCurve = zeros(1, length(t));
    for index = 2 : length(IdealCurve)
        IdealCurve(1, index) = IdealCurve(1, index - 1) + ...
            Time / SamplePoints * (CurveParam_A * sin(CurveParam_W * ...
            t(1, index - 1) + CurveParam_InitPhase) + CurveParam_DC);
    end
    ObserveCurve = IdealCurve + NoiseVariance * randn(size(IdealCurve));
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,ObserveCurve,'LineWidth',1);hold on;
    plot(t,IdealCurve,'LineWidth',2);hold off;
    legend('Observe','Real');title('实际曲线和观测曲线');
    % 从指定点点开始逐个增加点进行拟合
    FitCurve = zeros(1, length(t));
    FitCurve(1, 1 : StartPoints) = ObserveCurve(1, 1 : StartPoints);
    % 准备记录拟合参数
    FittedParam = zeros(length(t), 4);
    for index = 2 : StartPoints
        FittedParam(index, :) = InitParam(1, :);
    end
    for iteration = StartPoints : 1 : length(t)
        tempt = t(1, 1 : iteration);
        % 使用观测到的数据做非线性最小二乘拟合
        tempObserveData = ObserveCurve(1, 1 : iteration);
        error = @(Param) -Param(1) / Param(2) * sin(Param(2) * tempt + ...
            Param(3)) + Param(4) * tempt - tempObserveData;
        % 上一次观测的参数结果可以作为下一次的初始值
        if iteration == StartPoints
            Param = lsqnonlin(error, InitParam, lb, ub);
        else
            Param = lsqnonlin(error, Param, lb, ub);
        end
        % 相位角的角度限制允许跨圈
        lb(1, 3) = Param(1, 3) - pi;ub(1, 3) = Param(1, 3) + pi;
        % 使用拟合出的结果计算下一时刻的函数值，但是最后一个计算周期不需要
        if iteration ~= length(t)
            NextTime = iteration / SamplePoints * Time;
            FitCurve(1, iteration + 1) = -Param(1, 1) / Param(1, 2) * ...
                sin(Param(1, 2) * NextTime + Param(1, 3)) + Param(1, 4) * ...
                NextTime;
        end
        % 输出 记录本次观测的参数
        disp(Param);
        FittedParam(iteration, :) = Param;
    end
    % 绘制最终的拟合效果
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve,'LineWidth',1.5);hold on;
    plot(t,IdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted','Real');title('实际曲线和拟合曲线');
    % 绘制误差曲线的变化
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve - IdealCurve);title('拟合误差');
    % 拟合结果和期望结果分别微分以后作比较
    figure(figureindex);figureindex = figureindex + 1;
    DerivativedFitCurve = Param(1, 1) * sin(Param(1, 2) * ...
        t + Param(1, 3)) + Param(1, 4);
    DerivativedIdealCurve = CurveParam_A * sin(CurveParam_W * t + ...
        CurveParam_InitPhase) + CurveParam_DC;
    plot(t,DerivativedFitCurve,'LineWidth',1.5);hold on;
    plot(t,DerivativedIdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted-Derivatived','Real-Derivatived');
    title('实际曲线和拟合曲线分别微分后的结果');
    % 绘制拟合参数的变化
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FittedParam(:,1),t,FittedParam(:,2),...
        t,FittedParam(:,3),t,FittedParam(:,4));
    legend('A','w','phi','c');title('拟合参数的变化');
end
