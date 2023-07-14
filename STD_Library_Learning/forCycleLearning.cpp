#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[])
{
    /************* for_each 循环 *************/
    int nums[]{3, 4, 2, 9, 15, 267};
    const auto N = sizeof(nums) / sizeof(int);
    auto Print = [](int i)
    { std::cout << i << ' '; };

    // 第一种遍历方式——遍历数组
    std::for_each(nums, nums + N, Print);
    std::cout << std::endl;
    for (auto *ptr = nums; ptr < nums + N; ++ptr)
        Print(*ptr);
    std::cout << std::endl
              << std::endl;

    // 第二种遍历方式——遍历容器
    std::vector<int> vec_int{3, 4, 2, 9, 15, 267};
    vec_int.pop_back();
    vec_int.push_back(120);
    std::for_each(vec_int.begin(), vec_int.end(), Print);
    std::cout << std::endl;
    auto Add2 = [](int &i)
    { i += 2;std::cout << i << ' '; }; // 入参为引用
    std::for_each(vec_int.begin(), vec_int.end(), Add2);
    std::cout << std::endl;
    for (auto index = 0; index < vec_int.size(); index++)
        std::cout << vec_int.at(index) << ' ';
    std::cout << std::endl
              << std::endl;

    // 跳出 for_each 循环
    auto ExitCycle = [nums](int i)
    {
        if (i == nums[N / 2])
            return;
        else if (i == nums[N - 1])
            throw "end-loop";
        std::cout
            << i << ' ';
    };
    try
    {
        std::for_each(nums, nums + N, ExitCycle);
    }
    catch (const char *)
    {
        std::cout << "\nexit the cycle." << std::endl;
    }
    std::cout << std::endl;

    /************* for 循环变种 *************/
    for (auto i : nums)
        Print(i); // 注意这种方式出来的 i 已经是寻址以后的结果了
    std::cout << std::endl;
    for (auto i : vec_int)
        Print(i); // 传数据
    std::cout << std::endl;
    for (auto &i : vec_int)
        Add2(i); // 传引用

    return 0;
}
