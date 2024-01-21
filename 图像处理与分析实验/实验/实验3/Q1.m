clc
clear 
close all

% 实验1 傅立叶正反变换及频谱显示
% 报错   错误使用 rgb2gray>parse_inputs (line 80) MAP 必须为 m x 3 的数组。
% 原因是给的lena.jpg不是用rgb存储的，用画布打开，另存为为24位bmp位图即可
% img=rgb2gray(imread('lena.bmp'));
% img=rgb2gray(imread('Tracy.bmp'));
img=rgb2gray(imread('字母A.jpg'));
figure;
imshow(img,[]);
title('原始灰度图像');

% 正反变换验证
img_fft=fft2(img);%二维离散傅立叶变换
img_fft_reverse=ifft2(img_fft);
figure;
imshow(uint8(img_fft_reverse),[]);
title('反变换灰度图像');


% 频谱显示
img_fft_shift=fftshift(img_fft);%居中
img_fft_shift_mag=abs(img_fft_shift);
img_fft_phase=angle(img_fft_shift);
figure 
imshow(log(img_fft_shift_mag),[]);
title('幅度谱')
figure 
imshow(img_fft_phase,[]);
title('相位谱')