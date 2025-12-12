import mpmath as mp
import numpy as np
import os
import inspect
from typing import Tuple, Optional
import subprocess
import sys
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# Config
N = 10000
mp.dps = 50

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

    def run_binary(self):

        result = subprocess.run([
            './bin/' + f'{self.name}'
            ], capture_output=True, text=True)

        if result.stderr:
            print("Error:", result.stderr)
            sys.exit(1)

        print(f"{self.name} run succeed")
        
    def read_points_from_file(self):
        file_path = os.path.join('..', 'points', 'output.txt')
        return np.loadtxt(file_path, dtype=np.float64)

    def generate_points(self):
        # Computing points
        n = int((self.b - self.a) * N)
        points = np.linspace(self.a, self.b, n, endpoint=True)

        # Writing points to input.txt
        with open('../points/input.txt', 'w') as file:
            for point in points:
                file.write(f"{point}\n")

        return points

    def compute_target_values(self, points):
        results = []

        for point in points:
            # Преобразуем вход в mp.mpf для обеспечения точности
            x = mp.mpf(point) if not isinstance(point, mp.mpf) else point
            result = mp.struveh(0, x)  # H0(x)
            results.append(result)

        return np.array(results)
        
    def save_results(self, points, comp_values, target_values):
    
        # Создаем директории, если они не существуют
        reports_dir = Path("./reports")
        plots_dir = Path("./plots")
        reports_dir.mkdir(parents=True, exist_ok=True)
        plots_dir.mkdir(parents=True, exist_ok=True)
    
        # Вычисляем ошибки
        abs_errors = np.abs(comp_values - target_values)
        # Добавляем небольшое число, чтобы избежать деления на ноль
        rel_errors = abs_errors / (np.abs(target_values) + 1e-12)
    
        # Создаем DataFrame с результатами
        results_df = pd.DataFrame({
            'точка': points,
            'вычисленное_значение': comp_values,
            'точное_значение': target_values,
            'абс_ошибка': abs_errors,
            'относ_ошибка': rel_errors
        })
    
        # Сохраняем таблицу в CSV файл
        csv_path = reports_dir / f"{self.name}_results.csv"
        results_df.to_csv(csv_path, index=False, encoding='utf-8')
        print(f"Таблица сохранена: {csv_path}")
    
        # Создаем график относительной ошибки
        plt.figure(figsize=(12, 6))
        
        # Если точек много, используем scatter plot для лучшей визуализации
        if len(points) > 1000:
            plt.scatter(points, rel_errors, s=1, alpha=0.5, label='Относительная ошибка')
        else:
            plt.plot(points, rel_errors, 'b-', linewidth=1, label='Относительная ошибка')
        
        # Настройка графика
        plt.xlabel('Точка (x)', fontsize=12)
        plt.ylabel('Относительная ошибка', fontsize=12)
        plt.title(f'Относительная ошибка для функции {self.name}', fontsize=14)
        plt.grid(True, alpha=0.3)
        plt.yscale('log')  # Логарифмическая шкала для ошибки
        plt.legend(fontsize=10)
        
        # Добавляем статистику
        # stats_text = (f'Средняя отн. ошибка: {np.mean(rel_errors):.2e}\n'
        #             f'Макс. отн. ошибка: {np.max(rel_errors):.2e}\n'
        #             f'Мин. отн. ошибка: {np.min(rel_errors):.2e}')
        # plt.text(0.02, 0.98, stats_text, transform=plt.gca().transAxes,
        #         verticalalignment='top', fontsize=10,
        #         bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8))
    
        # Сохраняем график
        plot_path = plots_dir / f"{self.name}_error_plot.png"
        plt.tight_layout()
        plt.savefig(plot_path, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"График сохранен: {plot_path}")
        
        # Дополнительно: сохраняем статистику в отдельный файл
        stats_df = pd.DataFrame({
            'статистика': ['средняя_абс_ошибка', 'средняя_отн_ошибка', 
                        'макс_абс_ошибка', 'макс_отн_ошибка',
                        'медианная_абс_ошибка', 'медианная_отн_ошибка'],
            'значение': [
                np.mean(abs_errors),
                np.mean(rel_errors),
                np.max(abs_errors),
                np.max(rel_errors),
                np.median(abs_errors),
                np.median(rel_errors)
            ]
        })
        
        stats_path = reports_dir / f"{self.name}_statistics.csv"
        stats_df.to_csv(stats_path, index=False, encoding='utf-8')
        print(f"Статистика сохранена: {stats_path}")


    def test(self):
        print("Start testing " + self.name)

        # source code compilation
        self.compile_src()

        # points generation
        points = self.generate_points()

        self.run_binary()
        comp_values = self.read_points_from_file()
        target_values = self.compute_target_values(points)

        self.save_results(points,  comp_values, target_values)

# List of all available functions
series_0_3 = FunctionTester(0, 3, "series_0_3", "./src/series_0_3.cpp")

# Initialization testing
def main():
    series_0_3.test()

main()