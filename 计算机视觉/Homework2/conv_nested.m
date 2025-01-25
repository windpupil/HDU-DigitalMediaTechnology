%����ͼ����ģ��ľ�����
%�ú�������������ѭ���ľ���汾
%�����ٶȽ���
function result=conv_nested(image, kernel)
img=double(image);%�������ʱ��ʹ��double����
% ��Ĵ���
[m,n]=size(img);
[a,b]=size(kernel);
kernel=rot90(kernel,2);
result=zeros(m,n);
img1=zero_pad(img,a-1,b-1);
for i=1:m
    for j=1:n
        for k=1:a
            for l=1:b
                result(i,j)=result(i,j)+img1(i+k,j+l)*kernel(k,l);
            end
        end
    end
end
% ��Ĵ���
end