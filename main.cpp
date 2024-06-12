#include "data_reader.h"
#include "TensorsNet.h"
#include "TrainingLoop.h"
#include <iostream>



int main() {
    // Чтение данных MNIST
    std::vector<std::vector<double>> train_images = readImageFile("../data/train-images.idx3-ubyte");
    std::vector<unsigned char> train_labels = readLabelFile("../data/train-labels.idx1-ubyte");
    printImage(train_images[228], 28);
    std::cout << "Label: " <<static_cast<int>(train_labels[228]) << std::endl;

    // Определение архитектуры сети: 784 входных нейрона, 128 скрытых нейронов, 10 выходных нейронов
    std::vector<size_t> architecture = {784, 128, 10};
    TensorsNet net(architecture);


    Matrix M1 = Matrix::readMatrix("../learned/weights1.txt");
    Matrix M2 = Matrix::readMatrix("../learned/weights2.txt");
    std::vector<double> V1 = Matrix::readVector("../learned/bias1.txt");
    std::vector<double> V2 = Matrix::readVector("../learned/bias2.txt");

    net.graph[0][0].weights = M1;
    net.graph[0][0].biases = V1;
    net.graph[1][0].weights = M2;
    net.graph[1][0].biases = V2;



    // Обучение сети
    int epochs = 100;
    double learning_rate = 0.01;
    double momentum = 0.9;
    //trainNetwork(net, train_images, train_labels, epochs, learning_rate, momentum);

    return 0;
}