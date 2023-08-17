close all;
dt = 1e-3;                                      % 通信周期 1ms
Encoder_Len = 8192;                             % 编码器线数
t = 0 : dt : 5;                                 % 仿真时间
Real_Angle = 90*(1-exp(-10*t))+20*sin(3*t);     % 实际角度变化(degree)
Real_AngularSpeed = [0, diff(Real_Angle)]/dt;   % 实际角速度变化(dps)

Ideal_Angle_ENCD = round(Real_Angle/360*Encoder_Len); % 理想编码器角度变化
Ideal_AngularSpeed_ENCD = round(Real_AngularSpeed/6); % 理想编码器角速度变化

figure(1);
subplot(2,1,1);plot(t,Ideal_Angle_ENCD);hold off;
xlabel('时间(s)'),ylabel('角度(360/8192°)');
subplot(2,1,2);plot(t,Ideal_AngularSpeed_ENCD);hold off;
xlabel('时间(s)'),ylabel('角速度(rpm)');
suptitle('理想编码器反馈数据');

% 实际编码器角度变化
Real_Angle_ENCD = round(Real_Angle/360*Encoder_Len+3*randn(size(Real_Angle)));
% 实际编码器角速度变化
temp = [0, diff(Real_Angle_ENCD)/Encoder_Len]/dt*60;
Real_AngularSpeed_ENCD = round(temp*0.005+Ideal_AngularSpeed_ENCD*0.995+...
    randn(size(Real_Angle)));

figure(2);
subplot(2,1,1);plot(t,Real_Angle_ENCD);hold off;
xlabel('时间(s)'),ylabel('角度(360/8192°)');
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD);hold off;
xlabel('时间(s)'),ylabel('角速度(rpm)');
suptitle('实际编码器反馈数据');

figure(3);
subplot(2,1,1);plot(t,Ideal_Angle_ENCD,t,Real_Angle_ENCD);hold on;
xlabel('时间(s)'),ylabel('角度(360/8192°)');
subplot(2,1,2);plot(t,Ideal_AngularSpeed_ENCD,t,Real_AngularSpeed_ENCD);hold on;
xlabel('时间(s)'),ylabel('角速度(rpm)');

% 对实际数据进行滞后滤波
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

% 滞后滤波以后使用匀速卡尔曼滤波器对齐
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

% 对原始数据直接使用匀速卡尔曼滤波器
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
legend('实际角度','编码器读数','LPF输出角度','LPF-KF输出角度','KF输出角度');
subplot(2,1,2);plot(t,Real_AngularSpeed_ENCD_KF);hold off;
legend('实际角度','编码器读数','LPF输出角速度','LPF-KF输出角速度','KF输出角速度');

figure(4);
subplot(2,1,1);
plot(t,Ideal_Angle_ENCD-Real_Angle_ENCD_filtered,...
    t,Ideal_Angle_ENCD-Real_Angle_ENCD_LPF_KF,...
    t,Ideal_Angle_ENCD-Real_Angle_ENCD_KF);
xlabel('时间(s)'),ylabel('角度误差(360/8192°)');
legend('滞后滤波角度估计误差','LPF-KF角度估计误差','KF角度估计误差');
subplot(2,1,2);
plot(t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_filtered,...
    t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_LPF_KF,...
    t,Ideal_AngularSpeed_ENCD-Real_AngularSpeed_ENCD_KF);
xlabel('时间(s)'),ylabel('角速度误差(rpm)');
legend('滞后滤波角速度估计误差','LPF-KF角速度估计误差','KF角速度估计误差');
