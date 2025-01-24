function result=hsv_decomposition(img,channel)
%本函数将输入图片分解为H,S,V三个通道
%并返回指定通道的图像
%提示：matlab对于double类型的图像，需要其绝对值不大于1才能进行显示。因此你需要进行归一化处理。
%提示：可以在命令行窗口键入help rgb2hsv查看帮助
result=mat2gray(img);
hsv_img = rgb2hsv(result);
switch channel
    case 'H'
        result = hsv_img(:, :, 1);
    case 'S'
        result = hsv_img(:, :, 2);
    case 'V'
        result = hsv_img(:, :, 3);
end
end