%计算竖直方向的梯度
function result = partial_y(img)
%   你的代码
% 定义y方向的差分卷积核
    h_y = [0.5; 0; -0.5];
    result = conv2(double(img), h_y, 'same');
%   你的代码
end