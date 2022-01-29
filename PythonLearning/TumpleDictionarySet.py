import json
# 统计字符在列表中出现的次数
chars = ['a', 'm', 't', 'n', 'a', 'm', 'a', 'n', 'a', 'm', 'm', 'n']

char_count_1 = {}
for char in chars:
    if char not in char_count_1:
        char_count_1[char] = chars.count(char)
print(char_count_1)

char_count_2 = {}
for char in chars:
    if char in char_count_2:
        char_count_2[char] += 1
    else:
        char_count_2[char] = 1
print(char_count_2)

# 统计出现次数最多的字符
count = char_count_1.values()
max_count = max(count)
flag = 0
for key, value in char_count_1.items():
    if value == max_count:
        flag += 1
        if flag == 1:
            print('{}是出现次数最多的字符，出现了{}次'.format(key, value))
        else:
            print('{}也是出现次数最多的字符，出现了{}次'.format(key, value))

# 创建一个字典列表，用户输入名字，若名字存在则提示用户已存在，反之让用户继续输入年龄并新建字典存储
persons = [{'name': '张三', 'age': 18}, {'name': '李四', 'age': 19}, {'name': '王五', 'age': 17}]
input_name = input('请输入您的姓名:').strip()
for person in persons:
    if person['name'] == input_name:
        print('该姓名已存在！')
        break
else:
    new_person = {'name': input_name}
    print('该姓名注册成功！')
    age = int(input('请输入您的年龄：'))
    new_person['age'] = age
    persons.append(new_person)
    print('用户添加成功！')
print(persons)

# JSON字符串的简单应用实例，json模块的导入在第一行
m = json.dumps(persons)
print(m, type(m), sep='\n')
n1 = json.loads(m)
n2 = eval(m)
print(n1, type(n1), sep='\n')
print(n2, type(n2), sep='\n')

# 带下表的遍历
nums = [12, 24, 58, 92, 76, 88]
en = enumerate(nums)
for e in en:
    print(e)
