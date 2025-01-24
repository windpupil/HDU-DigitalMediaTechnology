function out = duplicate_seam(image, seam)
%     """复制seam上的像素点, 使得这些像素点出现两次.
% 
%     该函数会被 enlarge_naive 以及 enlarge 调用。
% 
%     参数:
%         image: 形状为 (H, W, C) 的数组
%         seam: 形状为 (H,1)的数组，数组的第i个元素保存了第i行的索引值。即seam里面每个元素的位置都是(i, seam[i])。
% 
%     Returns:
%         out: 形状为 (H, W + 1, C) 的数组
%     """

    [H, W, C] = size(image);
    out = zeros(H, W + 1, C);
%   你的代码
    for i = 1:H
        s = seam(i);
        out(i, 1:s, :) = image(i, 1:s, :);
        out(i, s+1, :) = image(i, s, :);
        out(i, s+2:end, :) = image(i, s+1:end, :);
    end
%   你的代码

end