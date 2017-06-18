#coding:utf8
from numpy import *
from matplotlib.pyplot import *
import sys

datapath="fisherdata.txt"
data=genfromtxt(datapath,delimiter=' ');

#列表示维，行表示样本数量
def fisher(data1,data2):
    m1,n1=shape(data1);
    m2,n2=shape(data2);
    if(n1!=n2):
        print "Data1 must is the same array as data2!"
        return 

    M1=average(data1,axis=0);
    M2=average(data2,axis=0);
    Sw1=cov(transpose(data1));
    Sw2=cov(transpose(data2));
    print shape(Sw1)
    lammda=1e-16
    Sw=Sw1+Sw2+lammda*eye(n1);
    return array(linalg.inv(Sw).dot(M1-M2))


data1=array([[0,0],[0,2],[2,0],[2,2]]);
data2=array([[4,4],[4,6],[6,4],[6,6]]);
W=fisher(data1,data2);

print data1[:,0]
print data1[:,1]
scatter(data1[:,0],data1[:,1],color='red',label='Kase1');
scatter(data2[:,0],data2[:,1],color='blue',label='Kase2');
if W[0]!=0:
    x=linspace(-10,10,1000)
    y=x*1.0*W[1]/W[0]
    plot(x,y,color='green',label='Fisher')
else:
    x=zeros(100)
    y=linspace(-10,10,1000)
    plot(x,y,color='green')
title("Fisher")
legend(); 
show(); 
    
