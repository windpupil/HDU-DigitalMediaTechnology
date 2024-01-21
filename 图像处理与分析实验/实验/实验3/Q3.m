% ��ȡͼ��
originalImage = imread('tongtai.bmp');
% ��ʾԭʼͼ��
figure;
subplot(1,2,1);
imshow(originalImage);
title('ԭʼͼ��');
originalImage = double(originalImage);
% �����任����ͼ��Ҷ�ֵӳ�䵽������
c = 1; % ���������Ե���
logTransformedImage = c * log(1 + originalImage);
% ʹ�ø���Ҷ�任��ͼ��ת����Ƶ��
fftImage = fft2(logTransformedImage);
% ���̬ͬ�˲���
% �����������Ҫ���� H��D0��cL��cH ��ֵ
H = homomorphicFilter(size(originalImage, 1), size(originalImage, 2), 1, 0.4, 1.2, 2);
% Ӧ��̬ͬ�˲���
filteredImage = fftImage .* H;
% �����ת���ؿռ���
enhancedImage = abs(ifft2(filteredImage));
% ���任����ͼ��ָ���ԭʼ�Ķ�̬��Χ
enhancedImage = exp(enhancedImage) - 1;

% ��ʾ��ǿ���ͼ��
subplot(1,2,2);
imshow(uint8(enhancedImage));
title('̬ͬ�������ͼ��');

% ̬ͬ�˲�����ƺ���
function H = homomorphicFilter(rows, cols, D0, cL, cH, n)
    % ����̬ͬ�˲���
    H = zeros(rows, cols);
    
    for u = 1:rows
        for v = 1:cols
            D = sqrt((u - rows/2)^2 + (v - cols/2)^2);
            H(u, v) = (cH - cL) * (1 - exp(-n*(D^2)/(2*D0^2))) + cL;
        end
    end
    
    % �ƶ���Ƶ�ʷ�����ͼ������
    H = fftshift(H);
end