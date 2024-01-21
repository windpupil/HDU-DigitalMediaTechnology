clc
clear
close all
img=imread('Tracy.tif');
[m,n]=size(img);    %确定图像的宽和高
figure 
origin = img;
subplot(3,2,1)
imshow(img)
title("Origin")

for i=1:m
      for j=1:n
            img(i,j)=255-img(i,j);
      end
end
subplot(3,2,2)
imshow(img)
title("Negtive")

img=imread('Tracy.tif');
img=im2double(img);
subplot(3,2,3)
for i=1:m
      for j=1:n
            img(i,j)=45.98*log(255*img(i,j)+1);
      end
end
imshow(uint8(img))
title("Log")

img=imread('Tracy.tif');
img=im2double(img);
subplot(3,2,4)
for i=1:m
      for j=1:n
            img(i,j)=1.5*power(img(i,j),0.5);
      end
end
imshow(img)
title("nth root")

subplot(3,2,5)
for i=1:m
      for j=1:n
           img(i,j)=exp(255*img(i,j)/45.98)-1;
      end
end
% img=img.*256;
img2=uint8(img);
imshow(img2);
title("Inverse Log")

img=imread('Tracy.tif');
img=im2double(img);
subplot(3,2,6)
for i=1:m
      for j=1:n
            img(i,j)=1.5*power(img(i,j),2);
      end
end
imshow(img)
title("nth power")