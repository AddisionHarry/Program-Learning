import time

# 计算代码的执行时间


def cal_time(fn):
    start = time.time()
    fn()
    end = time.time()
    print('这段代码执行的时间是{}s'.format(round(end - start, 4)))


def demo_1():
    print('Hello')
    time.sleep(2)
    print('World!')


def demo_2():
    a = 0
    for i in range(10000000):
        a += i
    print(a)


cal_time(demo_1)
cal_time(demo_2)

# 使用装饰器计算代码的执行时长


def calc_time(fn):
    print(1)

    def inner(*args, **kwargs):
        start = time.time()
        s = fn(*args)
        end = time.time()
        print('代码耗时{}s'.format(round(end - start, 4)))
        return s

    return inner


@calc_time  # 这里只要出现了一个语句，不论后面foo函数或者calc函数是否被调用，都会运行calc的外部函数(注意内部函数还没有运行)
def foo_1():
    print('Hello')
    time.sleep(2)
    print('World!')


@calc_time
def foo_2(n):
    a = 0
    for i in range(n):
        a += i
    return a


foo_1()
print(foo_1)
print(foo_2(10000000))
