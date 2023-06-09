clear all;close all;
% ʵ�����
CurveParam_A = 6;               % ���ҷ�ֵ
CurveParam_W = 9;               % ���ҽ�Ƶ��
CurveParam_InitPhase = 2*pi/3;  % ���ҳ���λ
CurveParam_DC = -2;             % ֱ������
NoiseVariance = 1.5;            % �۲���������
InitParam = [20, 5, -pi, 3];    % ������ָ���ĳ�ʼֵ, ˳��A,w,phi,c
lb = [5, 5, -pi, -4];           % ������ָ���Ĳ�������, ˳��A,w,phi,c
ub = [20, 10, pi, 4];           % ������ָ���Ĳ�������, ˳��A,w,phi,c

experiment_index = 2; % ���� 1��2 ���� 3, ���ļ�����ʵ��ͬʱֻʵ������һ��
figureindex = 1;
if experiment_index == 1
    % ������ȫ�����ʵ��,Ч�����ã�������ѡ��ĵ������۲������Լ���ֵ������
    fit_time = [0.5, 1.2, 1.5, 2, 3, 4];        % ���αȽϵĹ۲�ʱ��
    fit_pointsnum = [15, 20, 25, 30, 40, 50];   % ���αȽϵĲ�������
    for index = 1 : length(fit_time)
        figure(figureindex);figureindex = figureindex + 1;
        % ����һ�α��۲�ԭʼ����
        t = 0 : fit_time(index) / fit_pointsnum(index) : fit_time(index);
        IdealCurve = CurveParam_DC + CurveParam_A * sin(CurveParam_W * t ...
            + CurveParam_InitPhase);
        subplot(3,2,1);plot(t, IdealCurve);title('�������ʵ���������');
        % ��ԭʼ�����ϵ��������õ��۲⵽������
        ObserveData = IdealCurve + NoiseVariance * randn(size(IdealCurve));
        subplot(3,2,2);plot(t, ObserveData);title('�����ʵ�ʱ��۲�����');
        % ʹ�ø�˹-ţ�ٷ�����������С���˷���ϲ���
        error = @(Param) Param(1) * sin(Param(2) * t + Param(3)) + ...
            Param(4) - ObserveData;
        Param = lsqnonlin(error, InitParam, lb, ub);
        disp(Param);
        Curve = Param(1,1) * sin(Param(1,2) * t + Param(1,3)) + Param(1,4);
        subplot(3,2,3);plot(t,Curve,t,ObserveData,t,IdealCurve);
        title('��ϳ����ߵ�Ч��');
        % ���Ƴ�ʱ���Ժ��������ߵ����
        longtime = 0 : 0.01 : 40;
        RealCurve = CurveParam_A * sin(CurveParam_W * longtime + ...
            CurveParam_InitPhase) + CurveParam_DC;
        FittedCurve = Param(1,1) * sin(Param(1,2) * longtime + ...
            Param(1,3)) + Param(1,4);
        subplot(3,2,4);plot(longtime,RealCurve,longtime,FittedCurve);
        title('��ʱ����������ߺ����ȡ�������');
        % ��ӡ��Ϣ
        info = ['��������', num2str(fit_pointsnum(index)), newline, ...
            '����ʱ��', num2str(fit_time(index)), 's', newline, ...
            '��ʵ��Ϣ A = ', num2str(CurveParam_A), '   w = ', ...
            num2str(CurveParam_W), newline, ...
            '             InitPhase = ', num2str(CurveParam_InitPhase),...
            '   DC = ', num2str(CurveParam_DC), newline, ...
            '�����Ϣ A = ', num2str(Param(1,1)), '   w = ', ...
            num2str(Param(1,2)), newline, ...
            '             InitPhase = ', num2str(Param(1,3)),...
            '   DC = ', num2str(Param(1,4))];
        annotation('textbox', [.2 .05 .6 .3],'String', info);
    end
