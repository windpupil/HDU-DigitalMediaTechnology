figure; 
input_image=imread('lena.jpg');
noisy_image=imnoise(input_image,'salt & pepper',0.2); %���뽷������
%��ֵ�˲��Ը�˹����Ч���ȽϺã��Խ�������Ч���Ƚϲ�
output_image=filter2(fspecial('average',3),noisy_image); %����3*3ģ���ֵ�˲�
subplot(1,2,1)
imshow(uint8(output_image));
title('matlab��ֵ�˲�');
% ��ֵ�˲��Խ�����������Ч���ȽϺã��Ը�˹����Ч���Ƚϲ�
output_image=medfilt2(noisy_image,[3,3]);
subplot(1,2,2)
imshow(output_image)
title('matlab��ֵ�˲�');