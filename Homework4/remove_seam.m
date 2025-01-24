%该函数实现了从图像中移除一条seam
function out = remove_seam(image, seam)
    
    if length(size(image))==2
        image = reshape(image,[size(image),1]);
    end
    [H,W,C]=size(image);
    out = zeros(H,W-1,C);
    %你的代码
    for i = 1:H
        % 找到seam的索引值
        seam_idx = seam(i);

        % 移除seam之前的像素
        out(i, 1:seam_idx-1, :) = image(i, 1:seam_idx-1, :);

        % 移除seam之后的像素
        out(i, seam_idx:W-1, :) = image(i, seam_idx+1:W, :);
    end
    %你的代码

end