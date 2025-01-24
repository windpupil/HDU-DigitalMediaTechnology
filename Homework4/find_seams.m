%�ú����ҳ����������ӵ�seam��Ŀ
function seams = find_seams(image, k)
%     """�ҳ�ͼ����������С��k��seam.
%
%     ���ǿ��԰����Ƴ��ķ�ʽ��ǰk��seam��¼������Ȼ�����ú���enlarge�����Ǹ���һ�顣
%     ����������һ�����⣬ÿ����ͼƬ���Ƴ�һ��seam�Ժ����ص����λ�ûᷢ���ı䣬����޷�ֱ�ӽ����Ƴ���
%
%     Ϊ�˽��������⣬�������Ƕ�������������seams�Լ�indices��seams�ĳߴ��ԭͼ�񱣳�һ�£����Լ�¼ÿ���Ƴ���seam��ԭʼͼƬ�е�λ�á�
%     ��indices�����ͼ��imageһ������seam���Ƴ��𽥱�С����������¼ÿ���Ƴ���seam�ڵ�ǰimage�е�λ�á�ͬʱ������Ҳ������׷��seam��ԭʼͼƬ�е�λ�á�
%
%     �õ��ĺ���:
%         - backtrack_seam
%         - remove_seam
%
%     ����:
%         image: ��״Ϊ (H, W, C) ������
%         k: ��ҪѰ�ҵ�seam����Ŀ
%         axis: ���ڿ��(axis=1) ���߸߶� (axis=0)��Ѱ��
%         efunc: ��������energy�ĺ���
%         cfunc: ��������cost�ĺ���(����backtrack �� forward�����汾)��ֱ������ cfunc(image, energy) ������cfunc����cost��Ĭ��Ϊcompute_cost
%
%     ����ֵ:
%         seams: �ߴ�Ϊ (H, W) ������
%     """

[H, W, C] = size(image);
if W<k
    disp('�Ƴ���seam��Ŀ���ܱ�������');
end

%����indices��������סԭʼ���ص������
%indices[row, col] ��ʾ���ǵ�ǰ���ص��colֵ��
%������Ϊ�����Ƴ�seam�Ĺ����У�row�ǲ���ı�ģ���һ�����Ǽ�¼�����ص��colֵ
%�Ϳ�������ȷ�������ص��Ӧ��ԭͼ���е�λ��
%Ҳ����˵�������ص��Ӧ��ԭʼͼƬ�е�(row, indices[row, col])
%ͨ�������Ӳ���������������ֵ��¼�������ص����ꡣ
%���磬����һ����״Ϊ(2, 4)��ͼ��������Ӧ�ĳ�ʼ��`indices` �������״�ǣ�
%    [[1, 2, 3, 4],
%     [1, 2, 3, 4]]
%��ÿһ�ж�������ͬ������ֵ
indices = repmat(1:W, H,1);

%������seams�����¼�±�ɾ����seam
%��seams�����У���i��seam�����¼��ֵΪi�����أ�seam����Ŵ�1��ʼ��
%���磬һ��(3, 4) ��ͼƬ��ǰ����seams����������±�ʾ��
%   [[0, 1, 0, 2],
%    [1, 0, 2, 0],
%    [1, 0, 0, 2]]
%���Կ�����ֵΪ1����ֵΪ2�����ص���Թ���һ��seam
%���Ƚ��г�ʼ��
seams = zeros(H,W);



%   ��Ĵ���
%-------------------------��ʾ---------------------------
%   ѭ���ҵ�k��seam
%   ��ȡ��ǰ��ѵ�seam��1)����energy 2)���� cost �� path 3)����seam
%   �Ƴ�����seam��Ȼ����ͼ���������i����������seam
%   %���Բ���sub2ind�����±��ת��������ȡ�������е�Ԫ��
%-------------------------��ʾ---------------------------
%ѭ���ҵ�k��seam
for i =1 : k
    %��ȡ��ǰ��ѵ�seam������Ժ���ǰ��д�ĺ����Ƚ�һ���Ƿ�һ��
    energy = energy_function(image);
    [cost, paths] = compute_cost([], energy, 1);
    [~,index] = min(cost(end,:));
    seam = backtrack_seam(paths, index);      % #����optimal seam
    
    %�Ƴ���ǰ������seam
    image = remove_seam(image, seam);
    
    %��ͼ���������i����������seam
    %��Ҫ��sub2indȡ�������е�Ԫ��
    idx = indices(sub2ind(size(indices),1:H,seam'));%�ҳ���ǰseam���к�
    seams(sub2ind(size(seams),1:H,idx)) = i;%��seams�����ڼ�¼��ǰseam
    
    %ͬʱ��������indices������������Ƴ�seam��ʹ��������״��image��״����һ��
    indices = remove_seam(indices, seam);
end
%   ��Ĵ���

end