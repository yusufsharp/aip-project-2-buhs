//
// Created by yusufsharp on 21.03.2024.
//

#ifndef AIP_PROJECT_2_BUHS_NEURAL_NET_H
#define AIP_PROJECT_2_BUHS_NEURAL_NET_H

#include <vector>
#include <random>
#include <cmath>

struct WeightDW{
    double w;
    double dw;
};

class Neuron{
private:
    constexpr static double lr = 0.1;
    constexpr static double moment = 0.5;
    double output_value;
    std::vector<WeightDW> out_connects;
    unsigned int wire_i;
    double some_grad{};
    static double gen_random();
    static double neuron_activation(double sum);
    static double neuron_activation_derived(double sum);
    [[nodiscard]] double calc_diffs(const std::vector<Neuron> & layer_plus_1) const;


public:
    Neuron(unsigned int num_outs, unsigned int w_i);
    void calc_out(const std::vector<Neuron> &pre_layer);
    void change_value(const double &input);
    [[nodiscard]] double get_value() const;

    void function_calculates_gradients_for_outs(const double & target_i);

    void function_calculates_grads_for_hiddens(const std::vector<Neuron> & layer_plus_1_i);
    //не константа из-за изменений
    void update_weights(std::vector<Neuron> & layer_minus_1) const;

};

class NeuralNet {
private:
    std::vector<std::vector<Neuron>> graph; // номер слоя + номер нейрона
    double sum_err{};

public:
    explicit NeuralNet(const std::vector<unsigned int> &topology);

    void forward_step(const std::vector<double> &inputs);

    void backward_step(const std::vector<double> &targets);

    void eval_net(std::vector<double> &values) const;
};






#endif //AIP_PROJECT_2_BUHS_NEURAL_NET_H
