#include "../histogram.h"
#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_02()
{
    double min = 0;
    double max = 0;
    find_minmax({ -3, -4, -5 }, min, max);
    assert(min == -5);
    assert(max == -3);
}

void test_03()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1, 1, 1 }, min, max);
    assert(min == 1);
    assert(max == min);
}

void test_04()
{
    double min = 0;
    double max = 0;
    find_minmax({ 2 }, min, max);
    assert(min == 2);
    assert(max == 2);
}

void test_05()
{
    double min = 0, min1 = min;
    double max = 0, max1 = max;
    find_minmax({ }, min, max);
    assert(min == min1);
    assert(max == max1);
}

int main()
{
    test_positive();
    test_02();
    test_03();
    test_04();
    test_05();
}
