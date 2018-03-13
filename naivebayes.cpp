//
// Created by jackt on 3/8/2018.
//
#include "naivebayes.h"
#include "train_and_test.h"

vector<vector<bool>> convert_next_image();
vector<n_tuple> train(string image_filename, string label_filename);
pair<int, double> classify(vector<vector<bool>> image);
vector<vector<float>> test(string image_filename, string label_filename);

ifstream fin1;
ifstream fin2;
const double laplace_factor = 1.0;
vector<n_tuple> model;

int main() {
    string image_filename;
    string label_filename;
    cout << "Training image file name: ";
    cin >> image_filename;
    cout << "Training label file name: ";
    cin  >> label_filename;
    //store results from training files in model
    model = train(image_filename, label_filename);
    cout << "Training complete\nTesting image file name: ";
    cin >> image_filename;
    cout << "Testing label file name: ";
    cin >> label_filename;
    //assign 2d confusion matrix as per specification
    vector<vector<float>> confusion_matrix = test(image_filename, label_filename);
    cout << endl;
    for (int i = 0; i < confusion_matrix.size(); i++) {
        for (int j = 0; j < confusion_matrix[i].size(); j++) {
            //http://www.cplusplus.com/reference/iomanip/setprecision/
            cout << fixed << setprecision(1) << confusion_matrix[i][j] << '\t';
        }
        cout << endl << endl;
    }
    return 0;
}

//return confusion matrix for test
vector<vector<float>> test(string image_filename, string label_filename) {
    fin1.open(image_filename);
    fin2.open(label_filename);
    vector<vector<float>> confusion_matrix(10, vector<float>(10, 0.0));
    vector<int> actual_class_count(10, 0);
    while (!fin1.eof() && !fin2.eof()) {
        auto current_image = convert_next_image();
        int actual_label;
        fin2 >> actual_label;
        actual_class_count[actual_label]++;
        auto classification_pair = classify(current_image);
        confusion_matrix[actual_label][classification_pair.first]++;
    }
    fin1.close();
    fin2.close();
    //convert counts to percents
    for (int i = 0; i < confusion_matrix.size(); i++) {
        for (int j = 0; j < confusion_matrix[i].size(); j++) {
            confusion_matrix[i][j] = confusion_matrix[i][j] * 100 / actual_class_count[i];
        }
    }
    return confusion_matrix;
}

//computes probability of image belongs to each class using model
//returns most probable class and log of posterior probability
pair<int, double> classify(vector<vector<bool>> image) {
    pair<int, double> best_probability;
    bool is_first_iteration = true;
    double total_images_count = 0.0;
    for (n_tuple current_tuple : model) {
        total_images_count += (double) get<1>(current_tuple);
    }
    for (n_tuple current_tuple : model) {
        //calculate p(class)
        double current_probability_sum = log10(((double) get<1>(current_tuple))/(total_images_count));
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                double numerator;
                if (image[i][j]) {
                    numerator = laplace_factor + get<2>(current_tuple)[i][j];
                } else {
                    numerator = laplace_factor + (double)get<1>(current_tuple)
                                - (double)get<2>(current_tuple)[i][j];
                }
                current_probability_sum += log10(numerator /
                                           (2 * laplace_factor + (double)get<1>(current_tuple)));
            }
        }
        if (is_first_iteration
            || current_probability_sum > best_probability.second) {
            best_probability.first = get<0>(current_tuple);
            best_probability.second = current_probability_sum;
        }
        is_first_iteration = false;
    }
    return best_probability;
}



//return vector of n_tuples that model information from the training files
vector<n_tuple> train(string image_filename, string label_filename) {
    fin1.open(image_filename);
    fin2.open(label_filename);
    //vector of tuple<label, occurrence count, 2d integer vector>
    vector<n_tuple> tuple_vector(10);
    for (int i = 0; i < 10; i++) {
        tuple_vector[i] = make_tuple(i, 0, empty_2d_int_vector);
    }
    while (!fin1.eof() && !fin2.eof()) {
        //2d bool vector from fin1 stream
        auto image_vector = convert_next_image();
        int label;
        fin2 >> label;
        //add to the frequency count for actual number
        get<1>(tuple_vector[label])++;
        //copy 2d int vector to probability count for actual number
        auto probability_count = get<2>(tuple_vector[label]);
        for (int i = 0; i < image_vector.size(); i++) {
            for (int j = 0; j < image_vector[i].size(); j++) {
                if (image_vector[i][j]) {
                    probability_count[i][j]++;
                }
            }
        }
        //reassign changed 2d vector to the tuple_vector
        get<2>(tuple_vector[label]) = probability_count;
    }
    fin1.close();
    fin2.close();
    return tuple_vector;
}

//use stream fin1 to turn next string into 2d vector image
vector<vector<bool>> convert_next_image() {
    vector<vector<bool>> result_vector(empty_2d_bool_vector);
    for (int i = 0; i < image_height && !fin1.eof(); i++) {
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