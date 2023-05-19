% ����������˵����ŷ����������ת��Ϣʱ, ��ŷ���ǵ������ǶȾ�����[-pi, pi]��Χ��ʱ
% ͬһ��̬��Ȼ����ʹ������ŷ����������
% һ��Ľ���������Կ��Ǵ���ת����ĽǶ����֣����ֱ�����ʽ����ת������һ�µ�, ���
% ���Խ�ŷ���Ǳ���Ϊ��ת����, Ȼ����ת��������ת��Ϊŷ����, ��ʱ������ʽ�ͻ�����һ��
% ŷ������Ϣ[yaw,pitch, roll]<->[-pi+yaw,pi-pitch,pi+roll]

% ָ���������
yaw=30;   % �� z ����ת�ĽǶ�, y ��Ϊ��ɫ
pitch=20; % �� y ����ת�ĽǶ�, y ��Ϊ��ɫ
roll=30;  % �� x ����ת�ĽǶ�, x ��Ϊ��ɫ
len=15;   % ÿһ����ת�Ĳ�ֵ����
% ��ת�м����
theta11=0:yaw/len:yaw;
theta12=0:pitch/len:pitch;
theta13=0:roll/len:roll;
theta21=0:(-180+yaw)/len:-180+yaw;
theta22=0:(180-pitch)/len:180-pitch;
theta23=0:(roll+180)/len:roll+180;
for k=1:6*len+1
    %���Ƴ�ʼ����ϵ
    plot3([0,2],[0,0],[0,0],'r','LineWidth',1);%���� x ��, ������λ����
    xlim([-1 2]);ylim([-1 2]);zlim([-1 2]);
    hold on;
    plot3([0,0],[0,2],[0,0],'g','LineWidth',1);%���� y ��, ������λ����
    plot3([0,0],[0,0],[0,2],'b','LineWidth',1);%���� z ��, ������λ����
    if k<=len
        R=rotz(theta11(k));
    elseif k<=len*2
        k1=k-len;
        R=rotz(yaw)*roty(theta12(k1));
        % ������ʱ����ϵ
        Rtemp=rotz(yaw);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%���� x ��, ������λ����
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%���� y ��, ������λ����
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%���� z ��, ������λ����
    elseif k<=len*3
        k1=k-len*2;
        R=rotz(yaw)*roty(pitch)*rotx(theta13(k1));
        % ������ʱ����ϵ
        Rtemp=rotz(yaw)*roty(pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%����x��,������λ����
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%����y��,������λ����
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%����z��,������λ����
    elseif k<=len*4
        Rall=rotz(yaw)*roty(pitch)*rotx(roll);
        k1=k-len*3;
        R=rotz(theta21(k1));
    elseif k<=len*5
        k1=k-len*4;
        R=rotz(-180+yaw)*roty(theta22(k1));
        % ������ʱ����ϵ
        Rtemp=rotz(-180+yaw);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%����x��,������λ����
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%����y��,������λ����
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%����z��,������λ����
    elseif k<=len*6
        k1=k-len*5;
        R=rotz(-180+yaw)*roty(180-pitch)*rotx(theta23(k1));
        % ������ʱ����ϵ
        Rtemp=rotz(-180+yaw)*roty(180-pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%����x��,������λ����
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%����y��,������λ����
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%����z��,������λ����
    else
        R=rotz(-180+yaw)*roty(180-pitch)*rotx(roll+180);
        % ������ʱ����ϵ
        Rtemp=rotz(-180+yaw)*roty(180-pitch);
        plot3([Rtemp(1,1),0],[Rtemp(2,1),0],[Rtemp(3,1),0],'k');%����x��,������λ����
        plot3([Rtemp(1,2),0],[Rtemp(2,2),0],[Rtemp(3,2),0],'k');%����y��,������λ����
        plot3([Rtemp(1,3),0],[Rtemp(2,3),0],[Rtemp(3,3),0],'k');%����z��,������λ����
    end
    % ת�����xyz��
    if k<=len*3
        plot3([R(1,1),0],[R(2,1),0],[R(3,1),0],'-','color','r','LineWidth',3);%����x��
        plot3([R(1,2),0],[R(2,2),0],[R(3,2),0],'-','color','g','LineWidth',3);%����y��
        plot3([R(1,3),0],[R(2,3),0],[R(3,3),0],'-','color','b','LineWidth',3);%����z��
    else
        % ������һ�ֵ����ս��
        plot3([Rall(1,1),0],[Rall(2,1),0],[Rall(3,1),0],'-','color','r','LineWidth',3);%����x��
        plot3([Rall(1,2),0],[Rall(2,2),0],[Rall(3,2),0],'-','color','g','LineWidth',3);%����y��
        plot3([Rall(1,3),0],[Rall(2,3),0],[Rall(3,3),0],'-','color','b','LineWidth',3);%����z��
        % ���Ʊ�����ת���
        plot3([R(1,1),0],[R(2,1),0],[R(3,1),0],'-','color','r','LineWidth',4);%����x��
        plot3([R(1,2),0],[R(2,2),0],[R(3,2),0],'-','color','g','LineWidth',4);%����y��
        plot3([R(1,3),0],[R(2,3),0],[R(3,3),0],'-','color','b','LineWidth',4);%����z��
    end
    hold off;%�Ƿ����˶��켣
    %����gif����
    im = frame2im(getframe(gcf));
    [I, map] = rgb2ind(im,20);
    if (k==1)
        imwrite(I,map,'Rotate.gif','gif','Loopcount',inf,'DelayTime',0.1);
    else
        imwrite(I,map,'Rotate.gif','gif','WriteMode','append','DelayTime',0.1);
    end
end

% �����������ת������һ�µ�
flag = rotz(yaw)*roty(pitch)*rotx(roll)-rotz(-180+yaw)*roty(180-pitch)*rotx(roll+180)==0 %#ok<NBRAK,NOPRT>
