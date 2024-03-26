//
// Created by zxces on 26.03.2024.
//

#include "TensorsNet.h"




TensorsNet::TensorsNet(const std::vector<size_t> & all_layers){
    for (size_t l = 0; l < all_layers.size() - 1; ++l) {

        Matrix M(all_layers[l+1], all_layers[l]);
        graph.emplace_back().emplace_back();
        graph.back().back().weights = M;
        graph.back().back().d_weights = M;
        for (int i = 0; i < all_layers[l+1]; ++i) {
            for (int j = 0; j < all_layers[l]; ++j) {
                graph.back().back().weights.setElement(i, j, Matrix::genRandom());
            }
            graph.back().back().biases.push_back(Matrix::genRandom());
            graph.back().back().d_biases.push_back(Matrix::genRandom());
            graph.back().back().grads.push_back(0);
            graph.back().back().output_values.push_back(0);
        }

    }
};

void TensorsNet::forwardPass(const std::vector<double> &inputs) {

    graph[0][0].output_values = Matrix::sumVecs(graph[0][0].weights.dotVector(inputs), graph[0][0].biases);
    relu_function(graph[0][0].output_values);


    for (size_t i = 1; i < graph.size(); ++i) {
        const std::vector<double> & prevValues = graph[i-1][0].output_values;
        graph[i][0].output_values = Matrix::sumVecs(graph[i][0].weights.dotVector(prevValues), graph[i][0].biases);
        relu_function(graph[i][0].output_values);
    }
}

void TensorsNet::relu_function(std::vector<double> &nonactive){
    for (double & elm : nonactive) {
        if(elm <= 0){
            elm = 0;
        }
    }
}