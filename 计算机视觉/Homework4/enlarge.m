function out = enlarge(image, W_new, axis)
%     """ͨ�����Ƶ�������seams�����ǿ��ԷŴ�ͼƬ.
% 
%     ���ȣ�����ͨ������find_seams����ȡk����������seams.
%     �������ѭ��k����������Щseams.
% 
%     �����˺���:
%         - find_seams
%         - duplicate_seam
% 
%     ����:
%         image: ��״Ϊ (H, W, C) ������
%         size: Ŀ��ĳߴ磨��Ȼ��߸߶ȣ�
%         axis: ���ڿ��(axis=1) ���߸߶� (axis=0)��Ѱ��
% 
% 
%     Returns:
%         out: ���axis=0�������Ϊ�ߴ�Ϊ (size, W, C) �����顣���axis=1�������Ϊ (H, size, C) ������
%     """

    out=image;
%   �ж��Ƿ���Ҫת��
    if axis == 0
        out = rot90(out);
    end

    [H, W, C] = size(out);

%   ��Ĵ���
ota = out
seams = find_seams(ota,W_new - W);

out = zeros(H,W_new,C);

for i = 1:H
    jup = 0;
    for j = 1 : W
        if(seams(i,j) ~= 0)
            for o = 1 : C
                out(i,j + jup,o) = ota(i,j,o);
            end
            jup = jup + 1;
        end
        for l = 1 : C
            out(i,j + jup,l) = ota(i,j,l);
        end
    end
    dd = 1;
end

%   ��Ĵ���

    if axis == 0
        out = rot90(out);
        out = rot90(out);
        out = rot90(out);
    end
    out=uint8(out);
end