elseif experiment_index == 2
    % ��һ����ʱ��������������
    Time = 15;           % �۲���ʱ��
    SamplePoints = 1500; % �ܲ�������
    StartPoints = 65;    % ��ʼ��ϵĵ���λ��
    % ���ɹ۲�����
    t = 0 : Time / SamplePoints : Time;
    IdealCurve = CurveParam_A * sin(CurveParam_W * t + ...
        CurveParam_InitPhase) + CurveParam_DC;
    ObserveCurve = IdealCurve + NoiseVariance * randn(size(IdealCurve));
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,ObserveCurve,'LineWidth',1);hold on;
    plot(t,IdealCurve,'LineWidth',2);hold off;
    legend('Observe','Real');title('ʵ�����ߺ͹۲�����');
    % ��ָ����㿪ʼ������ӵ�������
    FitCurve = zeros(1, length(t));
    FitCurve(1, 1 : StartPoints) = ObserveCurve(1, 1 : StartPoints);
    % ׼����¼��ϲ���
    FittedParam = zeros(length(t), 4);
    for index = 2 : StartPoints
        FittedParam(index, :) = InitParam(1, :);
    end
    for iteration = StartPoints : 1 : length(t)
        tempt = t(1, 1 : iteration);
        % ʹ�ù۲⵽����������������С�������
        tempObserveData = ObserveCurve(1, 1 : iteration);
        error = @(Param) Param(1) * sin(Param(2) * tempt + Param(3)) + ...
            Param(4) - tempObserveData;
        % ��һ�ι۲�Ĳ������������Ϊ��һ�εĳ�ʼֵ
        if iteration == StartPoints
            Param = lsqnonlin(error, InitParam, lb, ub);
        else
            Param = lsqnonlin(error, Param, lb, ub);
        end
        % ��λ�ǵĽǶ����������Ȧ
        lb(1, 3) = Param(1, 3) - pi;ub(1, 3) = Param(1, 3) + pi;
        % ʹ����ϳ��Ľ��������һʱ�̵ĺ���ֵ���������һ���������ڲ���Ҫ
        if iteration ~= length(t)
            NextTime = iteration / SamplePoints * Time;
            FitCurve(1, iteration + 1) = Param(1, 1) * sin(Param(1, 2) * ...
                NextTime + Param(1, 3)) + Param(1, 4);
        end
        % ��� ��¼���ι۲�Ĳ���
        disp(Param);
        FittedParam(iteration, :) = Param;
    end
    % �������յ����Ч��
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve,'LineWidth',1.5);hold on;
    plot(t,IdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted','Real');title('ʵ�����ߺ��������');
    % ����������ߵı仯
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve - IdealCurve);title('������');
    % ��Ͻ������������ֱ�����Ժ����Ƚ�
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
    title('ʵ�����ߺ�������߷ֱ���ֺ�Ľ��');
    % ������ϲ����ı仯
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FittedParam(:,1),t,FittedParam(:,2),...
        t,FittedParam(:,3),t,FittedParam(:,4));
    legend('A','w','phi','c');title('��ϲ����ı仯');
elseif experiment_index == 3
    % ���Թ۲Ⲣ��ϻ���
    Time = 15;           % �۲���ʱ��
    SamplePoints = 1500; % �ܲ�������
    StartPoints = 65;    % ��ʼ��ϵĵ���λ��
    % ���ɹ۲�����
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
    legend('Observe','Real');title('ʵ�����ߺ͹۲�����');
    % ��ָ����㿪ʼ������ӵ�������
    FitCurve = zeros(1, length(t));
    FitCurve(1, 1 : StartPoints) = ObserveCurve(1, 1 : StartPoints);
    % ׼����¼��ϲ���
    FittedParam = zeros(length(t), 4);
    for index = 2 : StartPoints
        FittedParam(index, :) = InitParam(1, :);
    end
    for iteration = StartPoints : 1 : length(t)
        tempt = t(1, 1 : iteration);
        % ʹ�ù۲⵽����������������С�������
        tempObserveData = ObserveCurve(1, 1 : iteration);
        error = @(Param) -Param(1) / Param(2) * sin(Param(2) * tempt + ...
            Param(3)) + Param(4) * tempt - tempObserveData;
        % ��һ�ι۲�Ĳ������������Ϊ��һ�εĳ�ʼֵ
        if iteration == StartPoints
            Param = lsqnonlin(error, InitParam, lb, ub);
        else
            Param = lsqnonlin(error, Param, lb, ub);
        end
        % ��λ�ǵĽǶ����������Ȧ
        lb(1, 3) = Param(1, 3) - pi;ub(1, 3) = Param(1, 3) + pi;
        % ʹ����ϳ��Ľ��������һʱ�̵ĺ���ֵ���������һ���������ڲ���Ҫ
        if iteration ~= length(t)
            NextTime = iteration / SamplePoints * Time;
            FitCurve(1, iteration + 1) = -Param(1, 1) / Param(1, 2) * ...
                sin(Param(1, 2) * NextTime + Param(1, 3)) + Param(1, 4) * ...
                NextTime;
        end
        % ��� ��¼���ι۲�Ĳ���
        disp(Param);
        FittedParam(iteration, :) = Param;
    end
    % �������յ����Ч��
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve,'LineWidth',1.5);hold on;
    plot(t,IdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted','Real');title('ʵ�����ߺ��������');
    % ����������ߵı仯
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FitCurve - IdealCurve);title('������');
    % ��Ͻ������������ֱ�΢���Ժ����Ƚ�
    figure(figureindex);figureindex = figureindex + 1;
    DerivativedFitCurve = Param(1, 1) * sin(Param(1, 2) * ...
        t + Param(1, 3)) + Param(1, 4);
    DerivativedIdealCurve = CurveParam_A * sin(CurveParam_W * t + ...
        CurveParam_InitPhase) + CurveParam_DC;
    plot(t,DerivativedFitCurve,'LineWidth',1.5);hold on;
    plot(t,DerivativedIdealCurve,'LineWidth',1.5);hold off;
    legend('Fitted-Derivatived','Real-Derivatived');
    title('ʵ�����ߺ�������߷ֱ�΢�ֺ�Ľ��');
    % ������ϲ����ı仯
    figure(figureindex);figureindex = figureindex + 1;
    plot(t,FittedParam(:,1),t,FittedParam(:,2),...
        t,FittedParam(:,3),t,FittedParam(:,4));
    legend('A','w','phi','c');title('��ϲ����ı仯');
end
