#-*- coding:utf8 -*-
from numpy import *
from matplotlib.pyplot import *
import sys
datapath="data.txt"
decisionpath="decisiontable.txt"
datamat=genfromtxt(datapath,delimiter=' ');
decisiontable=genfromtxt(decisionpath,delimiter=' ');
m,n=shape(datamat);

datamat=datamat.reshape(1,m*n);
datamat=sort(datamat);
#print datamat
pw1=0.9;
pw2=0.1;

mu1=-2;sigma1=0.5;
mu2=2;sigma2=2;
#plot(datamat[0,:],datamat[0,:])
#show()
def test():
    x=linspace(-6,6,1000)
    pxw2=1/(sqrt(2*pi)*sigma2)*exp(-1.0/2*(x-mu2)**2/sigma2**2);
    pxw1=1/(sqrt(2*pi)*sigma1)*exp(-1.0/2*(x-mu1)**2/sigma1**2);
    plot(x,pxw1,label="$pxw1$",color="red");
    plot(x,pxw2,label="$pxw2$");
    xlabel("x");
    ylabel("p(x)")
    ylim(0,2.0)
    legend();
    show();
#test()
#类条件
def p1(x):
    return 1/(sqrt(2*pi)*sigma1)*exp(-1.0/2*(x-mu1)**2/sigma1**2);

def p2(x):
    return 1/(sqrt(2*pi)*sigma2)*exp(-1.0/2*(x-mu2)**2/sigma2**2);

#后验概率
def pw1x(x):
#    print "pw1x:",pw1*p1(x)/(pw1*p1(x)+pw2*p2(x))
    return pw1*p1(x)/(pw1*p1(x)+pw2*p2(x))

def pw2x(x):
#    print "pw2x:",pw2*p2(x)/(pw1*p1(x)+pw2*p2(x))
    return pw2*p2(x)/(pw1*p1(x)+pw2*p2(x))


def rw1(x,dtable):
#    print "rw1:",dtable(0,0)*pw1x(x)+dtable(0,1)*pw2x(x);
    return dtable[0,0]*pw1x(x)+dtable[0,1]*pw2x(x);

def rw2(x,dtable):
#    print "rw2:",dtable(1,0)*pw1x(x)+dtable(1,1)*pw2x(x);
    return dtable[1,0]*pw1x(x)+dtable[1,1]*pw2x(x);

def decision(data,dtable):
    print "decision"
    m,n=shape(data);
    kase=zeros([m,n])
    for i in range(m):
        for j in range(n):
            x=data[i,j];
#            print x,p1(x),p2(x),pw1x(x),pw2x(x),rw1(x,dtable),rw2(x,dtable)
            if rw1(data[i,j],dtable)>rw2(data[i,j],dtable):
                kase[i,j]=1;
    return kase


figure(1);
#后验概率图:
y1=zeros([1,m*n]);
y2=y1.copy()
for i in range(1):
    for j in range(m*n):
        y1[i,j]=pw1x(datamat[i,j]);
        y2[i,j]=pw2x(datamat[i,j]);
#print sort(y1)
#print sort(y2)
#print datamat[0,:];
#print y1[0,:];
#x=y1[0,:];
#y=y1[0,:];
#print x.shape;
#print y.shape
#scatter(x,y);
plot(datamat[0,:],y1[0,:],'*-');
plot(datamat[0,:],y2[0,:],'o-',color="red");
title('Min Error Rate')
figure(2)

#最小风险：
y1=zeros([1,m*n]);
y2=y1.copy();
for i in range(1):
    for j in range(m*n):
        y1[i,j]=rw1(datamat[i,j],decisiontable);
        y2[i,j]=rw2(datamat[i,j],decisiontable);
plot(datamat[0,:],y1[0,:],'*-');
plot(datamat[0,:],y2[0,:],'o-',color='red');
title('Min Risk')

#ylim(-1,1)
#print datamat
#print y1
#print y2
#分类图
#print datamat.shape
figure(3)
kase=decision(datamat,decisiontable);
print kase.shape
print datamat.shape
scatter(datamat,kase,color='green',s=20)
title("Case")
show();


