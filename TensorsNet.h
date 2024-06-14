//
// Created by zxces on 26.03.2024.
//
/**
 * @file TensorsNet.h
 * @brief Заголовочный файл для класса модели нейросети
 */
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
    size_t layer_type;
};

class TensorsNet {
public:
    explicit TensorsNet(const std::vector<size_t>& all_layers);

    /**
     * @brief Performs the forward pass through the network.
     *
     * @param inputs Input values for the forward pass.
     */
    virtual void forwardPass(const std::vector<double>& inputs);

    /**
     * @brief Performs the backward pass (backpropagation) through the network.
     *
     * @param outputs Expected output values.
     * @param lr Learning rate.
     * @param moment Momentum for the gradient update.
     */
    void backwardPass(const std::vector<double>& outputs, double lr, double moment);

    /**
     * @brief Adds a convolutional layer to the network.
     *
     * @param num_filter Number of filters.
     * @param filters_size Size of each filter.
     */
    void addConvLayer(size_t num_filter, size_t filters_size);

    /**
     * @brief Adds a dense layer to the network.
     *
     * @param num_input Number of input neurons.
     * @param num_output Number of output neurons.
     * @param layer_type Type of the layer.
     */
    void addLayer(size_t num_input, size_t num_output, size_t layer_type);

    /**
     * @brief Performs the forward pass for a convolutional layer.
     *
     * @param inputs Input values for the convolutional layer.
     * @param conv_index Index of the convolutional layer in the network.
     */
    void convForward(const std::vector<double>& inputs, size_t conv_index);

    std::vector<std::vector<Layer>> graph;

    /**
     * @brief Applies ReLU activation function to the input values.
     *
     * @param nonactive Input values to be activated.
     */
    static void relu_function(std::vector<double>& nonactive);

    /**
     * @brief Computes the derivative of the ReLU activation function.
     *
     * @param nonderived Input values for which to compute the derivative.
     * @return A vector of derivative values.
     */
    static std::vector<double> relu_function_derived(const std::vector<double>& nonderived);
};

#endif // AIP_PROJECT_2_BUHS_TENSORSNET_H
