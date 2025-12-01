# import mpmath as mp
import os
import inspect
from typing import Tuple, Optional
import subprocess
import sys

# Config
N = 100
precision = 50

def generate_points(a: float, b: float):
    # Computing points
    len = b - a
    n = int(len * n)
    step = len / (n - 1)

    points = [a + i * step for i in range(n)]

    # Writing points to input.txt
    with open('../points/input.txt', 'w') as file:
        for point in points:
            file.write(f"{point}\n")

    return points

class FunctionTester:

    def __init__(self, a: float, b: float, name: str, source_path: str):
        self.a = float(a)
        self.b = float(b)
        self.name = name
        self.source_path = source_path

    def compile_src(self):
        result = subprocess.run([
            'clang++', '-o', './bin/' + f'{self.name}',
            '-std=c++11',
            self.source_path
            ], capture_output=True, text=True)

        if result.stderr:
            print("Error:", result.stderr)
            sys.exit(1)

        print(f"{self.name} compilation succeed")
        

    # def compute_target_values(points)

    # def save_results(target_values)


    def test(self):
        self.compile_src()
        # points = self.generate_points
        # target_values = self.compute_target_values(points)
        # self.save_results(target_values)

# List of all available functions
series_0_3 = FunctionTester(0, 3, "series_0_3", "./src/series_0_3.cpp")

# Initialization testing
def main():
    print("Start testing")
    series_0_3.test()

main()