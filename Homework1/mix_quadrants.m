function result=mix_quadrants(img1)
%������������ͼ�����2*2�Ļ��֣������Ͻ��ķ�֮һ�����Ͻ��ķ�֮һ�����½��ķ�֮һ�Լ����½��ķ�֮һ��
%����ÿһ���ķ�֮һͼ�񣬶����в�ͬ�Ĳ���������֮ǰ��ɵĺ�������
%���Ͻ��ķ�֮һ��ȥ��'R'ͨ��
%���Ͻ��ķ�֮һ���䰵
%���½��ķ�֮һ�����ù�ʽ������x_n = x_p^0.5
%���½��ķ�֮һ��ȥ��'R'ͨ��
%������������Ժ��ͼ��
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