# -*- coding:Shift_JIS
#VisualStudio�ł̊J���̂��߁A�����R�[�h��Shift_JIS�ɐݒ肷��B

#   �f�[�^�̑O��̒l�̍������Z�o����
def calc_diff(datas, label):
    #   �f�[�^�̌��̎Z�o
    data_num = len(datas[label])
    diff_data = []
    cnt_data = []
    diff_data.append(0)
    cnt_data.append(0)
    for data_index in range(1, data_num):
        diff_value = 0
        src_datas = datas[label]
        diff_data.append(src_datas[data_index] - src_datas[data_index - 1])
        cnt_data.append(data_index)

    return_val = {'CNT':cnt_data, 'DIFF':diff_data}

    return return_val
