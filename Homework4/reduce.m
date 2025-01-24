function out = reduce(image, size_W, axis)
%     """���� seam carving�㷨����ͼ��ĳߴ�.
% 
%     ÿ��ѭ�����Ƕ��Ƴ�������С��seam. ����ѭ�����������ֱ���õ���Ҫ��ͼ��ߴ�.
%     ���õ��ĺ���:
%         - backtrack_seam
%         - remove_seam
% 
%     Args:
%         image: ��״Ϊ (H, W, 3) ������
%         size:  Ŀ��ĸ߻��߿� (�� axis ����)
%         axis: ���ٿ��(axis=1) ���߸߶� (axis=0)
% 
%     Returns:
%         out: ���axis=0��������ߴ�Ϊ (size, W, 3),��� axis=1��������ߴ�Ϊ (H, size, 3)
%     """

    out = image;
    if axis == 0
        out = rot90(out);
    end

    %��Ĵ���
    %���裺
    %1)����energy 2)���� cost �� path 3)����seam 4)�Ƴ�seam
    while size(out, 2) > size_W
        % ��������
        energy_map = energy_function(out);
        
        % ���� cost �� path
        [costs, paths] = compute_cost([],energy_map, 1);
        
        % ���� seam
        [~,index] = min(costs(end,:));
        seam = backtrack_seam(paths, index);
        
        % �Ƴ� seam
        out = remove_seam(out, seam);
    end
    %��Ĵ���

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out = uint8(out);
end