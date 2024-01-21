I = imread('bld.tif');
subplot(2,3,1);
imshow(I);
title('ԭͼ');

I1 = im2double(I);
[J, ] = edge(I1, 'roberts');
subplot(2,3,2);
imshow(J);
title('roberts��Ե���');

[J, ] = edge(I1, 'prewitt', 'both');  % ˮƽ�ʹ�ֱ����
subplot(2,3,3);
imshow(J);
title('prewit��Ե���');

[J, ] = edge(I1, 'sobel', [], 'horizontal');  % ˮƽ����
subplot(2,3,4);
imshow(J);
title('sobel��Ե���');

%matlab�ƺ�û��edge�Դ���������˹��Ϊ����
Ig2=double(I); 
w=fspecial('laplacian',0);  
g1=imfilter(I,w,'replicate');  
g=I-g1;  
subplot(2,3,5);  
imshow(g); 
title('matlab�Դ�����������˹��');

