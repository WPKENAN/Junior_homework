#coding:utf8
from numpy import *
from matplotlib.pyplot import *
from matplotlib.animation import *
import sys

datapath="perceptrondata.txt"
data=genfromtxt(datapath,delimiter=' ');
#print min(data[1,:]),max(data[1,:])

#符号函数
def sign(v):
    if v>0:
        return 1;
    else:
        return -1;

def training(train_datas):

    weight=[1,1]
    bias=0;
    learning_rate=0.05
    wb=[];
#    train_num=int(raw_input("train num: "))
#    print train_datas
    train_num=10000
    for i in range(train_num):
        m,n=shape(train_datas);
        index=random.randint(0,m)
#        index=i%shape(train_datas)[0]
        train=train_datas[index,:];
#        train=random.choice(train_datas);
#        print train
        x1,x2,y=train;
#        print index,weight[0],weight[1],bias,": ",weight[0]*x1+weight[1]*x2+bias
#        print " "
        predict=sign(weight[0]*x1+weight[1]*x2+bias)

        if y*predict>=0:
            weight[0]=weight[0]-y*learning_rate*x1;
            weight[1]=weight[1]-y*learning_rate*x2;
            bias=bias+learning_rate*y;
            wb+=[[weight[0],weight[1],bias]];
#        print x1,x2,":",y,y*predict
#        print " "
    return weight,bias,array(wb);

fig=figure();
window=fig.add_subplot(111)
window.axis([min(data[:,0])-1,max(data[:,0])+1,min(data[:,1])-1,max(data[:,1])+1])
def test(data):
    weight,bias=training(data);
    while True:
        test_data=[];
        data=raw_input("Enter data test (x1,x2):");
        if data=='1':break;
        test_data+=[int(n) for n in data.split(',')]
        predict=sign(weight[0]*test_data[0]+weight[1]*test_data[1]+bias);
#        print predict
#

def picture(weight,bias):
    m,n=shape(data);
    for i in range(m):
        if data[i,2]>0:
            window.scatter(data[i,0],data[i,1],color='red');
        else:
            window.scatter(data[i,0],data[i,1],color='black');
#    x=linspace(min(data[:,0]),max(data[:,1]),1000);
#    window.plot(x,weight[0]/weight[1]*x-bias/weight[1])
#    show()
weight,bias,wb=training(data)
#print shape(wb)
print wb
picture(weight,bias)
x=linspace(min(data[:,0]),max(data[:,0]),1000);
#print x
#x=list(x)
#print 'x',x
m_wb,n_wb=shape(wb);
y=[]
for i in range(m_wb):
    if wb[i,1]==0:
#        y.append()
        continue
    y.append(-x*wb[i,0]/wb[i,1]-wb[i,2]/wb[i,1])

print "start"
#print y
y=array(y)

if shape(y)[0]==0:
    kase=5
    mid=1/2.0*(max(data[0:5,0])+min(data[kase:shape(data)[0],0]))
#    print min(data[1,:]),max(data[1,:])
    plot([mid,mid],[min(data[:,1]),max(data[:,1])])
    show()
else:
    p=min(data[:,0])
    q=max(data[:,0])
#    line,=window.plot(x,y[0,:])
    def update(data):
        line.set_xdata(linspace(p,q,1000));
        line.set_ydata(data);
        return line
#    ani = FuncAnimation(fig, update, y, interval=200)

    plot(x,y[shape(y)[0]-1,:])
    show()










