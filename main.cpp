#include <iostream>
#include "neural_net.h"
#include "program.h"
#include "matrix.h"
#include "TensorsNet.h"
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
    TensorsNet aboba({2, 3, 4});
    aboba.forwardPass({0.1, 0.2});
    return 0;
}




//std::cout << "Hello, World!" << std::endl;
//    NeuralNet aboba({3, 4, 5, 3});
//    for (int i = 0; i < 1000; ++i) {
//        aboba.forward_step({0.12, 0.642, 0.421});
//        aboba.backward_step({0.423, 0.95, 0.185});
//    }
//
//    //aboba.eval_net();