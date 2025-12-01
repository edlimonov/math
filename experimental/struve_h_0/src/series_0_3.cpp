#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double struve_0_3(double x, const std::vector<double>& powers, const std::vector<double>& coeff) {
    
    std::vector<double> powers_x;
    std::vector<int> pow = {1, 3, 5, 7, 9, 11};
    
    for (auto p : pow) {
        powers_x.push_back(std::pow(x, p));
    }
    
    double res = 0;
    
    for (size_t i = 0; i < coeff.size(); i++) {
        res += coeff[i] * powers_x[i] / powers[i];
    }
    
    return res;
}

int main() {
    
    std::ifstream in("../../points/input.txt");
    std::ofstream out("../../points/output.txt");
    
    double point;
    std::vector<double> powers;
    std::vector<double> coeff = {1.909859164, 1.909855001, 0.687514637, 0.126164557, 0.013828813, 0.000876918};
    std::vector<int> pow = {1, 3, 5, 7, 9, 11};
    
    for (auto p : pow) {
        powers.push_back(std::pow(3, p));
    }
    
    while (in >> point) {
        out << struve_0_3(point, powers, coeff) << '\n';
    }
    
    return 0;
}
