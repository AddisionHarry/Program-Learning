# 设计一个石头剪刀布游戏
import random

player = int(input('请输入你选择出的内容：（0）石头； （1）剪刀；  （2）布'))
print('用户出的是', player)

computer = random.randint(0, 2)
print('电脑出的是', computer)

if player == computer:
	print('平局啦，再来一次吧！')
elif player == 0:
	if computer == 2:
		print('很遗憾，用户失败。')
	else:
		print('恭喜您，用户胜利！')
elif player == 1:
	if computer == 2:
		print('恭喜您，用户胜利！')
	else:
		print('很遗憾，用户失败。')
elif player == 2:
	if computer == 0:
		print('恭喜您，用户胜利！')
	else:
		print('很遗憾，用户失败。')
