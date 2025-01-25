function result=lab_decomposition(img,channel)
%本函数将输入图片分解为L,A,B三个通道
%并返回指定通道的图像
%提示：matlab对于double类型的图像，需要其绝对值不大于1才能进行显示。因此你需要进行归一化处理。
%提示：对于L通道，除以100即可；对于a通道，一般除以120即可；对于b通道，一般除以90即可
%提示：可以在命令行窗口键入help rgb2lab查看帮助
result=mat2gray(img);
lab_img = rgb2lab(result);  
switch channel
    case 'L'
        result = lab_img(:, :, 1); % 亮度通道
    case 'A'
        result = lab_img(:, :, 2); % 色度A通道
    case 'B'
        result = lab_img(:, :, 3); % 色度B通道
end
end