#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    std::stringstream sstream;
    std::string strResult;

    /**************** 数据类型转换实验 ****************/
    int nValue = 1000;
    sstream << nValue;    // 将int类型的值放入输入流中
    sstream >> strResult; // 从sstream中抽取前面插入的int类型的值，赋给string类型

    std::cout << "[cout]strResult is: " << strResult << std::endl;
    printf("[printf]strResult is: %s\n", strResult.c_str());
    printf("[printf]strResult is: %s\n\n", sstream.str().c_str());

    /***************** 字符串拼接实验 *****************/
    // 将多个字符串放入 sstream 中
    sstream.clear(); // 清空类型记录
    sstream.str(""); // 清空字符串
    sstream << "first"
            << " "
            << "string, ";
    sstream << " second string";
    // 输出拼接结果
    std::cout << "strResult is: " << sstream.str() << std::endl
              << std::endl;

    /***************** 字符串清空实验 *****************/
    // 输出当前记录的字符串
    sstream.clear();   // 清空类型记录
    sstream.str("");   // 清空字符串
    sstream << "1626"; // 输入一个数字字符串
    std::cout << "strResult is: " << sstream.str() << std::endl;

    sstream >> nValue; // 将前面的字符串转化成数字
    printf("valResult is: %d\n", nValue);

    sstream.str(""); // 清空字符串
    std::cout << "strResult is: " << sstream.str() << std::endl;

    sstream << true; // 将 bool 类型的值放入输入流中
    std::cout << "strResult is: " << sstream.str() << std::endl;

    sstream.clear(); // 清空类型记录
    sstream << true; // 将 bool 类型的值放入输入流中
    std::cout << "strResult is: " << sstream.str() << std::endl;
    bool test = false;
    sstream >> test;
    std::cout << "boolResult is: " << test << std::endl;

    nValue = 10000;
    sstream >> nValue; // 不匹配的类型转换会失败, 但是不会输出错误信息
    printf("valResult is: %d\n", nValue);

    sstream.clear();   // 清空类型记录
    sstream >> nValue; // 不匹配的类型转换会失败, 但是不会输出错误信息
    printf("valResult is: %d\n", nValue);

    return 0;
}
