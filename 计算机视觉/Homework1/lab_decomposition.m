function result=lab_decomposition(img,channel)
%������������ͼƬ�ֽ�ΪL,A,B����ͨ��
%������ָ��ͨ����ͼ��
%��ʾ��matlab����double���͵�ͼ����Ҫ�����ֵ������1���ܽ�����ʾ���������Ҫ���й�һ������
%��ʾ������Lͨ��������100���ɣ�����aͨ����һ�����120���ɣ�����bͨ����һ�����90����
%��ʾ�������������д��ڼ���help rgb2lab�鿴����
result=mat2gray(img);
lab_img = rgb2lab(result);  
switch channel
    case 'L'
        result = lab_img(:, :, 1); % ����ͨ��
    case 'A'
        result = lab_img(:, :, 2); % ɫ��Aͨ��
    case 'B'
        result = lab_img(:, :, 3); % ɫ��Bͨ��
end
end