%����ͼ����ģ�����ؽ��

function result=cross_correlation(image, kernel)

% ��Ĵ���
img=double(image);%�������ʱ��ʹ��double����


[m,n]=size(img);
[a,b]=size(kernel);
result=zeros(m,n);

img1=zero_pad(img,a-1,b-1);
for i=1:m
    for j=1:n
        mat=img1(i+1:i+a,j+1:j+b).*kernel;
        result(i,j)=sum(mat(:));
    end
end
% ��Ĵ���

end
