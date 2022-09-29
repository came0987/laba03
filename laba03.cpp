#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include <curl/curl.h>

using namespace std;

vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; ++i)
    {
        cin >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if (prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if (prompt)
    {
        cerr << "Enter bin count: ";
    }
    in >> data.bin_count;

    return data;
}

/*vector<size_t> make_histogram(size_t number_count, size_t bin_count, vector<double> numbers)
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
}*/

vector <size_t>  make_histogram(Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    vector <size_t> result(input.bin_count);
    for (double number : input.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * (input.bin_count));
        if (bin == input.bin_count)
        {
            bin--;
        }
        result[bin]++;
    }
    return result;
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

int main(int argc, char* argv[])
{
    //curl_global_init(CURL_GLOBAL_ALL);

    if (argc > 1)
    {
        CURL* curl = curl_easy_init();
        if (curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
            res = curl_easy_perform(curl);
            if (res!=CURLE_OK)
            {
                cerr << curl_easy_strerror(res);
                exit(1);
            }
            curl_easy_cleanup(curl);
        }

        return (0);
    }

    const auto input = read_input(cin, true);

    //Расчет гистограммы
    const auto bins = make_histogram(input);

    //Вывод данных
    show_histogram_text(bins);
    //show_histogram_svg(bins);
}
