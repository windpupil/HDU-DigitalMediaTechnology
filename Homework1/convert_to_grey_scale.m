function result=convert_to_grey_scale(img)
%����������ɫͼ��imgת���ɻҶ�ͼ��result��ת����ʽ���£�
%Gray = 0.299R + 0.587G + 0.114B
%��ʾ��matlab����double���͵�ͼ����Ҫ�����ֵ������1���ܽ�����ʾ���������Ҫ���й�һ������
result=mat2gray(img);
R = img(:, :, 1);  
G = img(:, :, 2);  
B = img(:, :, 3);  
result = 0.299 * R + 0.587 * G + 0.114 * B;  
end