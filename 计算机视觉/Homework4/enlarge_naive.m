function out = enlarge_naive(image, size_W, axis)
%     """���� seam carving�㷨����ͼ��ĳߴ�.
% 
%     ÿ��ѭ�������Ƕ��Ḵ��ͼ����������͵�seam. �����ظ�������̣�֪��ͼ��ߴ�����Ҫ��.
%     �õ��ĺ���:
%         - backtrack_seam
%         - duplicate_seam
% 
%     Args:
%         image: ��״Ϊ (H, W, C) ������
%         size:  Ŀ��ĸ߻��߿� (�� axis ����)
%         axis: ���ӿ��(axis=1) ���߸߶� (axis=0)% 
%     Returns:
%         out: ���axis=0��������ߴ�Ϊ (size_W, W, C),��� axis=1��������ߴ�Ϊ (H, size_W, C)
%     """

    out = image;
    if axis == 0
        out = rot90(out);
    end

%   ��Ĵ���
    [H, W, ~] = size(out);
    while W < size_W
        energy = energy_function(out);
        % ���� cost �� path
        [cost, paths] = compute_cost([],energy, axis);

        % ����seam
        [seam_energy,index] = min(cost(end,:));
        seam = backtrack_seam(paths, index);

        out = duplicate_seam(out, seam);
        W = W + 1;
    end
%   ��Ĵ���

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out = uint8(out);
end