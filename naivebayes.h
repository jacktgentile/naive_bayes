//
// Created by jackt on 3/11/2018.
//

#ifndef NAIVEBAYES_NAIVEBAYES_H
#define NAIVEBAYES_NAIVEBAYES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

using std::cout;
using std::cin;
using std::endl;

const int image_width = 28;
const int image_height = 28;

vector<bool> empty_bool_vector(image_width, false);
vector<vector<bool>> empty_2d_bool_vector(image_height, empty_bool_vector);

vector<int> empty_int_vector(image_width, 0);
vector<vector<int>> empty_2d_int_vector(image_height, empty_int_vector);

#endif //NAIVEBAYES_NAIVEBAYES_H