//
// Created by yusufsharp on 21.03.2024.
//
#include "neural_net.h"
#include <vector>
#include <random>
#include <cmath>


//Функция статична в классе, если она не зависит от состояния конкретного объекта этого класса.
//Вместо этого, она может работать только с параметрами, переданными ей в качестве аргументов.



double Neuron::gen_random(){ //генерация от 0 до 1
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}
double Neuron::neuron_activation(double sum){
    return 1.0 / (1.0 + std::exp(-sum));
}
double Neuron::neuron_activation_derived(double sum){
    double sigma = neuron_activation(sum); // гигачад сигмамейл патрик бэйтмен качалка зож тун ту дун туннн ту ду дун
    return sigma * (1.0 - sigma);
}

[[nodiscard]] double Neuron::calc_diffs(const std::vector<Neuron> & layer_plus_1) const{
    double sum = 0.0;
    for(size_t i = 0; i < layer_plus_1.size(); ++i){
        sum += out_connects[i].w * layer_plus_1[i].some_grad;
    }
    return sum;
}



void Neuron::calc_out(const std::vector<Neuron> &pre_layer){
    double calc_sum = 0;
    for (const Neuron & neuron_i : pre_layer) {
        calc_sum += neuron_i.get_value() * neuron_i.out_connects[wire_i].w;
    }

    //функция активации: в будущем сделаю разные и отдельно от класса
    output_value = Neuron::neuron_activation(calc_sum);
}
void Neuron::change_value(const double &input){ output_value = input; }
[[nodiscard]] double Neuron::get_value() const{
    return output_value;
}

Neuron::Neuron(unsigned int num_outs, unsigned int w_i){
    for(unsigned int i = 0; i < num_outs; ++i) {
        out_connects.emplace_back();
        out_connects.back().w = gen_random();
    }
    wire_i = w_i;
    output_value = 0; //???
};

void Neuron::function_calculates_gradients_for_outs(const double & target_i){
    double delta = target_i - output_value;
    some_grad = delta * Neuron::neuron_activation_derived(output_value);
}

void Neuron::function_calculates_grads_for_hiddens(const std::vector<Neuron> & layer_plus_1_i){
    //сумма дифференциалов весов следующего слоя
    double sum_diffs = calc_diffs(layer_plus_1_i);
    some_grad = sum_diffs *  Neuron::neuron_activation_derived(output_value);
}
//не константа из-за изменений


void Neuron::update_weights(std::vector<Neuron> & layer_minus_1) const{
    for(Neuron & n : layer_minus_1){
        //здесь реализация с импульсом
        double old_d_weight = n.out_connects[wire_i].dw;
        double cur_d_weight = lr * n.output_value * some_grad + moment * old_d_weight;

        n.out_connects[wire_i].dw = cur_d_weight;
        n.out_connects[wire_i].w += cur_d_weight;
    }
}




NeuralNet::NeuralNet(const std::vector<unsigned int> &topology){
        unsigned int top_size = topology.size();
        for(size_t t = 0; t < top_size; ++t){
            graph.emplace_back();

            unsigned int num_outs;
            if(t == top_size - 1){
                num_outs = 0;
            }
            else{
                num_outs = topology[t+1];
            }

            for (unsigned int i = 0; i < topology[t] + 1; ++i) { // мы включаем bias (+1)
                graph.back().emplace_back(num_outs, i);
            }
        }
    };

void NeuralNet::forward_step(const std::vector<double> &inputs){
    //входной слой
    for (size_t i = 0; i < inputs.size(); ++i) {
        graph[0][i].change_value(inputs[i]);
    }
    //скрытый слой
    for (size_t layer_i = 1; layer_i < graph.size(); ++layer_i) {
        std::vector<Neuron> &pre_layer = graph[layer_i - 1];
        for (size_t neuron_i = 0; neuron_i < graph[layer_i].size() - 1; ++neuron_i) {
            //ему нужно перебрать нейроны пред. слоя
            graph[layer_i][neuron_i].calc_out(pre_layer);
        }
    }
};

void NeuralNet::backward_step(const std::vector<double> &targets){
    std::vector<Neuron> &outputs = graph.back();
    sum_err = 0.0;
    //здесь считаем ошибку выхода
    for (size_t i = 0; i < outputs.size(); ++i) {
        double diff = targets[i] - outputs[i].get_value();
        sum_err += diff * diff; //здесь используем MSE ошибки
    }
    sum_err /= static_cast<double>(outputs.size() - 1); // опять таки bias
    sum_err = sqrt(sum_err);

    // здесь считаем градиенты выхода учитывая функцию активации
    for (size_t i = 0; i < outputs.size() - 1; ++i) {
        outputs[i].function_calculates_gradients_for_outs(targets[i]);

    }

    // легендарный обратный проход в ноги (backpropagation)
    for (size_t i = graph.size() - 2; i >= 1; --i){
        std::vector<Neuron> & cur_layer = graph[i];
        std::vector<Neuron> & layer_plus_1  = graph[i+1];

        for (Neuron & j : cur_layer) {
            j.function_calculates_grads_for_hiddens(layer_plus_1); //????????

        }
    }

    //ну норм теперь надо обновить ВСЕ нейрончики
    for (size_t i = graph.size() - 1; i >= 1; --i) {
        std::vector<Neuron> & cur_layer = graph[i];
        std::vector<Neuron> & layer_minus_1  = graph[i-1];
        // обновляем связи, которые закрепелены за ПРЕДЫДУЩИМ слоем!
        for (Neuron & j : cur_layer) {
            j.update_weights(layer_minus_1);
        }
    }

};

void NeuralNet::eval_net(std::vector<double> &values) const{
    values.clear();

    for(size_t i = 0; i < graph.back().size() - 1; ++i){
        values.push_back(graph.back()[i].get_value());
    }
};
