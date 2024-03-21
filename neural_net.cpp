//
// Created by yusufsharp on 21.03.2024.
//
#include "neural_net.h"
#include <vector>
#include <random>


struct WeightAndGrad{
    double w;
    double w_grad;
};

class Neuron{
private:
    double output_value;
    std::vector<WeightAndGrad> out_connects;
    static double gen_random(){ //генерация от 0 до 1
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 1.0);

        return dis(gen);
    }

public:
    Neuron(unsigned int num_outs){
        for(unsigned int i = 0; i < num_outs; ++i){
            out_connects.emplace_back();
            out_connects.back().w = gen_random();
        }
    };

};

class NeuralNet {
private:
    std::vector<std::vector<Neuron>> all_layers; // номер слоя + номер нейрона

public:
    NeuralNet(const std::vector<unsigned int> &topology){
        unsigned int top_size = topology.size();
        for(unsigned int t = 0; t < top_size; ++t){
            all_layers.emplace_back();

            unsigned int num_outs;
            if(t == top_size - 1){
                num_outs = topology[t+1];
            }
            else{
                num_outs = 0;
            }

            for (unsigned int i = 0; i < t + 1; ++i) { // мы включаем bias (+1)
                all_layers.back().emplace_back(num_outs);
            }
        }
    };

    void forward_step(const std::vector<double> &inputs){

    };

    void backward_step(const std::vector<double> &targets){

    };

    void eval_net(const std::vector<double> &values) const{

    };
};