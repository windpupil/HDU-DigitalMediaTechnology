%������ֱ������ݶ�
function result = partial_y(img)
%   ��Ĵ���
% ����y����Ĳ�־����
    h_y = [0.5; 0; -0.5];
    result = conv2(double(img), h_y, 'same');
%   ��Ĵ���
end