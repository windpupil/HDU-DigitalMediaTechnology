input_image=imread('lena.jpg');    %读入一幅图像  
F=imnoise(input_image,'salt & pepper',0.1); %加入椒盐噪声
w=[1,2,1;2,4,2;1,2,1];
w=1/16*w;                %设置加权矩阵模板w
[m,n]=size(F);             %确定矩阵F的大小即原图像的行和列
g=zeros(size(F));           %平滑后的图像g
% 为了节省存储空间，matlab为图像提供了特殊的数据类型uint8(8位无符号整数），以此方式存储的图像称作8位图像。
% matlab读入图像的数据是uint8，而matlab中数值一般采用double型（64位）运算。
% 运算的时候将原图像的灰度值转换成double的作用主要是考虑计算过程中的精度的问题，double的数据是有小数点的，
% 而uint8是0－255的整数，如果直接用uint8计算，会在计算过程中产生舍入误差，这种误差在图像的数据中是比较大的误差。
F1=double(F);

for x=1:m
    for y=1:n
        if(x==1||y==1||x==m||y==n)
            g(x,y)=F(x,y);
        else
            g(x,y)=w(1,1)*F1(x-1,y-1)+w(1,2)*F1(x-1,y)+w(1,3)*F1(x-1,y+1)+w(2,1)*F1(x,y-1)+w(2,2)*F1(x,y)+w(2,3)*F1(x,y+1)+w(3,1)*F1(x+1,y-1)+w(3,2)*F1(x+1,y)+w(3,3)*F1(x+1,y+1);
        end
    end
end

figure;
imshow(input_image);
title('original image');

figure; 
imshow(uint8(F)); 
title('noisy image');

figure;
imshow(uint8(g));
title('neighborhood average image');


