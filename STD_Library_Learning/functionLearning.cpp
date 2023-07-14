#include <iostream>
#include <functional>

// 函数指针类型定义
typedef int (*func)(void);

// 定义两个测试函数
int print1(void)
{
    std::cout << "hello, print1" << std::endl;
    return 0;
}
int print2(void)
{
    std::cout << "hello, print2" << std::endl;
    return 0;
}
// 一个模板测试函数
template <typename T>
T fun1(void)
{
    return (T)(2);
}

class A
{
public:
    void operator()(void) { std::cout << "This is A Object" << std::endl; }
};

class B
{
private:
    std::function<void()> callback_; // 回调函数

public:
    B(const std::function<void()> &f) : callback_(f){};
    void notify(void) { callback_(); }
};
class Foo
{
public:
    void operator()(void) { std::cout << __FUNCTION__ << std::endl; }
};

// // 尝试探索 std::function 原理
// namespace test
// {
//     template <typename R, typename ArgType>
//     class myfunction<R(ArgType)>
//     {
//     public:
//         R operator()(ArgType arg0)
//         {
//             return (R)arg0;
//         }
//     };
// }

int main(int argc, char *argv[])
{
    // 使用函数指针
    func fp = &print1;
    fp();
    fp = &print2;
    fp();
    std::cout << std::endl;

    // 使用 std::function 包装函数
    std::function<void(void)> func(&print1);
    func();
    func = &print2;
    func();
    std::cout << std::endl;

    // 包装仿函数(函数对象)
    A a;
    a();
    func = a;
    func();
    std::cout << std::endl;

    // std::function 使用实战
    std::function<int(void)> callback;
    // 包装函数指针
    callback = fp;
    std::cout << callback() << std::endl;
    // 包装模板函数
    callback = fun1<int>;
    std::cout << callback() << std::endl;
    // 包装 lambda 表达式
    auto fun2 = [](void)
    { return 4; };                        // lamda 表达式
    callback = fun2;                      // std::function 包装 lamda 表达式
    std::cout << callback() << std::endl; // std::function 对象实例调用包装的调用实体
    std::cout << std::endl;

    // 作为回调函数使用
    Foo foo;
    B b(foo);
    b.notify();
    std::cout << std::endl;

    // 尝试探究 std::function 原理
    // myfunction<int, void>::Function fun3 = print1;
    // fun3(1);

    return 0;
}
