function [cost, paths] = compute_forward_cost(~, energy,axis)

%     """���� forward cost map (��ֱ) �Լ���Ӧ��seams��paths.
% 
%     �ӵ�һ�п�ʼ,����ÿһ�����ص���ۻ������ͣ���cost�����ص��cost����Ϊ�Ӷ�����ʼ��ͬһseam�����ص���ۻ������͵���Сֵ.
%     ͬʱ����ȷ���Ѿ���ԭcost�Ļ����ϣ������������Ƴ�pixel��������µ�������
%     
%     ��֮ǰһ����������Ҫ��������·����·���ϵ�ÿ�����ص��ֵֻ�����ֿ��ܣ�-1,0,�Լ�1��-1��ʾ��ǰ���ص����������Ͻǵ�Ԫ��������0��ʾ��ǰ���ص�
%     �������Ϸ���Ԫ����������1��ʾ��ǰ���ص��������Ϸ���Ԫ��������
%   
%     ����:
%         image: �ú�������û��ʹ��
%                (��������Ϊ�˺� compute_forward_cost ������һ����ͬ�Ľӿ�)
%         energy: ��״Ϊ (H, W) ������
% 
%     ����ֵ:
%         cost: ��״Ϊ (H, W) ������
%         paths: ��״Ϊ (H, W) �����飬����Ԫ��Ϊ -1, 0 ����1
%     """
    if axis == 0
        energy = energy';
    end
    
    cost = zeros(size(energy));
    paths = cost;
    [H,W] = size(energy);
    % ��ʼ��
    cost(1,:) = energy(1,:);
    for i=2:W-1
       cost(1,i)= abs(energy(1,i+1) - energy(1,i-1)); %��һ�е�cost����������������������Ƴ��������ӵ�����
    end

    %��ʾ�����Ժ�֮ǰcompute_cost�����ı�дһ����ֻ����һ��ѭ��
%   ��Ĵ���
    for i = 2:H
        % �������M�����ڼ���ÿ�����ص�� cost ��·��
        M = [inf, cost(i-1, 1:W-1); cost(i-1, :); cost(i-1, 2:W), inf];
        [min_cost, idx] = min(M, [], 1);
        cost(i,:) = energy(i,:) + min_cost;
        paths(i,:) = idx - 2;
    end
%   ��Ĵ���
    if axis == 0
        cost = cost';
        paths = paths';
    end
end