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
//    TensorsNet aboba({2, 50, 10, 3});
//    aboba.addConvLayer(3, 2);
//    //aboba.addConvLayer(5, 3);
//    //прямой проход конволюции я пока не проверял (он не работает)
//    //обратный проход конволюции тоже (его нет)
//    for (int i = 0; i < 100; ++i) {
//        aboba.forwardPass({0.1, 0.2});
//        aboba.backwardPass({0.9, 0.13}, 1, 0.5);
//    }

    TensorsNet aboba;
    aboba.addConvLayer(2, 2);
    aboba.addLayer(2, 2, 0);
    //aboba.addConvLayer(3, 2);
    for (size_t i = 0; i < 100; ++i) {
        aboba.forwardPass({0.1, 0.2, 0.3, 0.4});
        //aboba.convForward({0}, 1);
        aboba.backwardPass({0.7, 0.9}, 1, 0.5);
        std::cout << "PIPA" << '\n';
        aboba.graph[0][0].weights.printMatrix();
        std::cout << "ZOPA" << '\n';
    }

    aboba.forwardPass({0, 0.5, 0.1, 0.3, 0.6, 0.7, -0.5, 0.9, 0.7});
    //aboba.convForward({0}, 1);
    aboba.backwardPass({0.8, 0.2}, 1, 1);

    return 0;
}
// d_weights, d_biases == 0?



//std::cout << "Hello, World!" << std::endl;
//    NeuralNet aboba({3, 4, 5, 3});
//    for (int i = 0; i < 1000; ++i) {
//        aboba.forward_step({0.12, 0.642, 0.421});
//        aboba.backward_step({0.423, 0.95, 0.185});
//    }
//
//    //aboba.eval_net();