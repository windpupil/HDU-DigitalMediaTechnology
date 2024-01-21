%��ȡͼ��
I = imread('������������ͼ��.png');
I = rgb2gray(I);
%ͼ�����
[M,N] = size(I);
P = 2*M;
Q = 2*N;
fillimage = uint8(zeros(P,Q));
fillimage(1:M,1:N) = I;

%Ƶ�����Ļ�
for x=1:P
    for y=1:Q
        h(x,y)=(-1)^(x+y);
    end
end
fillimagecenter = h.*double(fillimage);

%��ά����Ҷ�任
F = fft2(double(fillimagecenter));

%�ݲ��˲��㷨
H_NF = ones(P,Q);%Ϊ�˷��������۳ˣ�������ones,������ۼӾ���zeros
for u = 1:P
     for v = 1:Q
        D = 30;
        
        v_k = 59; u_k = 77;
        D_k1 = ((u-P/2-u_k)^2 + (v-Q/2-v_k)^2)^(0.5);
        D_k2 = ((u-P/2+u_k)^2 + (v-Q/2+v_k)^2)^(0.5);
        H_NF(u,v) = H_NF(u,v) * 1/(1+(D/D_k1)^4) * 1/(1+(D/D_k2)^4);
        
        v_k = 59; u_k = 159;
        D_k1 = ((u-P/2-u_k)^2 + (v-Q/2-v_k)^2)^(0.5);
        D_k2 = ((u-P/2+u_k)^2 + (v-Q/2+v_k)^2)^(0.5);
        H_NF(u,v) = H_NF(u,v) * 1/(1+(D/D_k1)^4) * 1/(1+(D/D_k2)^4);
        
        v_k = -54; u_k = 84;
        D_k1 = ((u-P/2-u_k)^2 + (v-Q/2-v_k)^2)^(0.5);
        D_k2 = ((u-P/2+u_k)^2 + (v-Q/2+v_k)^2)^(0.5);
        H_NF(u,v) = H_NF(u,v) * 1/(1+(D/D_k1)^4) * 1/(1+(D/D_k2)^4);
        
        v_k = -54; u_k = 167;
        D_k1 = ((u-P/2-u_k)^2 + (v-Q/2-v_k)^2)^(0.5);
        D_k2 = ((u-P/2+u_k)^2 + (v-Q/2+v_k)^2)^(0.5);
        H_NF(u,v) = H_NF(u,v) * 1/(1+(D/D_k1)^4) * 1/(1+(D/D_k2)^4);
     end
end

%����Ҷ��任
G_1 = H_NF .* F;
g_1 = real(ifft2(G_1));
g_1 = g_1(1:M,1:N);     

for x = 1:M
    for y = 1:N
        g_1(x,y) = g_1(x,y) * (-1)^(x+y);
    end
end

figure(1);
subplot(221);imshow(I);title('ԭͼ');%��ʾԭͼ

f=fft2(I);          %����Ҷ�任
f=fftshift(f);      %ʹͼ��Գ�
r=real(f);          %ͼ��Ƶ��ʵ��
i=imag(f);          %ͼ��Ƶ���鲿
margin=log(abs(f)); %ͼ������ף���log������ʾ
subplot(222);imshow(margin,[]);title('ԭͼ������');
subplot(223);imshow((H_NF));title('�ݲ��˲���');
subplot(224);imshow(uint8(g_1));title('�ݲ��˲���Ľ��ͼ');
