#include "data_reader.h"
#include "TensorsNet.h"
#include "TrainingLoop.h"
#include <iostream>

int main() {
    // Чтение данных MNIST
    std::vector<std::vector<double>> train_images = readImageFile("../data/train-images.idx3-ubyte");
    std::cout << train_images.size() << std::endl;
    std::vector<unsigned char> train_labels = readLabelFile("../data/train-labels.idx1-ubyte");

    std::cout << "Label: " << static_cast<int>(train_labels[5]) << std::endl;
    printImage(train_images[5], 28, 28);
    std::cout << std::endl;

    // Определение архитектуры сети: 784 входных нейрона, 128 скрытых нейронов, 10 выходных нейронов
    std::vector<size_t> architecture = {784, 128, 10};
    TensorsNet net(architecture);

    // Обучение сети
    int epochs = 100;
    double learning_rate = 0.01;
    double momentum = 0.9;
    trainNetwork(net, train_images, train_labels, epochs, learning_rate, momentum);

    return 0;
}