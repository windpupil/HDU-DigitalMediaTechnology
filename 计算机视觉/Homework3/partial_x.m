%����ˮƽ������ݶ�
function result = partial_x(img)
%   ��Ĵ���
% ����x����Ĳ�־����
    h_x = [0.5, 0, -0.5];
    % ʹ��conv2��������'same'���������С��������ͬ
    result = conv2(double(img), h_x, 'same');
%   ��Ĵ���
end