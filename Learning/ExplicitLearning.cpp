#include <iostream>

class Explicit_Test1
{
private:
    int _a;
    int _b;

public:
    Explicit_Test1() : _a(0), _b(0) {}
    Explicit_Test1(int a, int b = 1);
    void disp(void);
    Explicit_Test1 &operator=(int a);
    operator int() const;

    friend Explicit_Test1 operator+(Explicit_Test1 &a, int b);
};
Explicit_Test1::Explicit_Test1(int a, int b) : _a(a), _b(b)
{
    std::cout << "Construct called." << std::endl;
}
void Explicit_Test1::disp(void)
{
    std::cout << this->_a << '\t' << this->_b << std::endl;
}
Explicit_Test1 &Explicit_Test1::operator=(int a)
{
    std::cout << "Function operator= called." << std::endl;
    this->_a = a;
    this->_b = 0;
    return *this;
}
Explicit_Test1::operator int() const
{
    std::cout << "Function operator int() called." << std::endl;
    return this->_a + this->_b;
}
Explicit_Test1 operator+(Explicit_Test1 &a, int b)
{
    return Explicit_Test1(a._a + b, a._b + b);
}

class Explicit_Test2
{
private:
    int _a;
    int _b;

public:
    explicit Explicit_Test2() : _a(0), _b(0) {}
    explicit Explicit_Test2(int a, int b = 2);
    void disp(void);
    Explicit_Test2 &operator=(int a);
    explicit operator int() const;

    friend std::ostream &operator<<(std::ostream &os, const Explicit_Test2 &a);
    friend Explicit_Test2 operator+(Explicit_Test2 &a, int b);
};
Explicit_Test2::Explicit_Test2(int a, int b) : _a(a), _b(b)
{
    std::cout << "Construct called." << std::endl;
}
void Explicit_Test2::disp(void)
{
    std::cout << this->_a << '\t' << this->_b << std::endl;
}
Explicit_Test2 &Explicit_Test2::operator=(int a)
{
    std::cout << "Function operator= called." << std::endl;
    this->_a = a;
    this->_b = 0;
    return *this;
}
Explicit_Test2::operator int() const
{
    std::cout << "Function operator int() called." << std::endl;
    return this->_a + this->_b;
}
std::ostream &operator<<(std::ostream &os, const Explicit_Test2 &a)
{
    os << a._a << '\t' << a._b;
    return os;
}
Explicit_Test2 operator+(Explicit_Test2 &a, int b)
{
    return Explicit_Test2(a._a + b, a._b + b);
}

int main(int argc, char *argv[])
{
    // 首先复习一下类型转换构造函数(关键是隐式转换)和
    // 等号运算符的重载并感受一下两者之间的区别
    Explicit_Test1 test1 = 3;
    test1.disp();
    test1 = 2;
    test1.disp();
    std::cout << std::endl;

    // 复习一下类型转换运算符的重载
    Explicit_Test1 test2 = test1 + 2;
    test2.disp();
    test2 = 2 + test1;
    test2.disp();
    // !!! 注意这种具有二义性的写法应当避免，这里只是起知识学习作用
    std::cout << test1 + 2 << std::endl;
    std::cout << 2 + test1 << std::endl; // 重载以后的加法运算不满足交换律
    std::cout << std::endl;

    // 使用 explicit 关键字
    Explicit_Test2 test3(4);
    // 对输出流重载
    std::cout << test3 + 2 << std::endl;
    // 显式类型转换
    std::cout << static_cast<int>(test3 + 2) << std::endl;
    std::cout << std::endl;

    // 在复制构造函数中使用 explicit 关键字会导致报错，这里就不演示了

    return 0;
}
