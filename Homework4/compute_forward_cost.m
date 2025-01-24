function [cost, paths] = compute_forward_cost(~, energy,axis)

%     """计算 forward cost map (竖直) 以及对应的seams的paths.
% 
%     从第一行开始,计算每一个像素点的累积能量和，即cost。像素点的cost定义为从顶部开始，同一seam上像素点的累积能量和的最小值.
%     同时，请确保已经在原cost的基础上，增加了由于移除pixel所引入的新的能量。
%     
%     与之前一样，我们需要返回这条路径。路径上的每个像素点的值只有三种可能：-1,0,以及1，-1表示当前像素点与它的左上角的元素相连，0表示当前像素点
%     与它正上方的元素相连，而1表示当前像素点与它右上方的元素相连。
%   
%     参数:
%         image: 该函数里面没有使用
%                (留在这是为了和 compute_forward_cost 函数有一个相同的接口)
%         energy: 形状为 (H, W) 的数组
% 
%     返回值:
%         cost: 形状为 (H, W) 的数组
%         paths: 形状为 (H, W) 的数组，数组元素为 -1, 0 或者1
%     """
    if axis == 0
        energy = energy';
    end
    
    cost = zeros(size(energy));
    paths = cost;
    [H,W] = size(energy);
    % 初始化
    cost(1,:) = energy(1,:);
    for i=2:W-1
       cost(1,i)= abs(energy(1,i+1) - energy(1,i-1)); %第一行的cost除了它本身的能量，还有移除它所增加的能量
    end

    %提示：可以和之前compute_cost函数的编写一样，只采用一次循环
%   你的代码
    for i = 2:H
        % 构造矩阵M，用于计算每个像素点的 cost 和路径
        M = [inf, cost(i-1, 1:W-1); cost(i-1, :); cost(i-1, 2:W), inf];
        [min_cost, idx] = min(M, [], 1);
        cost(i,:) = energy(i,:) + min_cost;
        paths(i,:) = idx - 2;
    end
%   你的代码
    if axis == 0
        cost = cost';
        paths = paths';
    end
end