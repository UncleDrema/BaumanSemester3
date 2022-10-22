import json
import matplotlib.pyplot as plt
import dataclasses
from typing import List, Dict


@dataclasses.dataclass
class MeasureData:
    size: int
    times: int
    measured_time: float

path = '../benchmark.json'
case = 'average'
titles = {
    'average': 'Случайно заполненный массив',
    'bad': 'Отсортированный в обратном порядке массив',
    'good': 'Отсортированный массив'
}
title = 'Случайно заполненный массив'
with open(path) as f_in:
    dump = json.load(f_in)

    sort_names: List[str] = ['mysort', 'qsort', 'old_mysort']

    sorts: Dict[str, Dict[str, List[MeasureData]]] = {}
    for sort_name in sort_names:
        sorts[sort_name] = {
            'good': [],
            'bad': [],
            'average': []
        }

    for measure in dump:
        for sort_name in sort_names:
            sorts[sort_name][measure['case']].append(
                MeasureData(measure['size'], measure['times'], measure['results'][sort_name]))

    for case in ['good', 'bad', 'average']:
        x: List[int] = list(map(lambda x: x.size, sorts['mysort'][case]))
        mysort_y: List[float] = []
        qsort_y: List[float] = []
        old_mysort_y: List[float] = []
        for measure in sorts['mysort'][case]:
            mysort_y.append(measure.measured_time)
        for measure in sorts['qsort'][case]:
            qsort_y.append(measure.measured_time)
        for measure in sorts['old_mysort'][case]:
            old_mysort_y.append(measure.measured_time)

        plt.plot(x, mysort_y, 'r', label='mysort')
        plt.plot(x, qsort_y, 'b', label='qsort')
        plt.legend(loc='upper left')
        plt.xlabel('Размер массива')
        plt.ylabel('Время сортировки, мс')
        plt.title(titles[case])
        plt.show()

        plt.plot(x, mysort_y, 'r', label='mysort')
        plt.plot(x, old_mysort_y, 'b', label='old_mysort')
        plt.legend(loc='upper left')
        plt.xlabel('Размер массива')
        plt.ylabel('Время сортировки, мс')
        plt.title(titles[case])
        plt.show()

        plt.plot(x, old_mysort_y, 'r', label='old_mysort')
        plt.plot(x, qsort_y, 'b', label='qsort')
        plt.legend(loc='upper left')
        plt.xlabel('Размер массива')
        plt.ylabel('Время сортировки, мс')
        plt.title(titles[case])
        plt.show()

        plt.plot(x, mysort_y, 'g', label='mysort')
        plt.plot(x, old_mysort_y, 'r', label='old_mysort')
        plt.plot(x, qsort_y, 'b', label='qsort')
        plt.legend(loc='upper left')
        plt.xlabel('Размер массива')
        plt.ylabel('Время сортировки, мс')
        plt.title(titles[case])
        plt.show()

