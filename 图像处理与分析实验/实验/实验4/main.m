clc
clear 
close all

%ԭʼͼƬ������к��Ƶ�ף�
J=imread('lena.bmp');
J_gray=rgb2gray(J);
figure;
imshow(J_gray);%��ʾԭʼ�Ҷ�ͼ��
title('ԭʼ�Ҷ�ͼ��');
 
J2=fft2(J_gray);%��ά��ɢ����Ҷ�任
J3=fftshift(J2);%����
J4=log(abs(J3));
figure;
imshow(J4,[]);%��ʾ���к��Ƶ��ͼ
title('��ɢ����Ҷ�任����Ƶ��ͼ');
%�����ͨ�˲�����
[m,n]=size(J_gray);
d0=50;
x0=round(m/2);
y0=round(n/2);%����һ���뾶Ϊ256��Բ������
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
figure;
imshow(h);%���������ͨ�˲�����Ƶ��ͼ
title('�����ͨ�˲�����Ƶ��ͼ');
J5=J3.*h;
J6=log(abs(J5));
figure;
imshow(J6,[]) ;%�����˲����Ƶ��
title('ԭƵ�������ͨ�˲����Ƶ��');
J7=ifftshift(J5);
J8=ifft2(J7);
J9=uint8(real(J8)); %���˲����Ƶ�������任�����
figure;
imshow(J9);%�������������ͨ�˲����˲����ͼ��
title('���������ͨ�˲����˲����ͼ��'); 
%������˹�˲�����
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
imshow(h);%����������˹�˲�����Ƶ��ͼ
title('������˹�˲�����Ƶ��ͼ');
J10=J3.*h;
J11=log(abs(J10));
figure;
imshow(J11,[]); %�����˲����Ƶ��
title('������˹�˲����˲����Ƶ��'); 
J12=ifftshift(J10);
J13=ifft2(J12);
J14=uint8(real(J13)); %�԰�����˹�˲����ͼ����з��任������
figure;
imshow(J14); %��������������˹�˲����˲����ͼ��
title('����������˹�˲����˲����ͼ��');
 
