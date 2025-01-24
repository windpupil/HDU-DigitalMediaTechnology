function result=mix_quadrants(img1)
%本函数将输入图像进行2*2的划分，即左上角四分之一，右上角四分之一，左下角四分之一以及右下角四分之一。
%对于每一个四分之一图像，都进行不同的操作（利用之前完成的函数）：
%左上角四分之一：去除'R'通道
%右上角四分之一：变暗
%左下角四分之一：按该公式变亮：x_n = x_p^0.5
%右下角四分之一：去除'R'通道
%最终输出处理以后的图像
[height, width, ~] = size(img1);
result = zeros(height, width, 3, 'uint8');

quarter_height = floor(height / 2);
quarter_width = floor(width / 2);
img1_topLeft_noR = img1(1:quarter_height, 1:quarter_width, :);
img1_topLeft_noR(:, :, 1) = 0;
result(1:quarter_height, 1:quarter_width, :) = img1_topLeft_noR;

img1_topRight_dark = im2double(img1(1:quarter_height, quarter_width+1:end, :));
img1_topRight_dark = img1_topRight_dark * 0.5;
img1_topRight_dark = uint8(img1_topRight_dark * 255);
result(1:quarter_height, quarter_width+1:end, :) = img1_topRight_dark;

img1_bottomLeft_bright = im2double(img1(quarter_height+1:end, 1:quarter_width, :));
img1_bottomLeft_bright = sqrt(img1_bottomLeft_bright);
img1_bottomLeft_bright = uint8(img1_bottomLeft_bright * 255);
result(quarter_height+1:end, 1:quarter_width, :) = img1_bottomLeft_bright;

img1_bottomRight_noR = img1(quarter_height+1:end, quarter_width+1:end, :);
img1_bottomRight_noR(:, :, 1) = 0; 
result(quarter_height+1:end, quarter_width+1:end, :) = img1_bottomRight_noR;
end