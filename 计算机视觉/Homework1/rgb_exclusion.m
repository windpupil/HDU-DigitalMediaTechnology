function result=rgb_exclusion(img,channel)
%�������Ӳ�ɫͼ��img��ȥָ����ͨ��channel
%���ڱ�ȥ����ͨ����ֱ�ӽ���ͨ��ֵ��Ϊ0����
result=mat2gray(img);
switch channel
    case 'R'
        result(:, :, 1) = 0;
    case 'G'
        result(:, :, 2) = 0;
    case 'B'
        result(:, :, 3) = 0;
end