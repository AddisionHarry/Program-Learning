#include <functional>
#include <iostream>

// 是否要打印函数返回值
#define PRINT_FLAG 1

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
    TestClass1() { std::cout << "TestClass1 default construct." << std::endl; }
    TestClass1(int a) : m_a(a) {}
    TestClass1(const TestClass1 &obj);
    int ClassMember1(int a) { return 50 + a; }
    int ClassMember2(int a, char ch, float f);
    static int StaticClassMember(int a) { return 60 + a; }

private:
    int m_a;
};
TestClass1::TestClass1(const TestClass1 &obj)
{
    std::cout << "TestClass1 copy construct." << std::endl;
    m_a = obj.m_a + 100;
}
int TestClass1::ClassMember2(int a, char ch, float f)
{
    std::cout << ch << '\t' << f << '\t' << a << std::endl;
    return 52 + a;
}

class TestClass2
{
public:
    TestClass2() : m_a(100) {}
    TestClass2(const TestClass2 &);

public:
    int m_a;
};
TestClass2::TestClass2(const TestClass2 &)
{
    std::cout << "TestClass2 copy construct." << std::endl;
}

class TestClass3
{
public:
    TestClass3() { std::cout << "TestClass3 default construct." << std::endl; }
    TestClass3(const TestClass3 &);
    int operator()(int a);
};
TestClass3::TestClass3(const TestClass3 &)
{
    std::cout << "TestClass3 copy construct." << std::endl;
}
int TestClass3::operator()(int a)
{
    std::cout << a << std::endl;
    return 0;
}

// 打印输出结果
#if PRINT_FLAG == 1
static int index = 0;
static void Print_Res(int res)
{
    std::cout << "fun" << ++index << " res = " << res << std::endl
              << std::endl;
}
#define PRINT(res) Print_Res(res)
#else
static void Print_Endl(int res)
{
    std::cout << std::endl;
}
#define PRINT(res) Print_Endl(res)
#endif

int main(int argc, char *argv[])
{
    // 绑定普通函数
    auto fun1 = std::bind(TestFunc, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3);
    auto fun2 = std::bind(TestFunc, std::placeholders::_2,
                          std::placeholders::_3, std::placeholders::_1);
    auto fun3 = std::bind(TestFunc, std::placeholders::_1,
                          std::placeholders::_2, 98.77f);
    PRINT(fun1(30, 'C', 100.1f)); // 相当于 TestFunc(30, 'C', 100.1f)
    PRINT(fun2(100.1f, 30, 'C')); // 相当于 TestFunc(30, 'C', 100.1f)
    PRINT(fun3(30, 'C', 98.f));   // 相当于 TestFunc(30, 'C', 98.77f)

    // 绑定成员函数
    TestClass1 test1;
    auto fun4 = std::bind(&TestClass1::ClassMember1, &test1, std::placeholders::_1);
    PRINT(fun4(4)); // 相当于 test1.ClassMember1(4)
    auto fun5 = std::bind(&TestClass1::ClassMember2, &test1,
                          std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3);
    PRINT(fun5(1, 'A', 3.1f)); // 相当于 test1.ClassMember2(1, 'A', 3.1f)
    auto fun6 = std::bind(&TestClass1::StaticClassMember, std::placeholders::_1);
    PRINT(fun6(3)); // 相当于 test1.StaticClassMember(3)

    // 绑定成员变量
    TestClass2 test2;
    auto fun7 = std::bind(&TestClass2::m_a, std::placeholders::_1);
    fun7(&test2) = 8; // 相当于 test2.m_a = 8
    PRINT(fun7(&test2));

    // 绑定仿函数
    TestClass3 test3;
    auto fun8 = test3;
    PRINT(fun8(2023)); // 相当于 test3(2023)
    auto fun9 = std::bind(&TestClass3::operator(), test3, std::placeholders::_1);
    PRINT(fun9(2023)); // 相当于 test3(2023)
    auto fun10 = std::bind(&TestClass3::operator(), &test3, std::placeholders::_1);
    PRINT(fun10(2023)); // 相当于 test3(2023)

    // 通过指针或引用取消拷贝构造
    TestClass1 test4(67);
    std::function<int(TestClass1 *, int)> fun11 = &TestClass1::ClassMember1;
    PRINT(fun11(&test4, 5)); // 相当于 test4.ClassMember1(5)
    std::function<int(TestClass1 &, int)> fun12 = &TestClass1::ClassMember1;
    PRINT(fun12(test4, 5)); // 相当于 test4.ClassMember1(5)

    // 绑定 lambda 表达式
    auto fun13 = std::bind([](int a, int b)
                           { std::cout << "lambda function is called, a ="
                                       << a << ", b=" << b << std::endl;
                                       return 0; },
                           std::placeholders::_1, std::placeholders::_2);
    PRINT(fun13(1, 2));

    return 0;
}
