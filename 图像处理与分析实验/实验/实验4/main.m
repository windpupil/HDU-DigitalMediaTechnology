clc
clear 
close all

%原始图片及其居中后的频谱：
J=imread('lena.bmp');
J_gray=rgb2gray(J);
figure;
imshow(J_gray);%显示原始灰度图像
title('原始灰度图像');
 
J2=fft2(J_gray);%二维离散傅立叶变换
J3=fftshift(J2);%居中
J4=log(abs(J3));
figure;
imshow(J4,[]);%显示居中后的频谱图
title('离散傅立叶变换居中频谱图');
%理想低通滤波器：
[m,n]=size(J_gray);
d0=50;
x0=round(m/2);
y0=round(n/2);%定义一个半径为256的圆形区域
%截止频率d0=50的理想低通滤波器
for i=1:m
    for j=1:n
        d=sqrt((i-x0)^2+(j-y0)^2);%到原点中心的距离 
        if(d<d0)
            h(i,j)=1;
        else
            h(i,j)=0;
        end
    end
end
figure;
imshow(h);%画出理想低通滤波器的频谱图
title('理想低通滤波器的频谱图');
J5=J3.*h;
J6=log(abs(J5));
figure;
imshow(J6,[]) ;%画出滤波后的频谱
title('原频谱理想低通滤波后的频谱');
J7=ifftshift(J5);
J8=ifft2(J7);
J9=uint8(real(J8)); %对滤波后的频谱做反变换后居中
figure;
imshow(J9);%画出经过理想低通滤波器滤波后的图像
title('经过理想低通滤波器滤波后的图像'); 
%巴特沃斯滤波器：
[m,n]=size(J_gray);
d0=50;n=1;
x0=round(256);      
y0=round(256);
for i=1:m
    for j=1:n
        d=sqrt((i-x0)^2+(j-y0)^2);  
        h(i,j)=1/(1+(d/d0)^(2*n));
    end
end
figure;
imshow(h);%画出巴特沃斯滤波器的频谱图
title('巴特沃斯滤波器的频谱图');
J10=J3.*h;
J11=log(abs(J10));
figure;
imshow(J11,[]); %画出滤波后的频谱
title('巴特沃斯滤波器滤波后的频谱'); 
J12=ifftshift(J10);
J13=ifft2(J12);
J14=uint8(real(J13)); %对巴特沃斯滤波后的图像进行反变换并居中
figure;
imshow(J14); %画出经过巴特沃斯滤波器滤波后的图像
title('经过巴特沃斯滤波器滤波后的图像');
 
