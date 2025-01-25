function result=mix_images(img1,img2,channel1, channel2)
%本函数创建一幅新的图片，使得它的左半部分是图片1，右半部分是图片2，并且去掉指定的图像通道（R,G,或者B）。
result = zeros(size(img1, 1), size(img1, 2) * 2, 3, 'uint8');

% 定义通道索引
channels = {'R', 'G', 'B'};
idx1 = strcmp(channels, channel1);
idx2 = strcmp(channels, channel2);

% 移除img1的指定通道
img1_no_channel1 = img1;
img1_no_channel1(:, :, idx1) = 0;

% 移除img2的指定通道
img2_no_channel2 = img2;
img2_no_channel2(:, :, idx2) = 0;

% 将处理后的图像拼接到一起
half_width = size(img1, 2);
result(:, 1:half_width, :) = img1_no_channel1;
result(:, half_width+1:end, :) = img2_no_channel2;
end