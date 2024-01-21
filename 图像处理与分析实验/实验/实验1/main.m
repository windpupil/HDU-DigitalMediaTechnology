clc
clear
close all
img=imread('moon.tif');
figure
subplot(2,3,1);
imshow(img);
title('ԭͼ');

for angle=0:90:360   
    [img_out,a,b] = my_rotate( img, angle);
    imshow(img_out);
    pause(2);
end           