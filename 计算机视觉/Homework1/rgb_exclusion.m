function result=rgb_exclusion(img,channel)
%本函数从彩色图像img除去指定的通道channel
%对于被去除的通道，直接将该通道值置为0即可
result=mat2gray(img);
switch channel
    case 'R'
        result(:, :, 1) = 0;
    case 'G'
        result(:, :, 2) = 0;
    case 'B'
        result(:, :, 3) = 0;
end