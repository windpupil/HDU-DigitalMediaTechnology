h = imread('pollen.tif');
% histeq使图像直方图均衡化，256为均衡化后的灰度级数
g = histeq(h, 256);
figure
subplot(2,2,1)
imshow(h);
title('原图')

subplot(2,2,2)
% imhist是获取图像直方图的函数
% plot创建 Y 中数据对 X 中对应值的二维线图
plot(imhist(h))
title('原图的灰度直方图');

subplot(2,2,3)
imshow(g)
title('均衡化后的图') 

subplot(2,2,4)
plot(imhist(g))
title('均衡化后的图的直方图')


h = imread('rose.tif');
g = histeq(h, 256);
figure
subplot(2,2,1)
imshow(h);
title('原图')

subplot(2,2,2)
plot(imhist(h))
title('原图的灰度直方图');

subplot(2,2,3)
imshow(g)
title('均衡化后的图') 

subplot(2,2,4)
plot(imhist(g))
title('均衡化后的图的直方图')
