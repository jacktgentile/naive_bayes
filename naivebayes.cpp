//
// Created by jackt on 3/8/2018.
//
#include "naivebayes.h"
#include "train_and_test.h"

vector<vector<bool>> convert_next_image();
vector<n_tuple> train(string image_filename, string label_filename);

ifstream fin1;
ifstream fin2;

int main() {
    string image_filename;
    string label_filename;
    cout << "training image file name: ";
    cin >> image_filename;
    cout << "training label file name: ";
    cin  >> label_filename;
    //loop to get an image into result_vector
    vector<n_tuple> prob_holder = train(image_filename, label_filename);
    cout << get<0>(prob_holder[0]) << '\t' << get<1>(prob_holder[0]) << endl;
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            cout << get<2>(prob_holder[0])[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

vector<n_tuple> train(string image_filename, string label_filename) {
    fin1.open(image_filename);
    fin2.open(label_filename);
    //vector of tuple<label, occurrence count, 2d integer vector>
    vector<n_tuple> tuple_vector(10);
    for (int i = 0; i < 10; i++) {
        tuple_vector[i] = make_tuple(i, 0, empty_2d_int_vector);
    }
    while (!fin1.eof() && !fin2.eof()) {
        auto image_vector = convert_next_image();
        int label;
        fin2 >> label;
        get<1>(tuple_vector[label])++;
        auto probability_count = get<2>(tuple_vector[label]);
        for (int i = 0; i < image_vector.size(); i++) {
            for (int j = 0; j < image_vector[i].size(); j++) {
                if (image_vector[i][j]) {
                    probability_count[i][j]++;
                }
            }
        }
        get<2>(tuple_vector[label]) = probability_count;
    }
    fin1.close();
    fin2.close();
    return tuple_vector;
}

//use stream to turn next string into 2d vector image
vector<vector<bool>> convert_next_image() {
    vector<vector<bool>> result_vector(empty_2d_bool_vector);
    for (int i = 0; i < image_height; i++) {
        char current_line[image_width];
        fin1.getline(current_line, image_width + 1);
        for (int j = 0; j < image_width; j++) {
            char current_char = current_line[j];
            if (current_char == ' ') {
                result_vector[i][j] = false;
            } else if (current_char == '+' || current_char == '#') {
                result_vector[i][j] = true;
            }
        }
    }
    return result_vector;
}