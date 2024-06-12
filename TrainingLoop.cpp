
// код для всех изображений


#include <fstream>
#include <iostream>
#include "TrainingLoop.h"

void trainNetwork(TensorsNet& net, const std::vector<std::vector<double>>& train_images, const std::vector<unsigned char>& train_labels, int epochs, double learning_rate, double momentum) {
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
            //net.backwardPass(target_output, learning_rate, momentum);

            for(auto & elm : net.graph[1][0].output_values){
                std::cout << elm << " ";
            }
            std::cout << '\n';
            std::cout << static_cast<int>(train_labels[i]) << '\n';


        }
        std::string filename1 = "../learned/weights1.txt";
        std::string filename2 = "../learned/bias1.txt";
        saveWeightsAndBiases(net, filename1, filename2);

    }
}

void saveWeightsAndBiases(const TensorsNet& net, const std::string& filename1, const std::string& filename2) {
    std::ofstream file1(filename1);
    if (file1.is_open()) {
        for (const auto& layer : net.graph) {
            for (const auto& node : layer) {
                for (const auto& weight : node.weights.data) {
                    for (const auto& w : weight) {
                        file1 << w << " ";
                    }
                    file1 << std::endl;
                }
                file1 << std::endl;
            }
        }
        file1.close();
    } else {
        std::cerr << "Unable to open file: " << filename1 << std::endl;
    }
    std::ofstream file2(filename1);
    if (file1.is_open()) {
        for (const auto& layer : net.graph) {
            for (const auto& node : layer) {
                for (const auto& bias : node.biases) {
                    file2 << bias << " ";
                }
                file2 << std::endl;
                file2 << std::endl;
            }
        }
        file2.close();
    } else {
        std::cerr << "Unable to open file: " << filename1 << std::endl;
    }
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
//
//        // Обратный проход
//        net.backwardPass(target_output, learning_rate, momentum);
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
