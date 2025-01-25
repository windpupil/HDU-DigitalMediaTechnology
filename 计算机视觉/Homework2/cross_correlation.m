%计算图像与模板的相关结果

function result=cross_correlation(image, kernel)

% 你的代码
img=double(image);%卷积运算时候使用double类型


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
% 你的代码

end
