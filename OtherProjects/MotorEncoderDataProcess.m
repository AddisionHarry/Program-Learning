close all;
dt = 1e-3;                                      % ͨ������ 1ms
Encoder_Len = 8192;                             % ����������
t = 0 : dt : 5;                                 % ����ʱ��
Real_Angle = 90*(1-exp(-10*t))+20*sin(3*t);     % ʵ�ʽǶȱ仯(degree)
Real_AngularSpeed = [0, diff(Real_Angle)]/dt;   % ʵ�ʽ��ٶȱ仯(dps)

Ideal_Angle_ENCD = round(Real_Angle/360*Encoder_Len); % ����������Ƕȱ仯
Ideal_AngularSpeed_ENCD = round(Real_AngularSpeed/6); % ������������ٶȱ仯

figure(1);
subplot(2,1,1);plot(t,Ideal_Angle_ENCD);hold off;
xlabel('ʱ��(s)'),ylabel('�Ƕ�(360/8192��)');
subplot(2,1,2);plot(t,Ideal_AngularSpeed_ENCD);hold off;
xlabel('ʱ��(s)'),ylabel('���ٶ�(rpm)');
suptitle('�����������������');

% ʵ�ʱ������Ƕȱ仯
Real_Angle_ENCD = round(Real_Angle/360*Encoder_Len+3*randn(size(Real_Angle)));
% ʵ�ʱ��������ٶȱ仯
temp = [0, diff(Real_Angle_ENCD)/Encoder_Len]/dt*60;
Real_AngularSpeed_ENCD = round(temp*0.005+Ideal_AngularSpeed_ENCD*0.995+...
    randn(size(Real_Angle)));

figure(2);
subplot(2,1,1);plot(t,Real_Angle_ENCD);hold off;
xlabel('ʱ��(s)'),ylabel('�Ƕ�(360/8192��)');
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD);hold off;
xlabel('ʱ��(s)'),ylabel('���ٶ�(rpm)');
suptitle('ʵ�ʱ�������������');

figure(3);
subplot(2,1,1);plot(t,Ideal_Angle_ENCD,t,Real_Angle_ENCD);hold on;
xlabel('ʱ��(s)'),ylabel('�Ƕ�(360/8192��)');
subplot(2,1,2);plot(t,Ideal_AngularSpeed_ENCD,t,Real_AngularSpeed_ENCD);hold on;
xlabel('ʱ��(s)'),ylabel('���ٶ�(rpm)');

% ��ʵ�����ݽ����ͺ��˲�
Real_Angle_ENCD_filtered = zeros(size(t));
Real_AngularSpeed_ENCD_filtered = zeros(size(t));
for index = 1 : length(t)
    if index == 1
        Real_Angle_ENCD_filtered(index) = Real_Angle_ENCD(index);
        Real_AngularSpeed_ENCD_filtered(index) = Real_AngularSpeed_ENCD(index);
    else
        Real_Angle_ENCD_filtered(index) = Real_Angle_ENCD(index)*0.7+...
            Real_Angle_ENCD_filtered(index-1)*0.3;
        Real_AngularSpeed_ENCD_filtered(index) = ...
            Real_AngularSpeed_ENCD(index)*0.1+...
            Real_AngularSpeed_ENCD_filtered(index-1)*0.9;
    end
end
subplot(2,1,1);plot(t,Real_Angle_ENCD_filtered);legend();hold on;
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD_filtered);hold on;

% �ͺ��˲��Ժ�ʹ�����ٿ������˲�������
A = [1,dt;0,1];
C = eye(2);
Q = [0.1, 0;0, 0.1];
R = [0.5, 0; 0, 3];
X = [0;0];P=[1,0;0,1];
Real_Angle_ENCD_LPF_KF = zeros(size(t));
Real_AngularSpeed_ENCD_LPF_KF = zeros(size(t));
for index = 1 : length(t)
    if index==1
        Real_Angle_ENCD_LPF_KF(index)= Real_Angle_ENCD_filtered(index);
        Real_AngularSpeed_ENCD_LPF_KF(index) = ...
            Real_AngularSpeed_ENCD_filtered(index);
    else
        Z = [Real_Angle_ENCD_filtered(index-1)/Encoder_Len*360;...
            Real_AngularSpeed_ENCD_filtered(index-1)/60*360];
        X_ = A*X;
        P_ = A*P*A' + Q;
        K = P_*C'/(C*P_*C'+R);
        X = X_+K*(Z-C*X_);
        P = (eye(2)-K*C)*P_;
        Real_Angle_ENCD_LPF_KF(index)= X(1)/360*Encoder_Len;
        Real_AngularSpeed_ENCD_LPF_KF(index) = X(2)*60/360;
    end
end
subplot(2,1,1);plot(t,Real_Angle_ENCD_LPF_KF);hold on;
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD_LPF_KF);hold on;

% ��ԭʼ����ֱ��ʹ�����ٿ������˲���
Q = [0.2, 0;0, 0.2];
R = [2, 0; 0, 10];
X = [0;0];P=[1,0;0,1];
Real_Angle_ENCD_KF = zeros(size(t));
Real_AngularSpeed_ENCD_KF = zeros(size(t));
for index = 1 : length(t)
    if index==1
        Real_Angle_ENCD_LPF_KF(index)= Real_Angle_ENCD(index);
        Real_AngularSpeed_ENCD_LPF_KF(index) = Real_AngularSpeed_ENCD(index);
    else
        Z = [Real_Angle_ENCD(index-1)/Encoder_Len*360;...
            Real_AngularSpeed_ENCD(index-1)/60*360];
        X_ = A*X;
        P_ = A*P*A' + Q;
        K = P_*C'/(C*P_*C'+R);
        X = X_+K*(Z-C*X_);
        P = (eye(2)-K*C)*P_;
        Real_Angle_ENCD_KF(index)= X(1)/360*Encoder_Len;
        Real_AngularSpeed_ENCD_KF(index) = X(2)*60/360;
    end
end
subplot(2,1,1);plot(t,Real_Angle_ENCD_KF);hold off;
legend('ʵ�ʽǶ�','����������','LPF����Ƕ�','LPF-KF����Ƕ�','KF����Ƕ�');
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD_KF);hold off;
legend('ʵ�ʽǶ�','����������','LPF������ٶ�','LPF-KF������ٶ�','KF������ٶ�');

figure(4);
subplot(2,1,1);
plot(t,Ideal_Angle_ENCD-Real_Angle_ENCD_filtered,...
    t,Ideal_Angle_ENCD-Real_Angle_ENCD_LPF_KF,...
    t,Ideal_Angle_ENCD-Real_Angle_ENCD_KF);
xlabel('ʱ��(s)'),ylabel('�Ƕ����(360/8192��)');
legend('�ͺ��˲��Ƕȹ������','LPF-KF�Ƕȹ������','KF�Ƕȹ������');
subplot(2,1,2);
plot(t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_filtered,...
    t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_LPF_KF,...
    t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_KF);
xlabel('ʱ��(s)'),ylabel('���ٶ����(rpm)');
legend('�ͺ��˲����ٶȹ������','LPF-KF���ٶȹ������','KF���ٶȹ������');
