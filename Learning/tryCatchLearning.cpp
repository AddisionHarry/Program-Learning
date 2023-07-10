#include <iostream>
#include <string>
#include <exception>

int main(int argc, char *argv[])
{
    // 异常机制的引入
    std::string str = "Hello world!";
    std::cout << str << std::endl;

    try
    { // 下标越界 ch1 的值没有意义
        char ch1 = str[100];
        if (100 >= str.length())
        {
            throw "Out of length";
            std::cout << "Out of length" << std::endl;
        }
        std::cout << "str[100] = " << ch1 << std::endl;
    }
    catch (const char *&e)
    {
        std::cout << "[1]out of bound! from Exception const char*" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "[1]out of bound! from Exception std::exception" << std::endl;
    }

    try
    {
        // 下标越界 抛出异常
        char ch2 = str.at(100);
        std::cout << "str.at(100) = " << ch2 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "[2]out of bound!" << std::endl;
    }

    return 0;
}
