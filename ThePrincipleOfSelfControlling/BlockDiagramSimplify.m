% 规定系统参数
syms Ra T1 T2 c c1 c2 ka kr km kb
% 设定参数初值
Ra=1;T1=1;T2=1;c=1;c1=1;c2=1;ka=1;kr=1;km=1;kb=1;
% 系统模块定义
G1 = tf(c1);
G2 = tf(ka);
G3 = tf(kr);
G4 = tf(1/Ra,[T1 1]);
G5 = tf(km);
G6 = tf(1/c,[T2 1]);
G7 = tf(1,[1 0]);
G8 = tf(kb);
G9 = tf(c2);
% 定义模块连接顺序
Sum1 = sumblk('e1 = r1 - y1');
Sum2 = sumblk('e2 = u2 - y2');
Sum3 = sumblk('e3 = u4 - M');
G1.u = 'r';  G1.y = 'r1';
G2.u = 'e1'; G2.y = 'u1';
G3.u = 'u1'; G3.y = 'u2';
G4.u = 'e2'; G4.y = 'u3';
G5.u = 'u3'; G5.y = 'u4';
G6.u = 'e3'; G6.y = 'u5';
G7.u = 'u5'; G7.y = 'n';
G8.u = 'u5'; G8.y = 'y2';
G9.u = 'n';  G9.y = 'y1';
% 计算从输入到输出的传递函数
Trn = connect(G1,G2,G3,G4,G5,G6,G7,G8,G9,Sum1,Sum2,Sum3,'r','n');
[TrnNum,TrnDen] = ss2tf(Trn.A,Trn.B,Trn.C,Trn.D);
Grn = tf(TrnNum,TrnDen)
% 计算从扰动到输出的传递函数
Tmn = connect(G1,G2,G3,G4,G5,G6,G7,G8,G9,Sum1,Sum2,Sum3,'M','n');
[TmnNum,TmnDen] = ss2tf(Tmn.A,Tmn.B,Tmn.C,Tmn.D);
Gmn = tf(TmnNum,TmnDen)