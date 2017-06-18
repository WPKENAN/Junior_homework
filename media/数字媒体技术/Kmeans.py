#coding:utf8
from numpy import *
from matplotlib.pyplot import *

#datapath="colorD.txt"
#data=genfromtxt(datapath,delimiter=' ');
#print shape(data)

def loadDataSet(filename,d):
    return genfromtxt(filename,delimiter=d);

#计算两个向量之间的距离,行向量
def distEclud(vec1,vec2):
    return sqrt(sum(power(vec1-vec2,2)));

#随机生成的初始质心
def randCent(dataSet,k):
    m,n=shape(dataSet);
    centroids=mat(zeros((k,n)));
    for j in range(n):
        minJ=min(dataSet[:,j]);
        rangeJ=float(max(array(dataSet[:,j]))-minJ);
        centroids[:,j]=minJ+rangeJ*random.rand(k,1);
        return centroids;

def kMeans(dataSet,k,distMeas=distEclud,createCent=randCent):
    m,n=shape(dataSet);
    clusterAssment=mat(zeros((m,2)));#记录每一个样本的属于哪一类

    centroids=randCent(dataSet,k);#随机生成初始质心

    clusterChanged=True;
    while clusterChanged:
        clusterChanged=False;
        for i in range(m):
            minDist=inf;
            maxDist=-1;
            for j in range(k):
                distJI=distMeas(centroids[j,:],dataSet[i,:]);
                if distJI < minDist:
                    minDist = distJI;minIndex=j;#划分到j类
            if clusterAssment[i,0]!=minIndex:
                clusterChanged=True;
            clusterAssment[i,:]=minIndex,minDist**2;
#        print centroids;
        
        for cent in range(k):
            ptsInClust=dataSet[nonzero(clusterAssment[:,0].A==cent)[0]];
            centroids[cent,:]=mean(ptsInClust,axis=0);
    return centroids;        
datapath="colorD.txt";
data=loadDataSet(datapath,' ');
data=data[:,1:33];


