% ���룺
% descriptors1��m*d�����Ӿ���
% descriptors2��n*d�����Ӿ���
% k��������ֵ��
% 
% �����
% count��ƥ���ϵĽǵ������
% matched_points��(count*2)���󣬱���ƥ���ϵĽǵ�����ꡣ

function [matched_points,count]=match_descriptors(descriptors1,descriptors2,k)

%��ʼ��ŷ�Ͼ������
[count1,~]=size(descriptors1);
[count2,~]=size(descriptors2);
matched_points=zeros(count1,2);
dist=zeros(count1,count2);

%����ŷʽ�������
for i=1:count1
    for j=1:count2
        temp1=descriptors1(i,:);%ȡ�ǵ�1��������
        temp2=descriptors2(j,:);%ȡ�ǵ�2��������
        dist(i,j)=sqrt(sum((temp1-temp2).^2));%���������������ӵ�ŷ�Ͼ���
    end
end

%�жϽǵ��Ƿ�ƥ��
for i=1:count1
    [dist_min,ind]=sort(dist(i,:));%����img1�еĽǵ�i���ҳ�img2������ŷ�Ͼ�����С�������ǵ�j1��j2
    dist_min1=dist_min(1);%��(i,j1)��ŷ�Ͼ���Ϊdist_min1
    dist_min2=dist_min(2);%��(i,j2)��ŷ�Ͼ���Ϊdist_min2
    
    q=dist_min1/dist_min2;%����dist_min1/dist_min2
    
    if q<=k%������ֵk�ж�(i,j1)�Ƿ���һ�Ա�����ƥ��Ľǵ�
        matched_points(i,1)=i;
        matched_points(i,2)=ind(1);
    end
end

matched_points(all(matched_points==0,2),:)=[];
count=size(matched_points,1);

end