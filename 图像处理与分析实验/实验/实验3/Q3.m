% 读取图像
originalImage = imread('tongtai.bmp');
% 显示原始图像
figure;
subplot(1,2,1);
imshow(originalImage);
title('原始图像');
originalImage = double(originalImage);
% 对数变换，将图像灰度值映射到对数域
c = 1; % 常数，可以调整
logTransformedImage = c * log(1 + originalImage);
% 使用傅里叶变换将图像转换到频域
fftImage = fft2(logTransformedImage);
% 设计同态滤波器
% 在这里，根据需要调整 H，D0，cL，cH 的值
H = homomorphicFilter(size(originalImage, 1), size(originalImage, 2), 1, 0.4, 1.2, 2);
% 应用同态滤波器
filteredImage = fftImage .* H;
% 将结果转换回空间域
enhancedImage = abs(ifft2(filteredImage));
% 反变换，将图像恢复到原始的动态范围
enhancedImage = exp(enhancedImage) - 1;

% 显示增强后的图像
subplot(1,2,2);
imshow(uint8(enhancedImage));
title('同态增晰后的图像');

% 同态滤波器设计函数
function H = homomorphicFilter(rows, cols, D0, cL, cH, n)
    % 构建同态滤波器
    H = zeros(rows, cols);
    
    for u = 1:rows
        for v = 1:cols
            D = sqrt((u - rows/2)^2 + (v - cols/2)^2);
            H(u, v) = (cH - cL) * (1 - exp(-n*(D^2)/(2*D0^2))) + cL;
        end
    end
    
    % 移动零频率分量到图像中心
    H = fftshift(H);
end