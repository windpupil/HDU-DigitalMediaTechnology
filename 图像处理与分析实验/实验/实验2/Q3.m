I = imread('bld.tif');
subplot(2,3,1);
imshow(I);
title('原图');

I1 = im2double(I);
[J, ] = edge(I1, 'roberts');
subplot(2,3,2);
imshow(J);
title('roberts边缘检测');

[J, ] = edge(I1, 'prewitt', 'both');  % 水平和垂直方向
subplot(2,3,3);
imshow(J);
title('prewit边缘检测');

[J, ] = edge(I1, 'sobel', [], 'horizontal');  % 水平方向
subplot(2,3,4);
imshow(J);
title('sobel边缘检测');

%matlab似乎没有edge自带的拉普拉斯作为参数
Ig2=double(I); 
w=fspecial('laplacian',0);  
g1=imfilter(I,w,'replicate');  
g=I-g1;  
subplot(2,3,5);  
imshow(g); 
title('matlab自带函数拉普拉斯锐化');

