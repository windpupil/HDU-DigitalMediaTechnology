%函数`non_maximum_suppression`完成了非极大值抑制
function result = non_maximum_suppression(G ,theta)
    % 将角度round到最近的45°上去
    theta = floor((theta + 22.5) / 45) * 45;
    result = zeros(size(G));
    
    %提示：计算theta的时候，我们默认往右为x轴正方向，往下为y轴正方向。
    %所以，对于45°等角度的处理得注意。
    %   你的代码
for i = 2: length(G(:, 1)) - 1
    for j = 2: length(G(1, :)) - 1
        dirc = alpha(i, j);         % 四个基本方向判断并进行非最大抑制，比如矩阵是
                                    % [1 2 3;4 5 6;7 8 9]，边缘延[4 5 6]方向，那
                                    % 么我们关心的是元素2和元素8与元素5的大小关系
        if abs(dirc) <= pi / 8
            if G(i, j) == max([(G(i, j - 1)), G(i, j), G(i, j + 1)])%竖直梯度，水平边缘
                result(i, j) = G(i, j);
            end
        elseif abs(dirc) >= 3 * pi / 8
            if G(i, j) == max([(G(i - 1, j)), G(i, j), G(i + 1, j)])%水平梯度，竖直边缘
                result(i, j) = G(i, j);
            end
        elseif dirc > pi / 8 && dirc < 3 * pi / 8
            if G(i, j) == max([(G(i - 1, j - 1)), G(i, j), G(i + 1, j + 1)])
                result(i, j) = G(i, j);
            end
        elseif dirc > - 3 * pi / 8 && dirc < - pi / 8
            if G(i, j) == max([(G(i + 1, j - 1)), G(i, j), G(i - 1, j + 1)])
                result(i, j) = G(i, j);
            end
        end
    end
end
    %   你的代码
end