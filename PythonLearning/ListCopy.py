import copy
import random

# 列表复制的相关操作
a = [1, 2, 3, 4, 5]
b = a
c = copy.copy(a)
print(a, b, c)
a[0] = 10
print(a, b, c)

# 10个老师随机分配到3个房间
teachers = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
rooms = [[], [], []]
for teacher in teachers:
    room = random.choice(rooms)  # choice 从列表里随机一个数据
    room.append(teacher)
print(rooms)
for i, room in enumerate(rooms):  # 通过for...in语句对列表进行计数
    print('第%d个房间里有%d个老师，分别是：' % (i, len(room)))
    for teacher in room:
        print(teacher, end='\t')
    print()

# 列表推导式
x = [i for i in range(10) if i % 2]
print(x)

points = [(x, y) for x in range(1, 4) for y in range(5, 10)]
print(points)

# 生成一个包含0到100的整数的列表并将其内的元素按照3个一组划分生成一个嵌套列表
numbers = [i for i in range(0, 101)]
new_numbers = [numbers[j:j+3] for j in range(0, 101, 3)]
print(new_numbers)
