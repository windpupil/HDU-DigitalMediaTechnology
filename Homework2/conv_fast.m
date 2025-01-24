%计算图像与模板的卷积结果
%该函数采用了两重循环的卷积版本
%所以速度较慢
function result=conv_fast(image, kernel)
img=double(image);%卷积运算时候使用double类型

% 你的代码
[m,n]=size(img);
[a,b]=size(kernel);
result=zeros(m,n);
kernel=rot90(kernel,2);
img1=zero_pad(img,a-1,b-1);
for i=1:m
    for j=1:n
        mat=img1(i+1:i+a,j+1:j+b).*kernel;
        result(i,j)=sum(mat(:));
    end
end
% 你的代码

end
