clc
clear 
close all

% 高斯噪声添加与滤除
img=imread('lena.bmp');
img=rgb2gray(img);
[m,n]=size(img);
img_noise= imnoise(img,'gaussian',0.02);

img_noise_fft=fft2(img_noise);%二维离散傅立叶变换
img_noise_fft_shift=fftshift(img_noise_fft);%居中
img_noise_fft_shift_mag=abs(fftshift(img_noise_fft));
img_noise_fft_shift_phase=angle(fftshift(img_noise_fft));

%理想低通滤波器：
d0=80;
x0=round(m/2);
y0=round(n/2);
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

img_noise_fft_shift_mag_filted=img_noise_fft_shift_mag.*h;
img_noise_fft_shift_filted=img_noise_fft_shift_mag_filted.*exp(1i*img_noise_fft_shift_phase);
img_noise_fft_filted=ifftshift(img_noise_fft_shift_filted);
img_processed=ifft2(img_noise_fft_filted);
subplot(1,2,1);
imshow(img_processed,[]);
title('理想低通滤波后图像');

%巴特沃斯低通滤波
s=fftshift(fft2(img_noise));
[N1,N2]=size(s);% 求二维傅里叶变换后图像大小
n=2;            % 将巴特沃斯低通滤波器的阶数n设置为2
d0=80;          % 将巴特沃斯低通滤波器的截止频率D0设置为30
n1=round(N1/2);
n2=round(N2/2);
for i=1:N1      
    for j=1:N2 
        distance=sqrt((i-n1)^2+(j-n2)^2);
        if distance==0 
            h=0; 
        else
            h=1/(1+(distance/d0)^(2*n));% 根据巴特沃斯低通滤波器公式为1/(1+[D(i,j)/D0]^2n)
        end
        s(i,j)=h*s(i,j);% 频域图像乘以滤波器的系数
    end
end
% real函数取元素的实部
s=real(ifft2(ifftshift(s)));
subplot(1,2,2);
imshow(s,[]);
title('巴特沃斯低通滤波后图像');


