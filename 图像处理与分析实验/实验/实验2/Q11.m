input_image=imread('orig.tif');    %����һ��ͼ��  
F=imnoise(input_image,'salt & pepper',0.1); %���뽷������
[m,n]=size(F);             %ȷ������F�Ĵ�С��ԭͼ����к���
g=zeros(size(F));           %ƽ�����ͼ��g
for x=1:m
    for y=1:n
        if(x==1||y==1||x==m||y==n)
            g(x,y)=F(x,y);
        else
            %median��ȡ��λ����sort��������
            g(x,y)=median(sort([F(x-1,y-1),F(x-1,y),F(x-1,y+1),F(x,y-1),F(x,y),F(x,y+1),F(x+1,y-1),F(x+1,y),F(x+1,y+1)]));
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
title('median filtered image');