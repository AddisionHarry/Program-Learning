#include <iostream>

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
    // const 属性不一样，新的虚函数，但是由于出现了 override 关键字所以报错
    virtual void Show(int x) const override;

    // 新的不能被继承的虚函数
    virtual void show(void) final;
};
struct NewDerived final : public Derived
{
public:
    // 尝试重写不能被重写的虚函数，报错
    virtual void show(void) override;
};
class tryDerive : NewDerived
{
public:
    int a;
};

int main(int argc, char **argv)
{
    // 不能正常编译，因而没有输出信息
    return 0;
}
