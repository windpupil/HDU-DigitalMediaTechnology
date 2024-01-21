clc
clear
close all
img=imread('lena.tif');
figure
imshow(img)
imwrite(img,'lena backup.jpg');
