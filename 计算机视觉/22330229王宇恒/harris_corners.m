% ���룺
% image����Ҫ���ǵ��(H*W*3)ͼ��
% window_size����ⴰ�ڵĴ�С��
% k���ǵ���Ӧ���̲�����
% border�����Ƕ�ͼ��߽��ϵĽǵ㲢������Ȥ�����Ա߽�Ľǵ㡣
% 
% �����
% corners�������Ľǵ�������H*W����0/1ֵͼ����Ϊ�ǽǵ㴦��ֵ��Ϊ1�����ǵ���Ϊ0��

function corners=harris_corners(image,window_size,k,border)

%��RGBͼ��ת��Ϊ�Ҷ�ͼ
if length(size(image))==3
    image = rgb2gray(double(image)/255);
end

%��ʼ���ǵ���������
[H,W]=size(image);
E=zeros(H,W);

%����x�����y�����sobel����
sobelx=[-1 0 1;-2 0 2;-1 0 1];
sobely=[-1 -2 -1;0 0 0;1 2 1];

%����ͼ��x�����y������ݶ�ֵ
Gx=conv2(image,sobelx,'same');
Gy=conv2(image,sobely,'same');

%����ǵ���Ӧ�����е�A��B��C���ݶȳ˻�����������Եõ��Ľ����һ�θ�˹ƽ�����ӿ���������
% window=ones(window_size,window_size);                    %ѡ��1: û��Ȩ��
window=fspecial('gaussian',[window_size,window_size],1);   %ѡ��2: Gaussianƽ��
A=conv2(Gx.*Gx,window,'same');
B=conv2(Gx.*Gy,window,'same');
C=conv2(Gy.*Gy,window,'same');

%���ݽǵ���Ӧ��������ÿ�����ص�Ľǵ���Ӧֵ
for i=1:H
    for j=1:W
        M=[A(i,j),B(i,j);B(i,j),C(i,j)];
        E(i,j)=det(M)-k*(trace(M)^2);
    end
end

%�ҳ�ͼ��������ӦֵEmax������ֵ��Ϊ0.01*Emax
Emax=max(E(:));
t=Emax*0.01;
E=padarray(E,[1 1],'both');

%ʹ����ֵ���˽ǵ�
for i=2:H+1
    for j=2:W+1
        if E(i,j)<t
            E(i,j)=0;
        end
    end
end

%�Ǽ���ֵ����
for i=2:H+1
    for j=2:W+1
        if E(i,j)~=0
            neighbors=get_neighbors(E,i,j);
            if E(i,j)<max(neighbors(:))
                E(i,j)=0;
            end
        end
    end
end

%�޳��߽��ϵ���Ч�ǵ�
corners=E(2:H+1,2:W+1);
corners(1:border,:)=0;
corners(:,1:border)=0;
corners(H-border+1:H,:)=0;
corners(:,W-border+1:W)=0;

corners(corners~=0)=1;
end

%��������x,y�����ظõ����ڵ�����㣬����(x,y)
function neighbors=get_neighbors(m,x,y)
neighbors =[m(x-1,y-1),m(x-1,y),m(x-1,y+1),m(x,y-1),m(x,y+1),m(x+1,y-1),m(x+1,y),m(x+1,y+1)];
end

