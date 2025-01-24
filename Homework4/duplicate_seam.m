function out = duplicate_seam(image, seam)
%     """����seam�ϵ����ص�, ʹ����Щ���ص��������.
% 
%     �ú����ᱻ enlarge_naive �Լ� enlarge ���á�
% 
%     ����:
%         image: ��״Ϊ (H, W, C) ������
%         seam: ��״Ϊ (H,1)�����飬����ĵ�i��Ԫ�ر����˵�i�е�����ֵ����seam����ÿ��Ԫ�ص�λ�ö���(i, seam[i])��
% 
%     Returns:
%         out: ��״Ϊ (H, W + 1, C) ������
%     """

    [H, W, C] = size(image);
    out = zeros(H, W + 1, C);
%   ��Ĵ���
    for i = 1:H
        s = seam(i);
        out(i, 1:s, :) = image(i, 1:s, :);
        out(i, s+1, :) = image(i, s, :);
        out(i, s+2:end, :) = image(i, s+1:end, :);
    end
%   ��Ĵ���

end