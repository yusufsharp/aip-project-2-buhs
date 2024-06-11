#ifndef AIP_PROJECT_2_BUHS_DATA_READER_H
#define AIP_PROJECT_2_BUHS_DATA_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

void NormalizeData(std::vector<std::vector<double>>& images);
std::vector<unsigned char> readLabelFile(const std::string& filename);
std::vector<std::vector<double>> readImageFile(const std::string& filename);
void printImage(const std::vector<double>& image, int sideLength);

#endif //AIP_PROJECT_2_BUHS_DATA_READER_H
