# 打印九九乘法表
i, j = 0, 0
while i < 9:
	i += 1
	while j < i:
		j += 1
		print(i, '*', j, '=', i*j, sep='', end='\t')
	print()
	j = 0  # 注意这一句是比较关键的
print('结束啦，你会了吗？')
