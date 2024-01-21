img = imread('����������.bmp');
img = rgb2gray(img);
fd_img = log(1+computeAmplitudeImage(img));

outimg = myapplyNotchFilter(img,1);
outfdimg = log(1+computeAmplitudeImage(outimg));
subplot(2,2,1),imshow(img,[]),title('ԭͼ');
subplot(2,2,2),imshow(fd_img,[]),title('����ͼ');
subplot(2,2,3),imshow(outimg,[]),title('�����˲���');
subplot(2,2,4),imshow(outfdimg,[]),title('�˲������ͼ');
function img_fft_shift = computeAmplitudeImage(img)
    img_fft=fft2(img);%��ά��ɢ����Ҷ�任
    img_fft_shift=fftshift(img_fft);%����
    img_fft_shift=abs(img_fft_shift);  
end

%�����˲���
function filteredImage = myapplyNotchFilter(grayImage, width)
    spectrum = fft2(double(grayImage));
    % ��ȡͼ���С
    [m, n] = size(grayImage);
    k = 6;
    q = width;
    % ���������˲���
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
    % Ӧ�ô����˲���
    filteredSpectrum = spectrum .* notchFilter;
    % �Դ�����Ƶ�׽����渵��Ҷ�任
    filteredImage = ifft2(filteredSpectrum);
    % ȡʵ������Ϊ�渵��Ҷ�任���ܲ����鲿
    filteredImage = real(filteredImage);
    filteredImage = uint8(filteredImage);
end



