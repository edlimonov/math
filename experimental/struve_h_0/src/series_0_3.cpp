#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// This number gives high precision without any extra libraries included
const double PI = 3.14159265358979323846;

double struve_0_3(double x, const std::vector<double>& coeff) {
    
    std::vector<double> terms;
    std::vector<int> pow = {1, 3, 5, 7, 9, 11};
    
    for (auto p : pow) {
        terms.push_back(std::pow(x / 3.0, p));
    }
    
    double res = 0;
    int sign = 1;
    
    for (size_t i = 0; i < coeff.size(); i++) {
        res += coeff[i] * terms[i] * sign;
        sign *= -1;
    }
    
    return res;
}

int main() {
    
    std::ifstream in("/Users/nailzaripov/math/experimental/points/input.txt");
    std::ofstream out("/Users/nailzaripov/math/experimental/points/output.txt");
    
    double point;
    std::vector<double> coeff = {1.909859164, 1.909855001, 0.687514637, 0.126164557, 0.013828813, 0.000876918};
    
    while (in >> point) {
        out << struve_0_3(point, coeff) << '\n';
    }
    
    return 0;
}
