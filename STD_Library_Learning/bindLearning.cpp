#include <functional>
#include <iostream>

// 测试函数
int TestFunc(int a, char c, float f)
{
    std::cout << a << '\t' << c << '\t' << f << std::endl;
    return a;
}

// 测试类
class TestClass1
{
public:
    TestClass1() {}
    TestClass1(int a) : m_a(a) {}
    TestClass1(const TestClass1 &obj)
    {
        std::cout << "copy construct." << std::endl;
        m_a = obj.m_a + 100;
    }
    int ClassMember(int a) { return 50 + a; }
    int ClassMember2(int a, char ch, float f)
    {
        std::cout << ch << '\t' << f << '\t' << a << std::endl;
        return 52 + a;
    }
    static int StaticMember(int a) { return 60 + a; }

private:
    int m_a;
};
class TestClass2
{
public:
    TestClass2() : m_a(100) {}

public:
    int m_a;
};
class TestClass3
{
public:
    TestClass3() = default;
    TestClass3(const TestClass3 &obj)
    {
        std::cout << "TestClass3 copy construct." << std::endl;
    }
    int operator()(int a)
    {
        std::cout << a << std::endl;
        return 0;
    }
};

// 打印函数返回值的函数
static void
Print_Res(int res, int FuncIndex)
{
    std::cout << "fun" << FuncIndex << " res = " << res << std::endl
              << std::endl;
}

int main(int argc, char *argv[])
{
    // 绑定普通函数
    auto fun1 = std::bind(TestFunc, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3);
    auto fun2 = std::bind(TestFunc, std::placeholders::_2,
                          std::placeholders::_3, std::placeholders::_1);
    auto fun3 = std::bind(TestFunc, std::placeholders::_1,
                          std::placeholders::_2, 98.77f);
    Print_Res(fun1(30, 'C', 100.1f), 1);
    Print_Res(fun2(100.1f, 30, 'C'), 2);
    Print_Res(fun3(30, 'C', 98.f), 3);
    // 绑定成员函数
    TestClass1 test;
    auto fun4 = std::bind(&TestClass1::ClassMember, test, std::placeholders::_1);
    Print_Res(fun4(4), 4);
    auto fun5 = std::bind(&TestClass1::ClassMember2, test,
                          std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3);
    Print_Res(fun5(1, 'A', 3.1f), 5);
    auto fun6 = &TestClass1::StaticMember;
    Print_Res(fun6(3), 6);
    // 绑定成员变量
    TestClass2 test2;
    auto fun7 = std::bind(&TestClass2::m_a, std::placeholders::_1);
    Print_Res(fun7(test2), 7);
    // 绑定仿函数
    TestClass3 test3;
    auto fun8 = test3;
    Print_Res(fun8(2018), 8);
    // 通过指针取消拷贝构造
    TestClass1 test1(67);
    std::function<int(TestClass1 *, int)> fg = &TestClass1::ClassMember;
    Print_Res(fg(&test1, 5), 9);

    return 0;
}
