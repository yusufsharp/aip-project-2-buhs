//
// Created by yusufsharp on 21.03.2024.
//
#include "neural_net.h"
#include <vector>
#include <random>
#include <cmath>


//Функция статична в классе, если она не зависит от состояния конкретного объекта этого класса.
//Вместо этого, она может работать только с параметрами, переданными ей в качестве аргументов.

struct WeightAndGrad{
    double w;
    double w_grad;
};

class Neuron{
private:
    double output_value;
    std::vector<WeightAndGrad> out_connects;
    unsigned int wire_i;
    static double gen_random(){ //генерация от 0 до 1
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 1.0);

        return dis(gen);
    }
    static double neuron_activation(double sum){
        return 1.0 / (1.0 + std::exp(-sum));
    }
    static double neuron_activation_derived(double sum){
        double sigma = neuron_activation(sum); // гигачад сигмамейл патрик бэйтмен качалка зож тун ту дун туннн ту ду дун
        return sigma * (1.0 - sigma);
    }

public:
    void calc_out(const std::vector<Neuron> &pre_layer){
        double calc_sum = 0;
        for (const Neuron & neuron_i : pre_layer) {
            calc_sum += neuron_i.get_value() * neuron_i.out_connects[wire_i].w;
        }

        //функция активации: в будущем сделаю разные и отдельно от класса
        output_value = Neuron::neuron_activation(calc_sum);

    }
    void change_value(const double &input){ output_value = input; }
    [[nodiscard]] double get_value() const { return output_value; }

    Neuron(unsigned int num_outs, unsigned int w_i){
        for(unsigned int i = 0; i < num_outs; ++i) {
            out_connects.emplace_back();
            out_connects.back().w = gen_random();
        }
        wire_i = w_i;
        output_value = 0; //???
    };

};

class NeuralNet {
private:
    std::vector<std::vector<Neuron>> graph; // номер слоя + номер нейрона

public:
    explicit NeuralNet(const std::vector<unsigned int> &topology){
        unsigned int top_size = topology.size();
        for(size_t t = 0; t < top_size; ++t){
            graph.emplace_back();

            unsigned int num_outs;
            if(t == top_size - 1){
                num_outs = topology[t+1];
            }
            else{
                num_outs = 0;
            }

            for (unsigned int i = 0; i < t + 1; ++i) { // мы включаем bias (+1)
                graph.back().emplace_back(num_outs, i);
            }
        }
    };

    void forward_step(const std::vector<double> &inputs){
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

    void backward_step(const std::vector<double> &targets){

    };

    void eval_net(const std::vector<double> &values) const{

    };
};