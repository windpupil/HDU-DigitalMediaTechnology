% ���룺
% keypoints1��(m*2)img1�ǵ�������������
% keypoints2��(n*2)img2�ǵ�������������
% matched_points��(p*2)���󣬱���ƥ���ϵĽǵ�����ꡣ
% iterations��RANSAC����������
% thres��RANSAC��ֵ��
% 
% �����
% ransac_matched_points��(q*2)���󣬱���RANSAC�����޳���ƥ����ƥ������ꡣ
% count_inliers��RANSAC�����޳���ƥ����ƥ��������

function [ransac_matched_points,count_inliers]=ransac(keypoints1,keypoints2,matched_points,iterations,thres,num_inliers)

N=length(matched_points);%�����ƥ��������ʼ��RANSAC���ƥ����������
ransac_matched_points=zeros(N,2);

matched1=matched_points(:,1);%ͼ��1�е�ƥ�������
matched2=matched_points(:,2);%ͼ��2�е�ƥ�������

sub_matched1=zeros(N,2);
sub_matched2=zeros(N,2);
sub_transed=zeros(N,2);

for i=1:N
    sub_matched2(i,:)=keypoints1(matched1(i),:);%ͼ��1�е�ƥ�������
    sub_matched1(i,:)=keypoints2(matched2(i),:);%ͼ��2�е�ƥ�������
end

count_inliers = 0;%��ʼ�����ڵ����
H=[0 0 0;0 0 0;0 0 1];%��ʼ���任����
x1=[];y1=[];x2=[];y2=[];A=[];B=[];

for i=1:iterations%ransac��������
    x1=[];y1=[];x2=[];y2=[];A=[];B=[];
    temp_n=0;temp_newmatches=zeros(N,2);
    
    randIndex=randperm(N);
    sub_p1=sub_matched1(randIndex,:);
    sub_p2=sub_matched2(randIndex,:);%��������
    
    %ȡǰnum_inliers����������Ϸ���任����H
    for t1=1:num_inliers
        tempx1=sub_p1(t1,1);x1=[x1,tempx1];
        tempy1=sub_p1(t1,2);y1=[y1,tempy1];
        tempx2=sub_p2(t1,1);x2=[x2,tempx2];
        tempy2=sub_p2(t1,2);y2=[y2,tempy2];
    end
    
    for t2=1:num_inliers
        tempA=[x1(t2) y1(t2) 1 0 0 0;0 0 0 x1(t2) y1(t2) 1];
        A=[A;tempA];
        tempb=[x2(t2);y2(t2)];
        B=[B;tempb];
    end
    
    T=((A'*A)^-1)*A'*B;
    H(1,1:3)=T(1:3);
    H(2,1:3)=T(4:6);
    
    %������ϳ����ı任�������任���
    for t3=1:N
        x=sub_matched1(t3,1);
        y=sub_matched1(t3,2);
        transed_point=H*[x;y;1];
        sub_transed(t3,1)=transed_point(1,1);
        sub_transed(t3,2)=transed_point(2,1);
    end
    
    % �������
    inaccuracy=abs(sub_transed./sub_matched2-1);
    %     inaccuracy=abs(norm(sub_transed)-norm(sub_matched2));
    
    for t4=1:N
        if sum(inaccuracy(t4,:))<thres
            %         if inaccuracy<thres
            temp_n=temp_n+1;
            temp_newmatches(t4,:)=matched_points(t4,:);
        end
    end
    
    if temp_n > count_inliers
        count_inliers = temp_n;
        ransac_matched_points=temp_newmatches;
    end
end

ransac_matched_points(all(ransac_matched_points==0,2),:)=[];

end