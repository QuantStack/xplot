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

auto randn(std::size_t n1, std::size_t n2)
{
    std::vector<std::vector<double>> output(n1, std::vector<double>(n2));
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(5, 2);

    for(auto& line: output)
        for(auto& v: line)
            v = dis(gen);

    return output;
}

auto randint(std::size_t beg, std::size_t end)
{
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(beg, end-1);
    return dis(gen);
}

auto randint(std::size_t beg, std::size_t end, std::size_t size)
{
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(beg, end-1);
    std::vector<double> output(size);
    std::for_each(output.begin(), output.end(), [&dis, &gen](auto& v){v = dis(gen);});
    return output;
}
