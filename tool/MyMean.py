# -*- coding:Shift_JIS
#VisualStudio�ł̊J���̂��߁A�����R�[�h��Shift_JIS�ɐݒ肷��B

def calc_mean(datas, label):
    #   �f�[�^�̌��̎Z�o
    data_num = len(datas[0])
    for datas_index in range(1, len(datas)):
        data = datas[datas_index]
        if len(data) < data_num:
            data_num = len(data)

    mean_data = []
    cnt_data = []
    for data_index in range(0, data_num):
        mean_val = 0
        for datas_index in range(0, len(datas)):
            src_data = datas[datas_index]
            src_value = src_data[label]
            mean_val += src_value[data_index]

        mean_val /= len(datas)
        mean_data.append(mean_val)
        cnt_data.append(data_index)

    return_val = {'CNT':cnt_data, 'MEAN':mean_data}

    return return_val
