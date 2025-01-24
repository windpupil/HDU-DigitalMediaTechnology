function out = reduce(image, size_W, axis)
%     """利用 seam carving算法减少图像的尺寸.
% 
%     每次循环我们都移除能量最小的seam. 不断循环这个操作，直到得到想要的图像尺寸.
%     利用到的函数:
%         - backtrack_seam
%         - remove_seam
% 
%     Args:
%         image: 形状为 (H, W, 3) 的数组
%         size:  目标的高或者宽 (由 axis 决定)
%         axis: 减少宽度(axis=1) 或者高度 (axis=0)
% 
%     Returns:
%         out: 如果axis=0，则输出尺寸为 (size, W, 3),如果 axis=1，则输出尺寸为 (H, size, 3)
%     """

    out = image;
    if axis == 0
        out = rot90(out);
    end

    %你的代码
    %步骤：
    %1)计算energy 2)计算 cost 和 path 3)计算seam 4)移除seam
    while size(out, 2) > size_W
        % 计算能量
        energy_map = energy_function(out);
        
        % 计算 cost 和 path
        [costs, paths] = compute_cost([],energy_map, 1);
        
        % 计算 seam
        [~,index] = min(costs(end,:));
        seam = backtrack_seam(paths, index);
        
        % 移除 seam
        out = remove_seam(out, seam);
    end
    %你的代码

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out = uint8(out);
end