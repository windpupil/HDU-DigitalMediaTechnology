% ���룺
% patch��(patch_size*patch_size)����
% 
% �����
% out��(1*(patch_size*patch_size))������չ����ı�׼��̬��patch��

function out=simple_descriptor(patch)

patch_std=std2(patch);%��׼��
patch_mean=mean(patch(:));%��ֵ

out=(patch-patch_mean)./patch_std;%��׼��̬��
out=out(:);

end