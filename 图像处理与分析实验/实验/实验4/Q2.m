clc
clear 
close all

% ��˹����������˳�
img=imread('lena.bmp');
img=rgb2gray(img);
[m,n]=size(img);
img_noise= imnoise(img,'gaussian',0.02);

img_noise_fft=fft2(img_noise);%��ά��ɢ����Ҷ�任
img_noise_fft_shift=fftshift(img_noise_fft);%����
img_noise_fft_shift_mag=abs(fftshift(img_noise_fft));
img_noise_fft_shift_phase=angle(fftshift(img_noise_fft));

%�����ͨ�˲�����
d0=80;
x0=round(m/2);
y0=round(n/2);
%��ֹƵ��d0=50�������ͨ�˲���
for i=1:m
    for j=1:n
        d=sqrt((i-x0)^2+(j-y0)^2);%��ԭ�����ĵľ��� 
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
title('�����ͨ�˲���ͼ��');

%������˹��ͨ�˲�
s=fftshift(fft2(img_noise));
[N1,N2]=size(s);% ���ά����Ҷ�任��ͼ���С
n=2;            % ��������˹��ͨ�˲����Ľ���n����Ϊ2
d0=80;          % ��������˹��ͨ�˲����Ľ�ֹƵ��D0����Ϊ30
n1=round(N1/2);
n2=round(N2/2);
for i=1:N1      
    for j=1:N2 
        distance=sqrt((i-n1)^2+(j-n2)^2);
        if distance==0 
            h=0; 
        else
            h=1/(1+(distance/d0)^(2*n));% ���ݰ�����˹��ͨ�˲�����ʽΪ1/(1+[D(i,j)/D0]^2n)
        end
        s(i,j)=h*s(i,j);% Ƶ��ͼ������˲�����ϵ��
    end
end
% real����ȡԪ�ص�ʵ��
s=real(ifft2(ifftshift(s)));
subplot(1,2,2);
imshow(s,[]);
title('������˹��ͨ�˲���ͼ��');


