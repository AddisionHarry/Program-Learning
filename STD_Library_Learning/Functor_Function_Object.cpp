#include <iostream>

class Compare
{
private:
    int m_Number;

public:
    Compare(int num) : m_Number(num) {}
    // 通过重载 () 运算符构造仿函数
    bool operator()(int other) { return (m_Number > other); }
};

int main(int argc, char *argv[])
{
    Compare cmp(10);
    std::cout << cmp(11) << std::endl;
    std::cout << cmp(9) << std::endl;

    return 0;
}
