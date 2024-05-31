//
// Created by zxces on 26.03.2024.
//
#pragma once

#include "matrix.h"

#ifndef AIP_PROJECT_2_BUHS_TENSORSNET_H
#define AIP_PROJECT_2_BUHS_TENSORSNET_H


struct Layer {
    Matrix weights;
    Matrix d_weights;
    std::vector<double> biases;
    std::vector<double> d_biases;
    std::vector<double> output_values;
    std::vector<double> grads;
    std::vector<double> input_values;
};


class TensorsNet {
public:
    explicit TensorsNet(const std::vector<size_t> &all_layers);

    void forwardPass(const std::vector<double> &inputs);

    void backwardPass(const std::vector<double> &outputs, double lr, double moment);

private:
    //с учетом фильтра
    std::vector<std::vector<Layer>> graph;

    static void relu_function(std::vector<double> &nonactive);

    static std::vector<double> relu_function_derived(const std::vector<double> &nonderived);
};


#endif //AIP_PROJECT_2_BUHS_TENSORSNET_H
