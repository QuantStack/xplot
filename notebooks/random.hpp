#pragma once

#include <algorithm>
#include <random>
#include <vector>

auto randn(std::size_t n)
{
    std::vector<double> output(n);
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(5, 2);

    std::for_each(output.begin(), output.end(), [&dis, &gen](auto& v){v = dis(gen);});

    return output;
}

auto randint(std::size_t beg, std::size_t end)
{
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(beg, end-1);
    return dis(gen);
}
