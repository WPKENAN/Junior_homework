#-*- coding:utf-8 -*-

from numpy import *
#from numpy import genfromtxt
import cv2
import sys
import os

path_image="lena.bmp"
path_color=r"color.txt";
path_light=r"light.txt";
light = genfromtxt(path_light,delimiter=' ');
color = genfromtxt(path_color,delimiter=' ');
image=cv2.imread(path_image);
b,g,r=cv2.split(image);

def Yuv(b,g,r):
    b=matrix(b,dtype='int16');
    g=matrix(g,dtype='int16');
    r=matrix(r,dtype='int16');
    m,n=b.shape;
    Y,U,V=r.copy(),g.copy(),b.copy();
    for i in range(m):
        for j in range(n):
            Y[i,j]=0.299*r[i,j]+0.587*g[i,j]+0.114*b[i,j];
            U[i,j]=-0.147*r[i,j]-0.289*g[i,j]+0.436*b[i,j];
            V[i,j]=0.615*r[i,j]-0.515*g[i,j]-0.1*b[i,j];

    Y=matrix(Y,dtype='uint8');
    U=matrix(U,dtype='uint8');
    V=matrix(V,dtype='uint8');
    return Y,U,V
            
def Rgb(y,u,v):
    y=matrix(y,dtype='int16');
    u=matrix(u,dtype='int16');
    v=matrix(v,dtype='int16');
    m,n=y.shape;
    b,g,r=y.copy(),u.copy(),v.copy();
    for i in range(m):
        for j in range(n):
            r[i,j]=1.0*y[i,j]+0+1.148*v[i,j];
            g[i,j]=1.0*y[i,j]-0.395*u[i,j]-0.581*v[i,j];
            b[i,j]=1.0*y[i,j]+2.032*u[i,j]+0.001*v[i,j];

    r=matrix(r,dtype='uint8');
    g=matrix(g,dtype='uint8');
    b=matrix(b,dtype='uint8');
    return b,g,r;
#image_source=image.copy();

m,n=r.shape;
#b=matrix(b,dtype='int16');
#g=matrix(g,dtype='int16');
#r=matrix(r,dtype='int16');
#print r

def Dct(org,isDctCv):
    #行和列补全成为8*8的倍数
    m_old,n_old=org.shape;
    m_new=m_old;
    n_new=n_old;
    if m_old%8>0:
        m_new=m_old+(8-m_old%8);
    if n_old%8>0:
        n_new=n_old+(8-n_old%8);
#    print "m_old=%d,n_old=%d"%(m_old,n_old)
#    print "m_new=%d,n_new=%d"%(m_new,n_new)
    
    #补全生成新的matrix矩阵
    matrix_data=matrix(zeros([m_new,n_new]));
    result=matrix(zeros([m_new,n_new]));
    eight_matrix=matrix(zeros([8,8]));
    translate_matrix=matrix(zeros([8,8]));

    for i in range(m_new):
        for j in range(n_new):
            if i<m_old and j<n_old:
                matrix_data[i,j]=org[i,j];

    #对补全的matrix进行8*8dct运算
    for p in range(m_new/8):
#        print "p:%d"%p
        for q in range(n_new/8):
#            print "q:%d"%q
            for i in range(8):
                for j in range(8):
                    pos_i=i+p*8;
                    pos_j=j+q*8;

                    eight_matrix[i,j]=matrix_data[pos_i,pos_j];

            for i in range(8):
                for j in range(8):
                    pos_i=i+p*8;
                    pos_j=j+q*8;

                    if i==0:
                        a=sqrt(1.0/8);
                    else:
                        a=sqrt(2.0/8);

                    translate_matrix[i,j]=a*cos(pi*(j+0.5)*i/8.0);

	    if isDctCv==0:
            	Y=translate_matrix*eight_matrix*translate_matrix.transpose();
            else:
            	Y=translate_matrix.transpose()*eight_matrix*translate_matrix;

            for i in range(8):
                for j in range(8):
                    pos_i=i+p*8;
                    pos_j=j+q*8;

                    result[pos_i,pos_j]=Y[i,j];


    return result


def put_image(blue,green,red):
    m,n=b.shape;
    for i in range(m):
        for j in range(n):
            if blue[i,j]<0:
                blue[i,j]=0;
            elif blue[i,j]>255:
                blue[i,j]=255;

            if green[i,j]<0:
                green[i,j]=0;
            elif green[i,j]>255:
                green[i,j]=255;
            
            if red[i,j]<0:
                red[i,j]=0;
            elif red[i,j]>255:
                red[i,j]=255;
    blue=matrix(blue,dtype='uint8');        
    green=matrix(green,dtype='uint8');        
    red=matrix(red,dtype='uint8');        
    image=cv2.merge([blue,green,red]);
    
    return image;


def Quantify(Y,U,V,light,color,isQuantify):
    m,n=Y.shape;

    y=matrix(Y.copy(),dtype='int16');
    u=matrix(U.copy(),dtype='int16');
    v=matrix(V.copy(),dtype='int16');
    for i in range(m):
        for j in range(n):
            if isQuantify==0:
                y[i,j]=y[i,j]*1.0/light[i%8,j%8];
                u[i,j]=u[i,j]*1.0/color[i%8,j%8];
                v[i,j]=v[i,j]*1.0/color[i%8,j%8];
            else: 
                y[i,j]=y[i,j]*1.0*light[i%8,j%8];
                u[i,j]=u[i,j]*1.0*color[i%8,j%8];
                v[i,j]=v[i,j]*1.0*color[i%8,j%8];

    return y,u,v




#org=matrix([[61,19,50,20],[82,26,61,45],[89,90,82,43],[93,59,53,97]])

x0=cv2.merge([b.copy(),g.copy(),r.copy()]);
#cv2.imshow("main0",x0);cv2.waitKey(100);

#b=matrix(b,dtype='int16');
#g=matrix(g,dtype='int16');
#r=matrix(r,dtype='int16');

#正变换
b1=Dct(b,0);
g1=Dct(g,0);
r1=Dct(r,0);
x1=put_image(b1.copy(),g1.copy(),r1.copy());
cv2.imshow("dct",x1);cv2.waitKey(100);

#逆变换
#print b1;
b2=matrix(Dct(b1.copy(),1),dtype='uint8');
g2=matrix(Dct(g1.copy(),1),dtype='uint8');
r2=matrix(Dct(r1.copy(),1),dtype='uint8');
x2=cv2.merge([b2.copy(),g2.copy(),r2.copy()]);
cv2.imshow("idct",x2);cv2.waitKey(100);

Y,U,V=Yuv(b.copy(),g.copy(),r.copy())

#b3,g3,r3=Rgb(Y.copy(),U.copy(),V.copy())
#cv2.imshow("rgb",cv2.merge([b3,g3,r3]));cv2.waitKey(0)
#print r3
#cv2.imshow("Y",Y);cv2.waitKey(100);
#cv2.imshow("U",U);cv2.waitKey(100);
#cv2.imshow("V",V);cv2.waitKey(0);

final=cv2.cvtColor(image,cv2.COLOR_YUV2RGB);
out=cv2.cvtColor(final,cv2.COLOR_RGB2YUV);
#cv2.imshow("main0",out[:,:,0]);cv2.waitKey(100);
#cv2.imshow("main1",out[:,:,1]);cv2.waitKey(100);
cv2.imshow("main2",out);cv2.waitKey(0);

print Y,U,V
print "----------------------"
y,u,v=Quantify(Y,U,V,light,color,0);
y,u,v=Quantify(y,u,v,light,color,1);
print Y-y,U-u,V-v


