clc
clear 
close all

% ʵ��1 ����Ҷ�����任��Ƶ����ʾ
% ����   ����ʹ�� rgb2gray>parse_inputs (line 80) MAP ����Ϊ m x 3 �����顣
% ԭ���Ǹ���lena.jpg������rgb�洢�ģ��û����򿪣����ΪΪ24λbmpλͼ����
% img=rgb2gray(imread('lena.bmp'));
% img=rgb2gray(imread('Tracy.bmp'));
img=rgb2gray(imread('��ĸA.jpg'));
figure;
imshow(img,[]);
title('ԭʼ�Ҷ�ͼ��');

% �����任��֤
img_fft=fft2(img);%��ά��ɢ����Ҷ�任
img_fft_reverse=ifft2(img_fft);
figure;
imshow(uint8(img_fft_reverse),[]);
title('���任�Ҷ�ͼ��');


% Ƶ����ʾ
img_fft_shift=fftshift(img_fft);%����
img_fft_shift_mag=abs(img_fft_shift);
img_fft_phase=angle(img_fft_shift);
figure 
imshow(log(img_fft_shift_mag),[]);
title('������')
figure 
imshow(img_fft_phase,[]);
title('��λ��')