%本函数从path图中找出了我们所需要的seam
function seam = backtrack_seam(paths, index)
   
%     为了实现这个功能，我们需要从图像的最下面一行开始，沿着paths图所给定的方向找出整个seam:
%         - 左上方 (-1)
%         - 正上方 (0)
%         - 右上方 (1)
% 
%     参数:
%         paths: 形状为 (H, W) 的数组，每个元素都是 -1, 0 或者 1
%         end: seam的终点，即最下面一行中累积能量cost最小的像素点位置
% 
%     Returns:
%         seam: 形状为 (H,1)的数组，数组的第i个元素保存了第i行的索引值。即seam里面每个元素的位置都是(i, seam[i])。
%     """
    [H, W] = size(paths);
%   用-1来进行初始化，确保每个元素都被正确赋值（如果没被赋值，值仍为-1，而-1是一个无效的索引）
    seam = - ones(H,1);

%     # 最后一个元素
    seam(end) = index;

%   你的代码
for i = H-1:-1:1
    index = index + paths(i+1, index);
    seam(i) = index;
end
%   你的代码

%     确定seam里面只包含[0, W-1]
        if max(seam) > W || min(seam) < 1
            disp('序号没找对');
        end
    end