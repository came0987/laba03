#pragma once
#include <vector>
#include <string>
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<size_t>& bins);

