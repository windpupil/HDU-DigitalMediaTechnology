function result=hsv_decomposition(img,channel)
%������������ͼƬ�ֽ�ΪH,S,V����ͨ��
%������ָ��ͨ����ͼ��
%��ʾ��matlab����double���͵�ͼ����Ҫ�����ֵ������1���ܽ�����ʾ���������Ҫ���й�һ������
%��ʾ�������������д��ڼ���help rgb2hsv�鿴����
result=mat2gray(img);
hsv_img = rgb2hsv(result);
switch channel
    case 'H'
        result = hsv_img(:, :, 1);
    case 'S'
        result = hsv_img(:, :, 2);
    case 'V'
        result = hsv_img(:, :, 3);
end
end