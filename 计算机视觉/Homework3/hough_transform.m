%本函数完成了ROI区域的霍夫变换
%对应的变换是：
% rho = x * cos(theta) + y * sin(theta)
% 将像素点(x,y)变换成对应的sine-like曲线
% 输入为图像image
% 输出为：
% accumulator: m*n的矩阵
% rhos: m*1的向量
% thetas: n*1的向量
function [accumulator, rhos, thetas] = hough_transform(img)

%   确定 rho 和 theta 的范围
    [W, H] = size(img);
    diag_len = ceil(sqrt(W.^2+H.^2));
    rhos = -diag_len:diag_len; %防止rho越界
    thetas = -90:90;
%   预算一些有用的值，方便后面在进行计算
    cos_t = cosd(thetas);
    sin_t = sind(thetas);
    num_thetas = length(thetas);
    
%   初始化计数器计数器
    accumulator = zeros(2*diag_len+1, num_thetas);
    [xs,ys] = find(img);%找出不为0的像素点，此时坐标是相对于左上角而言的
    temp = ys;
    ys = size(img,1) - xs;
    xs = temp;          %此时原点在左下角
    
%   对所有不为0的像素点进行转换
%   根据theta确定对应的rho值
%   并对计数器进行累加
%   你的代码

%   你的代码
end