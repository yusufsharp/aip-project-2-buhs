#include <iostream>
#include "neural_net.h"
#include "program.h"
#include "matrix.h"
#include "TensorsNet.h"
#include "data_reader.h"



int main() {

//    Matrix A(2, 3);
//    A.setElement(0, 0, 1.0);
//    A.setElement(0, 1, 2.0);
//    A.setElement(0, 2, 3.0);
//    A.setElement(1, 0, 4.0);
//    A.setElement(1, 1, 5.0);
//    A.setElement(1, 2, 6.0);
//
//    A.printMatrix();
//
//    std::vector<double> vec = {1, 2, 3};
//    std::vector<double> result = A.dotVector(vec);
//
//    for (const double &i : result) {
//        std::cout << i << ' ';
//    }

//    TensorsNet aboba({2, 3, 5, 4});
//    for (int i = 0; i < 100; ++i) {
//       aboba.forwardPass({0.1, 0.2});
//        aboba.backwardPass({0.6, 0.7, 0.8, 0.9}, 0.05, 0.5);
//    }

    std::string filename = "../data/train-images.idx3-ubyte";
    std::vector<std::vector<unsigned char>> images = readImageFile(filename);
    NormalizeData(images);

    std::string labelFilename = "../data/train-labels.idx1-ubyte";
    std::vector<unsigned char> labels = readLabelFile(labelFilename);

    int sideLength = 28;

    // Выводим первое изображение в консоль, сделав его квадратным
    printImage(images[0], sideLength);
    std::cout << "Label: " << static_cast<int>(labels[0]) << std::endl;

    return 0;
}




//std::cout << "Hello, World!" << std::endl;
//    NeuralNet aboba({3, 4, 5, 3});
//    for (int i = 0; i < 1000; ++i) {
//        aboba.forward_step({0.12, 0.642, 0.421});
//        aboba.backward_step({0.423, 0.95, 0.185});
//    }
//
//    aboba.eval_net();