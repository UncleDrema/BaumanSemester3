import json
import matplotlib.pyplot as plt
import dataclasses
from typing import List, Dict


@dataclasses.dataclass
class MeasureData:
    size: int
    times: int
    measured_time: float

path = '../../out/benchmark.json'
case = 'average'
title = 'Случайно заполненный массив'
with open(path) as f_in:
    dump = json.load(f_in)

    sort_names: List[str] = ['mysort', 'qsort']

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

    x: List[int] = list(map(lambda x: x.size, sorts['mysort'][case]))
    mysort_y: List[float] = []
    qsort_y: List[float] = []
    for measure in sorts['mysort'][case]:
        mysort_y.append(measure.measured_time)
    for measure in sorts['qsort'][case]:
        qsort_y.append(measure.measured_time)

    plt.plot(x, mysort_y, 'r', label='mysort')
    plt.plot(x, qsort_y, 'b', label='qsort')
    plt.legend(loc='upper left')
    plt.xlabel('Размер массива')
    plt.ylabel('Время сортировки, мс')
    plt.title(title)
    plt.show()
