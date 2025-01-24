%�ú���ʵ���˴�ͼ�����Ƴ�һ��seam
function out = remove_seam(image, seam)
    
    if length(size(image))==2
        image = reshape(image,[size(image),1]);
    end
    [H,W,C]=size(image);
    out = zeros(H,W-1,C);
    %��Ĵ���
    for i = 1:H
        % �ҵ�seam������ֵ
        seam_idx = seam(i);

        % �Ƴ�seam֮ǰ������
        out(i, 1:seam_idx-1, :) = image(i, 1:seam_idx-1, :);

        % �Ƴ�seam֮�������
        out(i, seam_idx:W-1, :) = image(i, seam_idx+1:W, :);
    end
    %��Ĵ���

end