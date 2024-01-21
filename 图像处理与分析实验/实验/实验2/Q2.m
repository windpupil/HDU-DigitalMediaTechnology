figure; 
input_image=imread('lena.jpg');
noisy_image=imnoise(input_image,'salt & pepper',0.2); %加入椒盐噪声
%均值滤波对高斯噪声效果比较好，对椒盐噪声效果比较差
output_image=filter2(fspecial('average',3),noisy_image); %进行3*3模板均值滤波
subplot(1,2,1)
imshow(uint8(output_image));
title('matlab均值滤波');
% 中值滤波对椒盐噪声处理效果比较好，对高斯噪声效果比较差
output_image=medfilt2(noisy_image,[3,3]);
subplot(1,2,2)
imshow(output_image)
title('matlab中值滤波');