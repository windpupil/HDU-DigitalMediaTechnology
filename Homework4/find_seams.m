%该函数找出了所需增加的seam数目
function seams = find_seams(image, k)
%     """找出图像中能量最小的k条seam.
%
%     我们可以按照移除的方式把前k条seam记录下来，然后利用函数enlarge把它们复制一遍。
%     但这样存在一个问题，每次在图片中移除一条seam以后，像素的相对位置会发生改变，因此无法直接进行移除。
%
%     为了解决这个问题，这里我们定义了两个矩阵，seams以及indices。seams的尺寸和原图像保持一致，用以记录每次移除的seam在原始图片中的位置。
%     而indices矩阵和图像image一起，随着seam的移除逐渐变小，它用来记录每次移除的seam在当前image中的位置。同时，我们也用它来追踪seam在原始图片中的位置。
%
%     用到的函数:
%         - backtrack_seam
%         - remove_seam
%
%     参数:
%         image: 形状为 (H, W, C) 的数组
%         k: 需要寻找的seam的数目
%         axis: 是在宽度(axis=1) 或者高度 (axis=0)上寻找
%         efunc: 用来计算energy的函数
%         cfunc: 用来计算cost的函数(包括backtrack 和 forward两个版本)，直接利用 cfunc(image, energy) 来调用cfunc计算cost。默认为compute_cost
%
%     返回值:
%         seams: 尺寸为 (H, W) 的数组
%     """

[H, W, C] = size(image);
if W<k
    disp('移除的seam数目不能比列数多');
end

%生成indices矩阵来记住原始像素点的索引
%indices[row, col] 表示的是当前像素点的col值。
%这是因为，在移除seam的过程中，row是不会改变的，而一旦我们记录下像素点的col值
%就可以马上确定该像素点对应于原图像中的位置
%也就是说，该像素点对应于原始图片中的(row, indices[row, col])
%通过这样子操作，我们用像素值记录下了像素的坐标。
%例如，对于一个形状为(2, 4)的图像，它所对应的初始的`indices` 矩阵的形状是：
%    [[1, 2, 3, 4],
%     [1, 2, 3, 4]]
%即每一列都具有相同的像素值
indices = repmat(1:W, H,1);

%我们用seams数组记录下被删除的seam
%在seams数组中，第i条seam将会记录成值为i的像素（seam的序号从1开始）
%例如，一幅(3, 4) 的图片的前两个seams数组可能如下表示：
%   [[0, 1, 0, 2],
%    [1, 0, 2, 0],
%    [1, 0, 0, 2]]
%可以看到，值为1或者值为2的像素点可以构成一条seam
%首先进行初始化
seams = zeros(H,W);



%   你的代码
%-------------------------提示---------------------------
%   循环找到k条seam
%   获取当前最佳的seam：1)计算energy 2)计算 cost 和 path 3)计算seam
%   移除这条seam，然后在图像中用序号i保存下这条seam
%   %可以采用sub2ind进行下标的转换，帮你取出矩阵中的元素
%-------------------------提示---------------------------
%循环找到k条seam
for i =1 : k
    %获取当前最佳的seam，你可以和你前面写的函数比较一下是否一样
    energy = energy_function(image);
    [cost, paths] = compute_cost([], energy, 1);
    [~,index] = min(cost(end,:));
    seam = backtrack_seam(paths, index);      % #计算optimal seam
    
    %移除当前的这条seam
    image = remove_seam(image, seam);
    
    %在图像中用序号i保存下这条seam
    %需要用sub2ind取出矩阵中的元素
    idx = indices(sub2ind(size(indices),1:H,seam'));%找出当前seam的列号
    seams(sub2ind(size(seams),1:H,idx)) = i;%在seams矩阵内记录当前seam
    
    %同时，我们在indices这个数组里面移除seam，使得它的形状与image形状保持一致
    indices = remove_seam(indices, seam);
end
%   你的代码

end