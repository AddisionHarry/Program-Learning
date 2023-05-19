% 本程序用于说明当欧拉角描述旋转信息时, 在欧拉角的三个角度均处于[-pi, pi]范围内时
% 同一姿态依然可以使用两种欧拉角来描述
% 一般的解决方法可以考虑从旋转矩阵的角度入手：两种表述方式的旋转矩阵是一致的, 因此
% 可以将欧拉角表述为旋转矩阵, 然后将旋转矩阵重新转化为欧拉角, 此时描述方式就会趋于一致
% 欧拉角信息[yaw,pitch, roll]<->[-pi+yaw,pi-pitch,pi+roll]

% 指定输入参数
yaw=30;   % 沿 z 轴旋转的角度, y 轴为蓝色
pitch=20; % 沿 y 轴旋转的角度, y 轴为绿色
roll=30;  % 沿 x 轴旋转的角度, x 轴为红色
len=15;   % 每一次旋转的插值次数
% 旋转中间变量
theta11=0:yaw/len:yaw;
theta12=0:pitch/len:pitch;
theta13=0:roll/len:roll;
theta21=0:(-180+yaw)/len:-180+yaw;
theta22=0:(180-pitch)/len:180-pitch;
theta23=0:(roll+180)/len:roll+180;
for k=1:6*len+1
    %绘制初始坐标系
    plot3([0,2],[0,0],[0,0],'r','LineWidth',1);%绘制 x 轴, 两个单位长度
    xlim([-1 2]);ylim([-1 2]);zlim([-1 2]);
    hold on;
    plot3([0,0],[0,2],[0,0],'g','LineWidth',1);%绘制 y 轴, 两个单位长度
    plot3([0,0],[0,0],[0,2],'b','LineWidth',1);%绘制 z 轴, 两个单位长度
    if k<=len
        R=rotz(theta11(k));
    elseif k<=len*2
        k1=k-len;
        R=rotz(yaw)*roty(theta12(k1));
        % 绘制临时坐标系
        Rtemp=rotz(yaw);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%绘制 x 轴, 两个单位长度
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%绘制 y 轴, 两个单位长度
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%绘制 z 轴, 两个单位长度
    elseif k<=len*3
        k1=k-len*2;
        R=rotz(yaw)*roty(pitch)*rotx(theta13(k1));
        % 绘制临时坐标系
        Rtemp=rotz(yaw)*roty(pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%绘制x轴,两个单位长度
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%绘制y轴,两个单位长度
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%绘制z轴,两个单位长度
    elseif k<=len*4
        Rall=rotz(yaw)*roty(pitch)*rotx(roll);
        k1=k-len*3;
        R=rotz(theta21(k1));
    elseif k<=len*5
        k1=k-len*4;
        R=rotz(-180+yaw)*roty(theta22(k1));
        % 绘制临时坐标系
        Rtemp=rotz(-180+yaw);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%绘制x轴,两个单位长度
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%绘制y轴,两个单位长度
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%绘制z轴,两个单位长度
    elseif k<=len*6
        k1=k-len*5;
        R=rotz(-180+yaw)*roty(180-pitch)*rotx(theta23(k1));
        % 绘制临时坐标系
        Rtemp=rotz(-180+yaw)*roty(180-pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%绘制x轴,两个单位长度
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%绘制y轴,两个单位长度
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%绘制z轴,两个单位长度
    else
        R=rotz(-180+yaw)*roty(180-pitch)*rotx(roll+180);
        % 绘制临时坐标系
        Rtemp=rotz(-180+yaw)*roty(180-pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%绘制x轴,两个单位长度
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%绘制y轴,两个单位长度
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%绘制z轴,两个单位长度
    end
    % 转动后的xyz轴
    if k<=len*3
        plot3([R(1,1),0],[R(2,1),0],[R(3,1),0],'-','color','r','LineWidth',3);%绘制x轴
        plot3([R(1,2),0],[R(2,2),0],[R(3,2),0],'-','color','g','LineWidth',3);%绘制y轴
        plot3([R(1,3),0],[R(2,3),0],[R(3,3),0],'-','color','b','LineWidth',3);%绘制z轴
    else
        % 绘制上一轮的最终结果
        plot3([Rall(1,1),0],[Rall(2,1),0],[Rall(3,1),0],'-','color','r','LineWidth',3);%绘制x轴
        plot3([Rall(1,2),0],[Rall(2,2),0],[Rall(3,2),0],'-','color','g','LineWidth',3);%绘制y轴
        plot3([Rall(1,3),0],[Rall(2,3),0],[Rall(3,3),0],'-','color','b','LineWidth',3);%绘制z轴
        % 绘制本次旋转结果
        plot3([R(1,1),0],[R(2,1),0],[R(3,1),0],'-','color','r','LineWidth',4);%绘制x轴
        plot3([R(1,2),0],[R(2,2),0],[R(3,2),0],'-','color','g','LineWidth',4);%绘制y轴
        plot3([R(1,3),0],[R(2,3),0],[R(3,3),0],'-','color','b','LineWidth',4);%绘制z轴
    end
    hold off;%是否保留运动轨迹
    %生成gif动画
    im = frame2im(getframe(gcf));
    [I, map] = rgb2ind(im,20);
    if (k==1)
        imwrite(I,map,'Rotate.gif','gif','Loopcount',inf,'DelayTime',0.1);
    else
        imwrite(I,map,'Rotate.gif','gif','WriteMode','append','DelayTime',0.1);
    end
end

% 两种运算的旋转矩阵是一致的
flag = rotz(yaw)*roty(pitch)*rotx(roll)-rotz(-180+yaw)*roty(180-pitch)*rotx(roll+180)==0 %#ok<NBRAK,NOPRT>
