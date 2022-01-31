# -*- coding: utf-8 -*-
"""
Created on Sun Sep 12 14:20:57 2021

@author: ZZJ
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split


df = pd.read_excel('D:\\a_school\\2021JM\\MLPRegressor_代码及数据集\\第三问.xlsx')
df = df.dropna()

df1 = df.values.tolist()

x = np.array(df1)[:,2:8]
y = np.array(df1)[:,1]
x = np.array(x,dtype = 'float')
y = np.array(y,dtype = 'float')

scaler = StandardScaler() # 标准化转换

traffic_feature = x
traffic_target = y

scaler.fit(traffic_feature) # 训练标准化对象
traffic_feature = scaler.transform(traffic_feature) # 转换数据集

feature_train, feature_test, target_train, target_test = train_test_split(traffic_feature, traffic_target, test_size=0.3,random_state=0)

clf = MLPRegressor(activation = 'logistic', solver='lbfgs', 
                   alpha=1e-5,hidden_layer_sizes=(4,), random_state=4,
                   early_stopping = True,max_iter=10000)

# 神经网络输入为1，第一隐藏层神经元个数为4
# solver='logistic',  MLP的求解方法：L-BFGS 在小数据上表现较好，Adam 较为鲁棒，
# SGD在参数调整较优时会有最佳表现（分类效果与迭代次数）,SGD标识随机梯度下降

clf.fit(feature_train,target_train.ravel())

predict_results=clf.predict(feature_test)
print(predict_results)
np.set_printoptions(suppress=True)
print(target_test)
print(clf.score(feature_test, target_test))

plt.figure
plt.plot(range(35),predict_results,'b',label='predict results')
plt.plot(range(35),target_test,'ro',label='target test')
plt.legend()
plt.show()

df_p = pd.read_excel('D:\\a_school\\2021JM\\MLPRegressor_代码及数据集\\第三问.xlsx')

df1_p = df_p.values.tolist()

x_p = np.array(df1_p)[:,2:8]
y_p = np.array(df1_p)[:,10]
x_p = np.array(x_p,dtype = 'float')
y_p = np.array(y_p,dtype = 'float')

scaler = StandardScaler() # 标准化转换
scaler.fit(x_p) # 训练标准化对象
x_p = scaler.transform(x_p) # 转换数据集

predict_results_p=clf.predict(x_p)
print(predict_results_p)

pd.DataFrame(predict_results_p).to_excel('D:\\a_school\\2021JM\\MLPRegressor_代码及数据集\\predict_result.xlsx')




