#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include "Volume.h"

class Projection {
public:
    Projection(const Volume* volume);
    ~Projection();

    void IP(const char* compare_function, const char* output_name, int min_z, int max_z);

private:
    const Volume* volume;

    template<typename T>
    T my_max(const T& a, const T& b);

    template<typename T>
    T my_min(const T& a, const T& b);

    int separation(std::vector<unsigned char>& val, int l, int h);
    void quickSort(std::vector<unsigned char>& val, int l, int h);
};
