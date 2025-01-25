function out = enlarge_naive(image, size_W, axis)
%     """利用 seam carving算法增加图像的尺寸.
% 
%     每次循环，我们都会复制图像中能量最低的seam. 不断重复这个过程，知道图像尺寸满足要求.
%     用到的函数:
%         - backtrack_seam
%         - duplicate_seam
% 
%     Args:
%         image: 形状为 (H, W, C) 的数组
%         size:  目标的高或者宽 (由 axis 决定)
%         axis: 增加宽度(axis=1) 或者高度 (axis=0)% 
%     Returns:
%         out: 如果axis=0，则输出尺寸为 (size_W, W, C),如果 axis=1，则输出尺寸为 (H, size_W, C)
%     """

    out = image;
    if axis == 0
        out = rot90(out);
    end

%   你的代码
    [H, W, ~] = size(out);
    while W < size_W
        energy = energy_function(out);
        % 计算 cost 和 path
        [cost, paths] = compute_cost([],energy, axis);

        % 计算seam
        [seam_energy,index] = min(cost(end,:));
        seam = backtrack_seam(paths, index);

        out = duplicate_seam(out, seam);
        W = W + 1;
    end
%   你的代码

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out = uint8(out);
end