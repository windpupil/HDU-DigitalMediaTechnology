h = imread('pollen.tif');
% histeqʹͼ��ֱ��ͼ���⻯��256Ϊ���⻯��ĻҶȼ���
g = histeq(h, 256);
figure
subplot(2,2,1)
imshow(h);
title('ԭͼ')

subplot(2,2,2)
% imhist�ǻ�ȡͼ��ֱ��ͼ�ĺ���
% plot���� Y �����ݶ� X �ж�Ӧֵ�Ķ�ά��ͼ
plot(imhist(h))
title('ԭͼ�ĻҶ�ֱ��ͼ');

subplot(2,2,3)
imshow(g)
title('���⻯���ͼ') 

subplot(2,2,4)
plot(imhist(g))
title('���⻯���ͼ��ֱ��ͼ')


h = imread('rose.tif');
g = histeq(h, 256);
figure
subplot(2,2,1)
imshow(h);
title('ԭͼ')

subplot(2,2,2)
plot(imhist(h))
title('ԭͼ�ĻҶ�ֱ��ͼ');

subplot(2,2,3)
imshow(g)
title('���⻯���ͼ') 

subplot(2,2,4)
plot(imhist(g))
title('���⻯���ͼ��ֱ��ͼ')
