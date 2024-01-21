input_image=imread('orig.tif');    %读入一幅图像  
F=imnoise(input_image,'salt & pepper',0.1); %加入椒盐噪声
[m,n]=size(F);             %确定矩阵F的大小即原图像的行和列
g=zeros(size(F));           %平滑后的图像g
for x=1:m
    for y=1:n
        if(x==1||y==1||x==m||y==n)
            g(x,y)=F(x,y);
        else
            %median是取中位数，sort是排序函数
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