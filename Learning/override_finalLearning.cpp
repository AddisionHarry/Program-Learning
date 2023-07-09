#include <iostream>

// 该宏写 1 会让编译器报错，写 0 会将报错部分注释
#define GET_ERROR 0

struct Base
{
public:
    // 虚函数
    virtual void Show(int x);
};
struct Derived : public Base
{
public:
    // o 写成了 0，新的虚函数
    virtual void Sh0w(int x);
    // 参数列表不一样，新的虚函数
    virtual void Show(double x);
    // const 属性不一样，新的虚函数
    virtual void Show(int x) const;
#if (GET_ERROR == 1)
    // const 属性不一样，新的虚函数，但是由于出现了 override 关键字所以报错
    virtual void Show(int x) const override;
#endif

    // 新的不能被继承的虚函数
    virtual void show(void) final;
};
struct NewDerived final : public Derived
{
public:
#if (GET_ERROR == 1)
    // 尝试重写不能被重写的虚函数，报错
    virtual void show(void) override;
#endif
    int test;
};
#if (GET_ERROR == 1)
class tryDerive : NewDerived
{
public:
    int a;
};
#endif

int main(int argc, char **argv)
{
    // 不能正常编译，因而没有输出信息
    return 0;
}
