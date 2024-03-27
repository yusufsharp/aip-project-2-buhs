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
            graph.back().back().grads.push_back(0);
        }

    }
};

void TensorsNet::forwardPass(const std::vector<double> &inputs) {
    // МЫ НЕ СОХРАНЯЕМ ВХОДНЫЕ ЗНАЧЕНИЯ!!!!!!!!!
    graph[0][0].input_values = inputs;
    graph[0][0].output_values = Matrix::sumVecs(graph[0][0].weights.dotVector(inputs), graph[0][0].biases);
    relu_function(graph[0][0].output_values);


    for (size_t i = 1; i < graph.size(); ++i) {
        graph[i][0].input_values = graph[i-1][0].output_values;
        graph[i][0].output_values = Matrix::sumVecs(graph[i][0].weights.dotVector(graph[i][0].input_values), graph[i][0].biases);
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

std::vector<double> TensorsNet::relu_function_derived(const std::vector<double> &nonderived){
    std::vector<double> res;
    for (const double & elm : nonderived) {
        if(elm <= 0){
            res.push_back(0);
        }
        else{
            res.push_back(1);
        }
    }
    return res;
}

void TensorsNet::backwardPass(const std::vector<double> &outputs, double lr, double moment){
    const size_t & len_graph = graph.size();
    graph[len_graph - 1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[len_graph - 1][0].output_values),
    Matrix::subVecs(outputs, graph[len_graph - 1][0].output_values));

    for (size_t i = len_graph - 1; i > 0; --i) {
        graph[i-1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[i-1][0].output_values),
                                                  graph[i][0].weights.t().dotVector(graph[i][0].grads));
    }

    for (size_t i = 0; i < len_graph; ++i) {
        Matrix M = Matrix::ij_mul(graph[i][0].input_values, graph[i][0].grads).t().scalarMul(1 - moment).scalarMul(lr);
        Matrix dM = graph[i][0].d_weights.scalarMul(moment);
        graph[i][0].d_weights = M.add(dM);
        graph[i][0].weights = graph[i][0].weights.add(graph[i][0].d_weights);

        std::vector<double> b = Matrix::scalarMulVec(Matrix::scalarMulVec(graph[i][0].grads, (1 - moment)), lr);
        std::vector<double> db = Matrix::scalarMulVec(graph[i][0].d_biases, moment);
        graph[i][0].d_biases = Matrix::sumVecs(b, db);
        graph[i][0].biases = Matrix::sumVecs(graph[i][0].d_biases, graph[i][0].biases);



    }
    for(const double & i : graph.back().back().output_values){
        std::cout << i << ' ';
    }
    std::cout << '\n';

}