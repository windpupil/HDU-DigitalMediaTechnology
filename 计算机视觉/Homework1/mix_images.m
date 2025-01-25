function result=mix_images(img1,img2,channel1, channel2)
%����������һ���µ�ͼƬ��ʹ��������벿����ͼƬ1���Ұ벿����ͼƬ2������ȥ��ָ����ͼ��ͨ����R,G,����B����
result = zeros(size(img1, 1), size(img1, 2) * 2, 3, 'uint8');

% ����ͨ������
channels = {'R', 'G', 'B'};
idx1 = strcmp(channels, channel1);
idx2 = strcmp(channels, channel2);

% �Ƴ�img1��ָ��ͨ��
img1_no_channel1 = img1;
img1_no_channel1(:, :, idx1) = 0;

% �Ƴ�img2��ָ��ͨ��
img2_no_channel2 = img2;
img2_no_channel2(:, :, idx2) = 0;

% ��������ͼ��ƴ�ӵ�һ��
half_width = size(img1, 2);
result(:, 1:half_width, :) = img1_no_channel1;
result(:, half_width+1:end, :) = img2_no_channel2;
end