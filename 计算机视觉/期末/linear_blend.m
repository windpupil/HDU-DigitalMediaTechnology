% ���룺
% img1��(H*W*3)��������任�����ͼ1��
% img2��(H*W*3)��������任�����ͼ2��
% 
% �����
% temp_mask��img1��img2���غ�����
% linear_blended_img��(H*W*3)�غ����������ͬ�ںϽ����
% equally_weighted_blended_img��(H*W*3)�غ����������ںϽ����


function [temp_mask,linear_blended_img,equally_weighted_blended_img]=linear_blend(img1,img2)

%��ʼ��
linear_blended_img1=double(img1);
linear_blended_img2=double(img2);
equally_weighted_blended_img1=double(img1);
equally_weighted_blended_img2=double(img2);

%ȷ���ں�����
temp_mask1 = (linear_blended_img2(:,:,1)>0 |linear_blended_img2(:,:,2)>0 | linear_blended_img2(:,:,3)>0);%�任ͼ����Ĥ
temp_mask2 = (linear_blended_img1(:,:,1)>0 | linear_blended_img1(:,:,2)>0 | linear_blended_img1(:,:,3)>0);%�Ǳ任ͼ����Ĥ
temp_mask = and(temp_mask1,temp_mask2);%�ص�����Ĥ

%ȷ���ں��������߽���ұ߽�
[row,col] = find(temp_mask==1);
left = min(col);right = max(col);%����ص������ҷ�Χ
% up=min(row);down=max(row);

%����������ͬ�ں�mask
equally_weighted_mask = ones(size(temp_mask));
equally_weighted_mask(:,left:right) = repmat(linspace(0.5,0.5,right-left+1),size(equally_weighted_mask,1),1);%����ƽ�̾���
%����ÿ��ͼ���غ���������ֵ
equally_weighted_blended_img1(:,:,:) = equally_weighted_blended_img1(:,:,:).*equally_weighted_mask;
equally_weighted_blended_img2(:,:,:) = equally_weighted_blended_img2(:,:,:).*equally_weighted_mask;

linear_blend_mask = ones(size(temp_mask));
%���������ں�mask1
linear_blend_mask(:,left:right) = repmat(linspace(1,0,right-left+1),size(linear_blend_mask,1),1);
% mask(up:down,:) = repmat(linspace(0,1,down-up+1)',1,size(mask,2));%����ƽ�̾���
%����ÿ��ͼ���غ���������ֵ
linear_blended_img1(:,:,:) = linear_blended_img1(:,:,:).*linear_blend_mask;
%���������ں�mask2
linear_blend_mask(:,left:right) = repmat(linspace(0,1,right-left+1),size(linear_blend_mask,1),1);%����ƽ�̾���
% mask(up:down,:) = repmat(linspace(1,0,down-up+1)',1,size(mask,2));%����ƽ�̾���
%����ÿ��ͼ���غ���������ֵ
linear_blended_img2(:,:,:) = linear_blended_img2(:,:,:).*linear_blend_mask;

%������
linear_blended_img(:,:,:) = linear_blended_img2(:,:,:) + linear_blended_img1(:,:,:);
linear_blended_img=uint8(linear_blended_img);

equally_weighted_blended_img(:,:,:)=equally_weighted_blended_img1(:,:,:) + equally_weighted_blended_img2(:,:,:);
equally_weighted_blended_img=uint8(equally_weighted_blended_img);
end