function result = dim_image(img)
%��ͼ���ÿ�����ص��ϵ�����ֵ������ʽ���б任
%x_n = 0.5*x_p^2
%��ʾ��matlab����double���͵�ͼ����Ҫ�����ֵ������1���ܽ�����ʾ���������Ҫ���й�һ������
result=mat2gray(img);
[rows, cols] = size(result); % ��ȡͼ�������������  
for i = 1:rows  
    for j = 1:cols  
        result(i,j)=0.5*result(i,j)*result(i,j);
    end  
end
end