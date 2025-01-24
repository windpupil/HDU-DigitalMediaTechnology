%利用公式生成高斯分布
function result = gaussian_kernel(sizeN ,sigma)

% 你的代码
% 创建一个size x size的零矩阵
kernel = zeros(sizeN);
% 计算高斯滤波器
center = floor(sizeN / 2)+1 ;
for i = 1:sizeN
    for j = 1:sizeN
        % 计算(i,j)位置相对于中心的偏移量
        x = i - center;
        y = j - center;
        % 计算高斯值并归一化
        kernel(i, j) = (1 / (2 * pi * sigma^2)) * exp(-(x^2 + y^2) / (2 * sigma^2));
    end
end
result=kernel;
end