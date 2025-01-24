function result=convert_to_grey_scale(img)
%本函数将彩色图像img转化成灰度图像result，转化公式如下：
%Gray = 0.299R + 0.587G + 0.114B
%提示：matlab对于double类型的图像，需要其绝对值不大于1才能进行显示。因此你需要进行归一化处理。
result=mat2gray(img);
R = img(:, :, 1);  
G = img(:, :, 2);  
B = img(:, :, 3);  
result = 0.299 * R + 0.587 * G + 0.114 * B;  
end