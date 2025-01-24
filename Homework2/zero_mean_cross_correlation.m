%���ֵ���
function result=zero_mean_cross_correlation(image, kernel)

% ��Ĵ���
[a,b]=size(kernel);
all=sum(sum(kernel));
ave=all/(a*b);
mat=zeros(a,b);
for i=1:a
    for j=1:b
        mat(i,j)=mat(i,j)+ave;
    end
end
kernel=kernel-mat;
img=double(image);%�������ʱ��ʹ��double����


[m,n]=size(img);
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
