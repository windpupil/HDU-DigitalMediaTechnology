I=imread('rose.tif');
K=im2uint8(mat2gray(log(1+double(I))));
U=imadjust(I,[0,1],[1,0]);
V=im2uint8(mat2gray(double(I).^0.5));
figure;
imshow(V);