%本函数完成了输入图像每个像素点能量的计算
function out = energy_function(image)
%     对于每个像素，先计算它 x- 和 y- 方向的梯度，然后再把它们的绝对值相加。
%     记得先把彩色图像转成灰度图像哦。
%     输出：能量图像，即每个像素点都是
    if length(size(image))==3
        gray_image = double(rgb2gray(uint8(image)))/255;
    end

%   你的代码
   [gx, gy] = gradient(gray_image);
    energy = abs(gx) + abs(gy);
    out = energy;
%   你的代码

end