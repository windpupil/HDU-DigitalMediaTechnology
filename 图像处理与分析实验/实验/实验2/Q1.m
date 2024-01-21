input_image=imread('lena.jpg');    %����һ��ͼ��  
F=imnoise(input_image,'salt & pepper',0.1); %���뽷������
w=[1,2,1;2,4,2;1,2,1];
w=1/16*w;                %���ü�Ȩ����ģ��w
[m,n]=size(F);             %ȷ������F�Ĵ�С��ԭͼ����к���
g=zeros(size(F));           %ƽ�����ͼ��g
% Ϊ�˽�ʡ�洢�ռ䣬matlabΪͼ���ṩ���������������uint8(8λ�޷������������Դ˷�ʽ�洢��ͼ�����8λͼ��
% matlab����ͼ���������uint8����matlab����ֵһ�����double�ͣ�64λ�����㡣
% �����ʱ��ԭͼ��ĻҶ�ֵת����double��������Ҫ�ǿ��Ǽ�������еľ��ȵ����⣬double����������С����ģ�
% ��uint8��0��255�����������ֱ����uint8���㣬���ڼ�������в������������������ͼ����������ǱȽϴ����
F1=double(F);

for x=1:m
    for y=1:n
        if(x==1||y==1||x==m||y==n)
            g(x,y)=F(x,y);
        else
            g(x,y)=w(1,1)*F1(x-1,y-1)+w(1,2)*F1(x-1,y)+w(1,3)*F1(x-1,y+1)+w(2,1)*F1(x,y-1)+w(2,2)*F1(x,y)+w(2,3)*F1(x,y+1)+w(3,1)*F1(x+1,y-1)+w(3,2)*F1(x+1,y)+w(3,3)*F1(x+1,y+1);
        end
    end
end

figure;
imshow(input_image);
title('original image');

figure; 
imshow(uint8(F)); 
title('noisy image');

figure;
imshow(uint8(g));
title('neighborhood average image');


