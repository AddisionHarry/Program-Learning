from functools import reduce

# 与匿名函数相关的内置方法/类
students = [
    {'name': '张三', 'age': 15, 'score': 98, 'height': 160},
    {'name': '李四', 'age': 18, 'score': 140, 'height': 180},
    {'name': '王五', 'age': 20, 'score': 150, 'height': 185},
    {'name': 'Jack', 'age': 25, 'score': 70, 'height': 182},
    {'name': 'Harry', 'age': 23, 'score': 86, 'height': 175}
]
students.sort(key=lambda m: m['height'], reverse=True)
print(students)
print(list(filter(lambda m: m['age'] > 18, students)))
print(list(map(lambda m: m['score'] + 2, students)))
print(reduce(lambda m, n: m + n['score'], students, 0), "\n")

# 高阶函数使用示例


def foo():
    print('我是foo,我被调用了')
    return 'foo'


def bar():
    print('我是bar,我被调用了')
    return foo()


def fun():
    print('我是fun,我被调用了')
    return foo


x = bar()
print('x的值是{}\n'.format(x))

y = fun()
print('y的值是{}'.format(y))
print(y(), '\n')

z = fun()()
print(z, '\n')


def outer(n):
    num = n

    def inner():
        print('我是inner函数')
        """
        这里也可以写成：
        nonlocal num
        num += 10
        return num
        """
        return num + 10

    print('我是outer函数')
    return inner


outer(4)
print(outer(4)())
