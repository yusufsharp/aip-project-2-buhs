//
// Created by zxces on 26.03.2024.
//

#include "TensorsNet.h"




TensorsNet::TensorsNet(const std::vector<size_t> & all_layers){
    for (size_t l = 0; l < all_layers.size() - 1; ++l) {
        graph.emplace_back().emplace_back();
        TensorsNet::addLayer(all_layers[l], all_layers[l + 1], 0);
    }
};

void TensorsNet::addLayer(size_t num_input, size_t num_output, size_t layer_type) {
    Matrix M(num_output, num_input);
    graph.back().back().weights = M;
    graph.back().back().d_weights = M;
    for (int i = 0; i < num_output; ++i) {
        for (int j = 0; j < num_input; ++j) {
            graph.back().back().weights.setElement(i, j, Matrix::genRandom());
        }
        graph.back().back().biases.push_back(Matrix::genRandom());
        graph.back().back().d_biases.push_back(Matrix::genRandom());
        graph.back().back().output_values.push_back(0);
        graph.back().back().layer_type = layer_type;
    }
}


void TensorsNet::forwardPass(const std::vector<double> &inputs) {
    // МЫ НЕ СОХРАНЯЕМ ВХОДНЫЕ ЗНАЧЕНИЯ!!!!!!!!!
    graph[0][0].input_values = inputs;
    graph[0][0].output_values = Matrix::sumVecs(graph[0][0].weights.dotVector(inputs), graph[0][0].biases);
    relu_function(graph[0][0].output_values);


    for (size_t i = 1; i < graph.size(); ++i) {
        graph[i][0].input_values = graph[i - 1][0].output_values;
        graph[i][0].output_values = Matrix::sumVecs(graph[i][0].weights.dotVector(graph[i][0].input_values),
                                                    graph[i][0].biases);
        if (i != graph.size() - 1) {
            relu_function(graph[i][0].output_values);
        }
    }
}

void TensorsNet::relu_function(std::vector<double> &nonactive) {

    for (double &elm : nonactive) {
        elm = std::max(0.0, elm);
    }
}

std::vector<double> TensorsNet::relu_function_derived(const std::vector<double> &nonderived) {
    std::vector<double> res(nonderived.size());
    for (size_t i = 0; i < nonderived.size(); ++i) {
        res[i] = (nonderived[i] > 0) ? 1.0 : 0.0;
    }
    return res;
}

void TensorsNet::backwardPass(const std::vector<double> &outputs, double lr, double moment) {
    const size_t &len_graph = graph.size();
//    graph[len_graph - 1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[len_graph - 1][0].output_values),
//                                                        Matrix::subVecs(outputs, graph[len_graph - 1][0].output_values));
    graph[len_graph - 1][0].grads =
            Matrix::subVecs(outputs, graph[len_graph - 1][0].output_values);

    for (size_t i = len_graph - 1; i > 0; --i) {
        graph[i - 1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[i - 1][0].output_values),
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

void TensorsNet::addConvLayer(size_t num_filter, size_t filters_size) {
    graph.emplace_back();
    for (size_t j = 0; j < num_filter; ++j) {
        graph.back().emplace_back();
        TensorsNet::addLayer(filters_size, filters_size, 1);
    }
}


//при обратном проходе конволюции учесть что я в ините тупанул и перепутал строки со столбцами

void TensorsNet::convForward(const std::vector<double> &inputs, size_t conv_index){
    size_t num_filters = graph[conv_index].size();
    size_t filter_size = graph[conv_index][0].weights.getRows();
    for(size_t i = 0; i < num_filters; ++i){
        graph[conv_index][i].input_values = inputs; //??? можно ли не учитывать
        auto img_shape = static_cast<size_t>(std::sqrt(inputs.size()));
        Matrix img = Matrix::vecReshape(graph[conv_index][i].input_values, img_shape);
        for (size_t j = 0; j < (img_shape - filter_size); ++j) {
            for (size_t k = 0; k < (img_shape - filter_size); ++k) {
                graph[conv_index][i].output_values.push_back(img.convDot(j, j + filter_size-1, k, k+filter_size-1,
                                                                         graph[conv_index][i].weights, graph[conv_index][i].biases[0]));
            }
        }
    }
}
