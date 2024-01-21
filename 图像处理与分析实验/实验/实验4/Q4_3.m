img = imread('竖条纹噪声.bmp');
img = rgb2gray(img);
fd_img = log(1+computeAmplitudeImage(img));

outimg = myapplyNotchFilter(img,1);
outfdimg = log(1+computeAmplitudeImage(outimg));
subplot(2,2,1),imshow(img,[]),title('原图');
subplot(2,2,2),imshow(fd_img,[]),title('幅度图');
subplot(2,2,3),imshow(outimg,[]),title('带阻滤波器');
subplot(2,2,4),imshow(outfdimg,[]),title('滤波后幅度图');
function img_fft_shift = computeAmplitudeImage(img)
    img_fft=fft2(img);%二维离散傅立叶变换
    img_fft_shift=fftshift(img_fft);%居中
    img_fft_shift=abs(img_fft_shift);  
end

%带阻滤波器
function filteredImage = myapplyNotchFilter(grayImage, width)
    spectrum = fft2(double(grayImage));
    % 获取图像大小
    [m, n] = size(grayImage);
    k = 6;
    q = width;
    % 创建带阻滤波器
    notchFilter = ones(m, n);
    for i = k:m-k
        for j =1:q
            notchFilter(j, i) = 0;
        end
    end
    for i = k:m-k
        for j =n-q:n
            notchFilter(j, i) = 0;
        end
    end
    % 应用带阻滤波器
    filteredSpectrum = spectrum .* notchFilter;
    % 对处理后的频谱进行逆傅里叶变换
    filteredImage = ifft2(filteredSpectrum);
    % 取实部，因为逆傅里叶变换可能产生虚部
    filteredImage = real(filteredImage);
    filteredImage = uint8(filteredImage);
end



