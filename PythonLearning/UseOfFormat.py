# format方法配合列表、字典的使用

# 配合列表的使用
d = ['张三', 20, '上海', 180]
b1 = '我叫{}，我今年{}岁了，我来自{}，身高{}cm'.format(d[0], d[1], d[2], d[3])
b2 = '我叫{}，我今年{}岁了，我来自{}，身高{}cm'.format(*d)
print(b1)
print(b2)

# 配合字典的使用
info = {'name': 'chris', 'age': 23, 'add': '北京', 'height': 190}
c = '我叫{name}，我今年{age}岁了，我来自{add}，身高{height}cm'.format(**info)
print(c)
