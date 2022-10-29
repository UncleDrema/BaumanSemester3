#!/bin/python3
import sys
import random

try:
    rows = int(sys.argv[1])
    cols = int(sys.argv[2])
    percent = float(sys.argv[3])
    file = sys.argv[4]
    with open(file, "w") as f_out:
        percent = percent / 100
        if percent <= 0 or percent > 1.0:
            raise Exception('wrong percent, <0 or >100')
        row_percent = percent / rows
        total = 0
        res_str = ''
        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                if random.random() < percent:
                    val = 0
                    while val == 0:
                        val = random.randrange(-1000, 1000)
                    res_str += f'{i} {j} {val}\n'
                    total += 1
        f_out.write(f'{rows} {cols} {total}\n')
        f_out.write(res_str)
        print('Result percent: ', total / (rows * cols))
except Exception as e:
    print(f'Ошибка в аргументах! Использование: {sys.argv[0]} <строк> <столбцов> <процент заполнения>')