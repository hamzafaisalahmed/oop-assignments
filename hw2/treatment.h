#pragma once
#include <iostream>
#include <string>

struct Treatment
{
    std::string name;
    double cost;
    std::string doctorName;
    Treatment(std::string n, double c, std::string dn) : name(n), cost(c), doctorName(dn) {}
    void print() const { std::cout << "Treatment: " << name << ", Cost: " << cost << ", Doctor: " << doctorName << std::endl; }
};