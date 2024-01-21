%读取图像
I = imread('交叉条纹噪声图像.png');
I = rgb2gray(I);
%图像填充
[M,N] = size(I);
P = 2*M;
Q = 2*N;
fillimage = uint8(zeros(P,Q));
fillimage(1:M,1:N) = I;

%频域中心化
for x=1:P
    for y=1:Q
        h(x,y)=(-1)^(x+y);
    end
end
fillimagecenter = h.*double(fillimage);

%二维傅里叶变换
F = fft2(double(fillimagecenter));

%陷波滤波算法
H_NF = ones(P,Q);%为了方便后面的累乘，所以用ones,如果是累加就用zeros
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

%傅里叶逆变换
G_1 = H_NF .* F;
g_1 = real(ifft2(G_1));
g_1 = g_1(1:M,1:N);     

for x = 1:M
    for y = 1:N
        g_1(x,y) = g_1(x,y) * (-1)^(x+y);
    end
end

figure(1);
subplot(221);imshow(I);title('原图');%显示原图

f=fft2(I);          %傅里叶变换
f=fftshift(f);      %使图像对称
r=real(f);          %图像频域实部
i=imag(f);          %图像频域虚部
margin=log(abs(f)); %图像幅度谱，加log便于显示
subplot(222);imshow(margin,[]);title('原图幅度谱');
subplot(223);imshow((H_NF));title('陷波滤波器');
subplot(224);imshow(uint8(g_1));title('陷波滤波后的结果图');
