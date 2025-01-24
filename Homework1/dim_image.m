function result = dim_image(img)
%将图像的每个像素点上的像素值均按下式进行变换
%x_n = 0.5*x_p^2
%提示：matlab对于double类型的图像，需要其绝对值不大于1才能进行显示。因此你需要进行归一化处理。
result=mat2gray(img);
[rows, cols] = size(result); % 获取图像的行数和列数  
for i = 1:rows  
    for j = 1:cols  
        result(i,j)=0.5*result(i,j)*result(i,j);
    end  
end
end