%���ù�ʽ���ɸ�˹�ֲ�
function result = gaussian_kernel(sizeN ,sigma)

% ��Ĵ���
% ����һ��size x size�������
kernel = zeros(sizeN);
% �����˹�˲���
center = floor(sizeN / 2)+1 ;
for i = 1:sizeN
    for j = 1:sizeN
        % ����(i,j)λ����������ĵ�ƫ����
        x = i - center;
        y = j - center;
        % �����˹ֵ����һ��
        kernel(i, j) = (1 / (2 * pi * sigma^2)) * exp(-(x^2 + y^2) / (2 * sigma^2));
    end
end
result=kernel;
end