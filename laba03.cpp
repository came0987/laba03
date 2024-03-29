﻿#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"

using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; ++i)
    {
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(size_t number_count, size_t bin_count, vector<double> numbers)
{
    double min, max;
    find_minmax(numbers, min, max);

    vector<size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;

    for (size_t i{ 0 }; i < number_count; ++i)
    {
        bool found{ false };
        for (size_t j{ 0 }; j < (bin_count - 1) && !found; ++j)
        {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;

            if ((low <= numbers[i]) && (numbers[i] < high))
            {
                ++bins[j];
                found = true;
            }
        }
        if (!found)
        {
            ++bins[bin_count - 1];
        }
    }
    return bins;
}

void show_histogram_text(vector<size_t> bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }

    for (size_t bin : bins)
    {
        size_t height = bin;

        if (max_bin > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }

        cout << bin << "|";

        for (size_t i{}; i < height; ++i)
        {
            cout << "*";
        }
        cout << '\n';
    }
}

int main()
{

    //Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;


    //Расчет гистограммы
    const auto bins = make_histogram(number_count, bin_count, numbers);


    //Вывод данных
    //show_histogram_text(bins);
    show_histogram_svg(bins);
}
