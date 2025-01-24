function out = reduce_forward(image, size_W, axis)
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
    
    
    %��Ĵ���

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out = uint8(out);
end