#include <fstream>
#include <iostream>
#include "TrainingLoop.h"


void trainNetwork(TensorsNet &net, const std::vector<std::vector<double>> &train_images,
                  const std::vector<unsigned char> &train_labels, int epochs, double learning_rate, double momentum) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::cout << "Epoch: " << epoch << std::endl;
        double total_loss = 0.0;
        for (size_t i = 0; i < train_images.size(); ++i) {
            // Прямой проход
            net.forwardPass(train_images[i]);

            // Получаем предсказание и вычисляем ошибку
            std::vector<double> target_output(10, 0.0);
            target_output[train_labels[i]] = 1.0;

            // Обратный проход
            std::cout << i << ". ";
            net.backwardPass(target_output, learning_rate, momentum);
        }
    }
    saveWeightsAndBiases(net, "../model/final_weights.txt");
}

void saveWeightsAndBiases(const TensorsNet& net, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& layer : net.graph) {
            for (const auto& node : layer) {
                for (const auto& weight : node.weights.data) {
                    for (const auto& w : weight) {
                        file << w << " ";
                    }
                    file << std::endl;
                }
                for (const auto& bias : node.biases) {
                    file << bias << " ";
                }
                file << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void loadWeightsAndBiases(TensorsNet& net, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for (auto& layer : net.graph) {
            for (auto& node : layer) {
                for (auto& weight : node.weights.data) {
                    for (auto& w : weight) {
                        file >> w;
                    }
                }
                for (auto& bias : node.biases) {
                    file >> bias;
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<double> predict(TensorsNet& net, const std::vector<double>& input_image) {
    net.forwardPass(input_image);
    return net.graph.back().back().output_values;
}


// код для одного изображения
//#include <fstream>
//#include <iostream>
//#include "TrainingLoop.h"
//
//void trainNetwork(TensorsNet& net, const std::vector<std::vector<double>>& train_images, const std::vector<unsigned char>& train_labels, int epochs, double learning_rate, double momentum) {
//    // Используем первое изображение и его метку
//    const std::vector<double>& image = train_images[0];
//    unsigned char label = train_labels[0];
//
//    for (int epoch = 0; epoch < epochs; ++epoch) {
//        std::cout << "Epoch: " << epoch << std::endl;
//
//        // Прямой проход
//        net.forwardPass(image);
//
//        // Получаем предсказание и вычисляем ошибку
//        std::vector<double> target_output(10, 0.0);
//        target_output[label] = 1.0;
//        // Обратный проход
//        net.backwardPass(target_output, learning_rate, momentum);
//        for(int i = 0; i < 10; ++i){
//            std::cout << net.graph[1][0].grads[i] << " ";
//        }
//        std::cout << '\n';
//
//
//        // Сохраняем веса и смещения на каждой итерации
//        std::string filename = "../model/weights_epoch_" + std::to_string(epoch) + ".txt";
//        saveWeightsAndBiases(net, filename);
//
//
//    }
//}
//
//void saveWeightsAndBiases(const TensorsNet& net, const std::string& filename) {
//    std::ofstream file(filename);
//    if (file.is_open()) {
//        for (const auto& layer : net.graph) {
//            for (const auto& node : layer) {
//                for (const auto& weight : node.weights.data) {
//                    for (const auto& w : weight) {
//                        file << w << " ";
//                    }
//                    file << std::endl;
//                }
//                for (const auto& bias : node.biases) {
//                    file << bias << " ";
//                }
//                file << std::endl;
//            }
//        }
//        file.close();
//    } else {
//        std::cerr << "Unable to open file: " << filename << std::endl;
//    }
//}
