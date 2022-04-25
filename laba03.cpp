#include <iostream>
#include <vector>
#include <string>

using namespace std;

void svg_begin(double width, double height) 
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() 
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) 
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x = '" << x << "' y = '" << y << "' width = '" << width << "' height = '" << height << "' stroke ='" << stroke << "' fill ='" << fill << "'/>";
}

void show_histogram_svg(const vector<size_t>& bins) 
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto COLOUR_RED = "#c51d34";
    const string COLOUR_BLUE = "#171dbf";
    const string COLOUR_GREEN = "#3ab53e";

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    double MAX_WIDTH = (IMAGE_WIDTH - TEXT_WIDTH) / BLOCK_WIDTH;

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
        double bin_width;
        if (max_bin > MAX_WIDTH)
        {
            bin_width = MAX_WIDTH * (static_cast<double>(bin) / max_bin);
        }
        else
        {
            bin_width = BLOCK_WIDTH * bin;
        }
        //const double bin_width = BLOCK_WIDTH * bin;

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, COLOUR_RED, COLOUR_BLUE);
        top += BIN_HEIGHT;
    }
    svg_end();
}

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; ++i)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double &min, double &max)
{
    min = numbers[0];
    max = numbers[0];

    for (double number : numbers)
    {
        if (number < min)
        {
            min = number;
        }
        else if (number > max)
        {
            max = number;
        }
    }
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

