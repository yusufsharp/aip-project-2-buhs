//
// Created by zxces on 26.03.2024.
//

#include "TensorsNet.h"
TensorsNet::TensorsNet() = default;

TensorsNet::TensorsNet(const std::vector<size_t> &all_layers) {
    for (size_t l = 0; l < all_layers.size() - 1; ++l) {
        TensorsNet::addLayer(all_layers[l], all_layers[l + 1], 0);
    }
};

void TensorsNet::addLayer(size_t num_input, size_t num_output, size_t layer_type) {
    if(layer_type == 0){
        graph.emplace_back().emplace_back();
    }

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
    if(graph[0][0].layer_type == 1){
        //реализовать релу
        TensorsNet::convForward(inputs, 0);
    }
    else {
        graph[0][0].input_values = inputs;
        graph[0][0].output_values = Matrix::sumVecs(graph[0][0].weights.dotVector(inputs), graph[0][0].biases);
        relu_function(graph[0][0].output_values);
    }
    for (size_t i = 1; i < graph.size(); ++i) {
        if(graph[i][0].layer_type == 1){
            //реализовать релу
            TensorsNet::convForward(inputs, i);
        }
        else {
            if(graph[i-1][0].layer_type == 1){
                std::vector<double> inputs_from_conv;
                for(auto & outs : graph[i-1]){
                    inputs_from_conv.insert(inputs_from_conv.end(), outs.output_values.begin(), outs.output_values.end());
                }
                graph[i][0].input_values = inputs_from_conv;
            }
            else {
                graph[i][0].input_values = graph[i - 1][0].output_values;
            }
            graph[i][0].output_values = Matrix::sumVecs(graph[i][0].weights.dotVector(graph[i][0].input_values),
                                                        graph[i][0].biases);
            relu_function(graph[i][0].output_values);
        }
    }
}

void TensorsNet::relu_function(std::vector<double> &nonactive) {
    for (double &elm: nonactive) {
//        if(elm <= 0){
//            elm = 0;
//        }
        elm = 1.0 / (1.0 + std::exp(-elm));
    }
}

std::vector<double> TensorsNet::relu_function_derived(const std::vector<double> &nonderived) {
    std::vector<double> res;
    for (const double &elm: nonderived) {
//        if(elm <= 0){
//            res.push_back(0);
//        }
//        else{
//            res.push_back(1);
//        }
        double temp = 1.0 / (1.0 + std::exp(-elm));
        res.push_back(temp * (1.0 - temp));
    }
    return res;
}

void TensorsNet::backwardPass(const std::vector<double> &outputs, double lr, double moment) {
    const size_t &len_graph = graph.size();
    size_t ifconv = 0;
    //loss function
    graph[len_graph - 1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[len_graph - 1][0].output_values),
                                                        Matrix::subVecs(outputs,
                                                                        graph[len_graph - 1][0].output_values));

    for (size_t i = len_graph - 1; i > 0; --i) {
        if(graph[i - 1][0].layer_type == 0) {
            graph[i - 1][0].grads = Matrix::eachmulVecs(relu_function_derived(graph[i - 1][0].output_values),
                                                        graph[i][0].weights.t().dotVector(graph[i][0].grads));
        }
        else{
            auto o_grads = graph[i][0].weights.t().dotVector(graph[i][0].grads);
            ifconv = i - 1;
            TensorsNet::convBackward(ifconv, o_grads, true, lr, moment);
            for(size_t j = i - 2; j > 0; --j){
                TensorsNet::convBackward(j, {0}, false, lr, moment);
            }
            break;
        }
    }

    for (size_t i = ifconv + 1; i < len_graph; ++i) {
        Matrix M = Matrix::ij_mul(graph[i][0].input_values, graph[i][0].grads).t().scalarMul(1 - moment).scalarMul(lr);
        Matrix dM = graph[i][0].d_weights.scalarMul(moment);
        graph[i][0].d_weights = M.add(dM);
        graph[i][0].weights = graph[i][0].weights.add(graph[i][0].d_weights);

        std::vector<double> b = Matrix::scalarMulVec(Matrix::scalarMulVec(graph[i][0].grads, (1 - moment)), lr);
        std::vector<double> db = Matrix::scalarMulVec(graph[i][0].d_biases, moment);
        graph[i][0].d_biases = Matrix::sumVecs(b, db);
        graph[i][0].biases = Matrix::sumVecs(graph[i][0].d_biases, graph[i][0].biases);
    }
    for (const double &i: graph.back().back().output_values) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

