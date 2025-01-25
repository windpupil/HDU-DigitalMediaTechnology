%计算图像与模板的卷积结果
%该函数采用了四重循环的卷积版本
%所以速度较慢
function result=conv_nested(image, kernel)
img=double(image);%卷积运算时候使用double类型
% 你的代码
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
% 你的代码
end