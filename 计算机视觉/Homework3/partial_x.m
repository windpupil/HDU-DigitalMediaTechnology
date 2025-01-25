%计算水平方向的梯度
function result = partial_x(img)
%   你的代码
% 定义x方向的差分卷积核
    h_x = [0.5, 0, -0.5];
    % 使用conv2计算卷积，'same'保持输出大小与输入相同
    result = conv2(double(img), h_x, 'same');
%   你的代码
end