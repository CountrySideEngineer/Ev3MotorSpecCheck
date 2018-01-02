# -*- coding:Shift_JIS
#VisualStudioでの開発のため、文字コードをShift_JISに設定する。
import pandas as pd
import matplotlib.pyplot as plt
import MyGraphDrawer
import MyMean
import MyDiff

from matplotlib.ticker import *

#   ログデータの読出し
log_data_file_names =["Log_001.csv", "Log_002.csv", "Log_003.csv", "Log_004.csv", "Log_005.csv",
                    "Log_006.csv", "Log_007.csv", "Log_008.csv", "Log_009.csv", "Log_010.csv"]
log_data = []
for log_data_file_name_index in range(0, len(log_data_file_names)):
    log_data_file_name = log_data_file_names[log_data_file_name_index]
    log_data_file_path = "datas/" + log_data_file_name
    new_log_data = pd.read_csv(log_data_file_path)
    log_data.append(new_log_data)

#   各平均値の算出
target_mean_data = MyMean.calc_mean(log_data, 'TARGET')
current_mean_data = MyMean.calc_mean(log_data, 'CURRENT')
counts_mean_data = MyMean.calc_mean(log_data, 'COUNTS')

#   モーターの角度の平均値から、角度/角速度を算出
counts_diff_data = MyDiff.calc_diff(counts_mean_data, 'MEAN')
diff_value = counts_diff_data['DIFF']
rpm_values = []
for data_index in range(0, len(counts_diff_data['CNT'])):
    rpm_values.append(diff_value[data_index] * 600 / 360)
rpm_data = {'CNT':counts_diff_data['CNT'], 'RPM':rpm_values}

#   計算結果のグラフへの出力
#   目標値と現在値
mean_data_graph, axs2 = plt.subplots(ncols = 1, nrows = 1)
MyGraphDrawer.setup_graph(axs2,
    'mean',
    'CNT',
    ['MEAN'],
    current_mean_data,
    0.5)
MyGraphDrawer.setup_graph(axs2,
    'mean',
    'CNT',
    ['MEAN'],
    target_mean_data,
    0.5)
axs2.yaxis.set_major_formatter(FormatStrFormatter('%d %%'))

#   全データを、個別のグラフへ出力
log_data_index = 0
log_data_graph, axs1 = plt.subplots(ncols=2, nrows=5, figsize=(8, 6))
for row_index in range(0, 5):
    for col_index in range(0, 2):
        axs = axs1[row_index][col_index]
        MyGraphDrawer.setup_graph(axs,
            'data',
            'CNT',
            ['TARGET', 'CURRENT'],
            log_data[log_data_index],
            0.5)
        log_data_index += 1
        axs.yaxis.set_major_formatter(FormatStrFormatter('%d %%'))

log_data_graph.tight_layout()

#   角度の変化と回転数
diff_data_graph, axs3 = plt.subplots(ncols=1, nrows=2)
MyGraphDrawer.setup_graph(axs3[0],
    'diff',
    'CNT',
    ['DIFF'],
    counts_diff_data,
    0.5)
MyGraphDrawer.setup_graph(axs3[1],
    'rpm',
    'CNT',
    ['RPM'],
    rpm_data,
    0.5)
axs3[0].yaxis.set_major_formatter(FormatStrFormatter('%d deg'))
axs3[1].yaxis.set_major_formatter(FormatStrFormatter('%d RPM'))

plt.show()

#   表示したグラフを画像で保存する。
mean_data_graph.savefig('datas/mean_data.png')
log_data_graph.savefig('datas/log_data.png')
diff_data_graph.savefig('datas/diff_data.png')
