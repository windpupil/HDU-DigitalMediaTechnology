%函数``double_thresholding``完成了强、弱边缘的标记
%从弱边缘中找出与强边缘相连接的点，并保留
%需要注意的是，如果一个弱边缘1与强边缘相连，那么它也是edge
%同时，如果另一个弱边缘2与弱边缘1也相连，那么弱边缘2也被视为edge
%（其实，也就是说弱边缘一旦与强边缘相连，那它就等同于强边缘了）
%完成这一步的一个方法是，建立一个list储存强边缘，然后不断从中取出强边缘点
%检测它的周围，一旦有弱边缘与它相连，那么就把这个弱边缘加到这个list里面
%（这个弱边缘之前没有被加进去过，因此你还需要一个map存储这个像素点有没有加入过list）
%循环，直到list为空
function edges = link_edges(strong_edges, weak_edges)
    [H, W] = size(strong_edges);
    idx = find(strong_edges > 0);
    edges = strong_edges;

    %   你的代码

    %   你的代码

end

function neighbors=get_neighbors(x, y, H, W)
    %输入坐标 x, y，返回该点相邻的坐标点
    x = [x-1, x, x+1];
    y = [y-1, y, y+1];
    x(x <= 0 | x>H) = [];
    y(y <= 0 | y>W) = [];
    [xx, yy] = meshgrid(x, y);
    neighbors = [xx(:), yy(:)];
end