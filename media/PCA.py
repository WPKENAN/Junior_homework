#-*- coding:utf-8 -*-
import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt

dataPath = r"/home/wpkenan/data.txt"
dataMat = genfromtxt(dataPath, delimiter=' ')
m,n = np.shape(dataMat)
dataMat=dataMat[:,1:n]

def pca(dataMat, rate):
	average = np.mean(dataMat, axis=0) #按列求均值
	
	meanRemoved = dataMat - np.tile(average, (m,1)) #减去均值
	normData = meanRemoved / np.std(dataMat) #标准差归一化
	covMat = np.cov(normData.T)  #求协方差矩阵
#        print covMat
	eigValue, eigVec = np.linalg.eig(covMat) #求协方差矩阵的特征值和特征向量
	k=setK(eigValue, rate);
	
	eigValInd = np.argsort(-eigValue) #返回特征值由大到小排序的下标
	selectVec = np.matrix(eigVec.T[:k]) #因为[:k]表示前k行，因此之前需要转置处理（选择前k个大的特征值）
	finalData = normData * selectVec.T #再转置回来
	return finalData
	
	
def setK(eigValue, rate):
    a=0;
#    print eigValue.sum();
    eigValInd = np.argsort(-eigValue) #返回特征值由大到小排序的下标值
    for i in range(1, eigValue.size+1):
        topK = eigValInd[i-1]
        eigVal = eigValue[topK]
        a = eigVal+a;
        b = eigValue.sum()
#        print i
#        print ":%f"%(a/b)
        if a/b >= rate:
            print "k = %d"%i
            break
    return i

while True:
#    print "请输入信息量："
    rate=input("请输入信息量：");
    if rate==0:
        break;
    finalData = pca(dataMat,rate);
#plt.scatter(dataMat.T[:1],dataMat.T[1:], color='red', s=20)
#plt.scatter(finalData.T[:1],finalData.T[1:], color='blue', s=20)
#plt.show()
#plt.close()
np.savetxt('/home/wpkenan/result.txt',finalData);	
	
	
	
	
