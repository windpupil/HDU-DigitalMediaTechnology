%零均值相关
function result=zero_mean_cross_correlation(image, kernel)

% 你的代码
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
img=double(image);%卷积运算时候使用double类型


[m,n]=size(img);
result=zeros(m,n);

img1=zero_pad(img,a-1,b-1);
for i=1:m
    for j=1:n
        mat=img1(i+1:i+a,j+1:j+b).*kernel;
        result(i,j)=sum(mat(:));
    end
end

% 你的代码
end
