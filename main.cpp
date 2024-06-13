#include "data_reader.h"
#include "TensorsNet.h"
#include "TrainingLoop.h"
#include <iostream>
#include "predict.h"
#include "program.h"


int main() {

    PaintApp app;
    app.run();


    // Обучение сети
    int epochs = 100;
    double learning_rate = 0.01;
    double momentum = 0.9;
    //trainNetwork(net, train_images, train_labels, epochs, learning_rate, momentum);

    return 0;
}
