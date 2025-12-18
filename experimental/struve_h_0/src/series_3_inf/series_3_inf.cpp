#include <boost/math/special_functions/bessel.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// This number gives high precision without any extra libraries included
const double PI = 3.14159265358979323846;

double struve_3_inf(double x) {
    return 2 / (PI * x) + boost::math::cyl_neumann(0, x);
}

int main() {

    std::ifstream in("/Users/nailzaripov/math/experimental/points/input.txt");
    std::ofstream out("/Users/nailzaripov/math/experimental/points/output.txt");

    double point;
    
    while (in >> point) {
        out << struve_3_inf(point) << '\n';
    }

    return 0;
}