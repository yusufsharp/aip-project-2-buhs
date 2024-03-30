//
// Created by pc on 27.03.2024.
//

#ifndef AIP_PROJECT_2_BUHS_DATA_READER_H
#define AIP_PROJECT_2_BUHS_DATA_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
void NormalizeData(std::vector<std::vector<unsigned char >>& images);
std::vector<unsigned char> readLabelFile(const std::string& filename);
std::vector<std::vector<unsigned char>> readImageFile(const std::string& filename);
void printImage(const std::vector<unsigned char>& image, int sideLength);


#endif //AIP_PROJECT_2_BUHS_DATA_READER_H
