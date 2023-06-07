% ʹ�� input ��������趨
r = input("���� R = \n");
P = input('���ݺ��� P = \n');
W = input('W = \n');
W0 = input('W0 = \n');
Wc = input('Wc = \n');
Tf = input('�������ʱ�� Tf = \n');
h = input('������㲽�� h = \n');
% ����ԽǾ���
A1 = diag(P(:,1));
B1 = diag(P(:,2));
C1 = diag(P(:,3));
D1 = diag(P(:,4));
% �����������
H = B1 - D1 * W;
Q = C1 * W - A1;
A = H \ Q;
B = H \ C1 * W0;
x = zeros(length(A), 1);
y = zeros(length(Wc(:, 1)), Tf / h + 1);
t = zeros(1, Tf / h + 1);
% �����������
for i = 1 : Tf / h
    k1 = A * x + B * r;
    k2 = A * (x + h * k1 / 2) + B * r;
    k3 = A * (x + h * k2 / 2) + B * r;
    k4 = A * (x + h * k3) + B * r;
    x = x + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    y(i + 1, :) = Wc * x;
    t(i + 1) = t(i) + h;
end
% ���������Ӧ����
plot(t, y);

% һ��ʾ�����룺
% R = 10; 
% P = [0.1,1,0.5,1;0,1,1,0;2,1,2,0;10,1,10,0];
% W = [0,0,0,-1;1,0,0,0;0,1,0,0;0,0,1,0];
% W0 = [1;0;0;0];
% Wc = [0,0,0,1];
% Tf = 10;
% h = 0.2;
