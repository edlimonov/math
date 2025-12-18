#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// This number gives high precision without any extra libraries included
const double PI = 3.14159265358979323846;

double struve_0_3(double x) {
    
    std::vector<double> terms;
    std::vector<int> pow = {1, 3, 5, 7, 9, 11};
    std::vector<int> delimeter = {1, 9, 9 * 25, 9 * 25 * 49, 9 * 25 * 49 * 81, 9 * 25 * 49 * 81 * 121};
    
    for (auto p : pow) {
        terms.push_back(std::pow(x, p));
    }
    
    double res = 0;
    int sign = 1;
    
    for (size_t i = 0; i < pow.size(); i++) {
        res += (2.0 * sign * terms[i]) / ( PI * delimeter[i]);
        sign *= -1;
    }
    
    return res;
}

int main() {
    
    std::ifstream in("/Users/nailzaripov/math/experimental/points/input.txt");
    std::ofstream out("/Users/nailzaripov/math/experimental/points/output.txt");
    
    double point;
    
    while (in >> point) {
        out << struve_0_3(point) << '\n';
    }
    
    return 0;
}
