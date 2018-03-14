//
// Created by jackt on 3/11/2018.
//

#ifndef NAIVEBAYES_NAIVEBAYES_H
#define NAIVEBAYES_NAIVEBAYES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <bits/stdc++.h>

using std::tuple;
using std::make_tuple;
using std::get;
using std::log;

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::make_pair;

using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;

const int image_width = 28;
const int image_height = 28;

vector<bool> empty_bool_vector(image_width, false);
vector<vector<bool>> empty_2d_bool_vector(image_height, vector<bool>(image_width, false));

vector<int> empty_int_vector(image_width, 0);
vector<vector<int>> empty_2d_int_vector(image_height, vector<int>(image_width, 0));

//tuple pairing label 0-9 to number of occurrences to 2D vector of ints
typedef tuple<int, int, vector<vector<int>>> n_tuple;

#endif //NAIVEBAYES_NAIVEBAYES_H