# -*- coding:Shift_JIS
#VisualStudioでの開発のため、文字コードをShift_JISに設定する。
import matplotlib.pyplot as plt

def setup_graph(target_graph, title, x_label, y_label, datas, line_width):
    x_data = datas[x_label]
    y_datas = []
    y_data_max = 0
    y_data_min = 0
    for y_data_title_index in range(0, len(y_label)):
        y_data_title = y_label[y_data_title_index]
        y_datas.append(datas[y_data_title])

    for data_index in range(0, len(y_datas)):
        if y_data_max < max(y_datas[data_index]):
            y_data_max = max(y_datas[data_index])
        if min(y_datas[data_index]) < y_data_min:
            y_data_min = min(y_datas[data_index])

        target_graph.plot(x_data, y_datas[data_index],linewidth=line_width)

    if 0 < y_data_max:
        y_data_max = y_data_max * 1.3
    else:
        y_data_max = y_data_max * 0.8

    if 0 < y_data_min:
        y_data_min = y_data_min * 0.8
    else:
        y_data_min = y_data_min * 1.3

    target_graph.set_ylim(y_data_min, y_data_max)
    target_graph.set_title(title)
    target_graph.grid(True)