//каким образом создать сеть непосредственно с конволюции?
void TensorsNet::addConvLayer(size_t num_filter, size_t filters_size) {
    graph.emplace_back();
    for (size_t j = 0; j < num_filter; ++j) {
        graph.back().emplace_back();
        TensorsNet::addLayer(filters_size, filters_size, 1);
    }
}

//при обратном проходе конволюции учесть что я в ините тупанул и перепутал строки со столбцами
//работает только с квадратными изображениями
void TensorsNet::convForward(const std::vector<double> &inputs, size_t conv_index) {
    size_t num_filters = graph[conv_index].size();
    size_t filter_size = graph[conv_index][0].weights.getRows();
    for (size_t i = 0; i < num_filters; ++i) {

        if(conv_index == 0) {
            graph[conv_index][i].input_values = inputs; //??? можно ли не учитывать
        }
        else{
            graph[conv_index][i].input_values = graph[conv_index - 1][i].output_values;
        }
        auto img_shape = static_cast<size_t>(std::sqrt(graph[conv_index][i].input_values.size()));
        Matrix img = Matrix::vecReshape(graph[conv_index][i].input_values, img_shape);
        graph[conv_index][i].output_values.clear();
        for (size_t j = 0; j < (img_shape - filter_size + 1); ++j) {
            for (size_t k = 0; k < (img_shape - filter_size + 1); ++k) {
                graph[conv_index][i].output_values.push_back(img.convDot(j, j + filter_size - 1, k, k + filter_size - 1,
                                                                         graph[conv_index][i].weights,0));
            }
        }
        relu_function(graph[conv_index][i].output_values);
    }
}
//для прямого прохода нужно сделать reshape нейронов. upd: сделал
//после фильтра необходимо сделать relu на выходные данные

void TensorsNet::convBackward(size_t conv_index, std::vector<double> before_grads, bool last, double lr, double moment){
    size_t num_filters = graph[conv_index].size();
    size_t filter_size = graph[conv_index][0].weights.getRows();

    for (size_t i = 0; i < num_filters; ++i) {
        auto img_shape = static_cast<size_t>(std::sqrt(graph[conv_index][i].input_values.size()));
        size_t out_shape = img_shape - filter_size + 1;

        Matrix img = Matrix::vecReshape(graph[conv_index][i].input_values, img_shape);

        graph[conv_index][i].grads.clear();
        std::vector<double> out;
        if(last){
            int all_pixs = static_cast<int>(graph[conv_index][i].output_values.size());
            std::vector<double> extracted;
            extracted.assign(before_grads.begin(), before_grads.begin() + all_pixs);
            before_grads.erase(before_grads.begin(), before_grads.begin() + all_pixs);
            out = Matrix::eachmulVecs(relu_function_derived(graph[conv_index][i].output_values), extracted);
        }
        else{
            out = Matrix::eachmulVecs(relu_function_derived(graph[conv_index][i].output_values),
                                           graph[conv_index][i].input_values);
        }


        Matrix out_grads = Matrix::vecReshape(out, out_shape);
        for (size_t j = 0; j < (img_shape - out_shape + 1); ++j) {
            for (size_t k = 0; k < (img_shape - out_shape + 1); ++k) {
                graph[conv_index][i].grads.push_back(img.convDot(j, j + out_shape - 1, k, k + out_shape - 1,
                                                                         out_grads, 0));

            }
        }
        graph[conv_index][i].input_values.clear();
        for (size_t j = 0; j < (out_shape - filter_size + 1); ++j) {
            for (size_t k = 0; k < (out_shape - filter_size + 1); ++k) {
                graph[conv_index][i].input_values.push_back(out_grads.convDot(j, j + filter_size - 1, k, k + filter_size - 1,
                                                                              Matrix::mirrored(graph[conv_index][i].weights, filter_size), 0));
            }
        }

        // grads пусть будет не у фильтров а входного изображения
        Matrix F_d = Matrix::vecReshape(graph[conv_index][i].grads, filter_size);
        F_d = F_d.scalarMul(1 - moment).scalarMul(lr);
        Matrix dF_d = graph[conv_index][i].d_weights.scalarMul(moment);
        graph[conv_index][i].d_weights = F_d.add(dF_d);
        graph[conv_index][i].weights = graph[conv_index][i].weights.add(graph[conv_index][i].d_weights);

        // итого при обратной свертке получается свертка размером с фильтр.
        // смещение - сумма всех градиентов из l+1 слоя
        // также необходимо отдельно возвращать градиенты изображения, помимо фильтра
        // вероятно через return
        // так проделываем со всеми фильтрами
        // необходимо добавить пулинг
        // необходимо передавать ошибку в линейный както
        // input output Обучать не надо
    }
}