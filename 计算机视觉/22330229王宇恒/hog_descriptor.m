% ���룺
% patch��(m*m)���󣬽ǵ���Χ��һ���̶�����
% 
% �����
% hog_descriptors��(1*d)������HOG�ݶ�ֱ��ͼ�����ӡ�

function hog_descriptors = hog_descriptor(patch)

%����x�����y�����sobel����
sobel_x=[1 0 -1;2 0 -2;1 0 -1];
sobel_y=[1 2 1;0 0 0;-1 -2 -1];

%����x�����y������ݶ�
Gx=conv2(patch,sobel_x,'same');
Gy=conv2(patch,sobel_y,'same');

%�����ݶȷ�ֵ���ݶȽǶ�
G=(Gx.^2+Gy.^2).^0.5;
theta=atan2d(Gy,Gx);
theta(theta<0)=theta(theta<0)+360;

%����ֱ��ͼbin�����������ｫ45��Ϊһ��bin����360�ȷ�Ϊ8��bin
n_bin=8;

%�����ݶȷ������
sort=sorter(theta,n_bin);

%��patch�ֿ飬��Ϊ(patch_size/4)��2*2��cell
[H,W]=size(patch);
patch_size=H*W;
cell_num=(patch_size/4)^0.5;
cell_size=ones(1,cell_num)*2;
B_sort=mat2cell(sort,cell_size,cell_size);
B=mat2cell(patch,cell_size,cell_size);
[H_B,W_B]=size(B);
B_G=mat2cell(G,cell_size,cell_size);
B_theta=mat2cell(theta,cell_size,cell_size);

temp_B_bin=zeros(4,n_bin);
count=1;

%����patch�ݶ�ֱ��ͼ
for m=1:H_B
    for n=1:W_B
        temp_B_G=B_G{m,n};
        temp_B_theta=B_theta{m,n};
        temp_B_sort=B_sort{m,n};
        [H_C,W_C]=size(temp_B_G);
        temp_C_bin=zeros(1,n_bin+1);
        
        %����cell�ݶ�ֱ��ͼ
        for i=1:H_C
            for j=1:W_C
                temp_theta=temp_B_theta(i,j);%�ݶȷ���
                temp_magnitude=temp_B_G(i,j);%�ݶȷ�ֵ
                temp_sort=temp_B_sort(i,j);%�ݶȽǶ����
                
                contri1_theta=temp_theta-(temp_sort-1)*(360/n_bin);%���ڵ�i��bin�Ĺ���
                contri2_theta=(360/n_bin)*2-contri1_theta;%���ڵ�i+1��bin�Ĺ���
                
                contri1_weiht=contri1_theta/(contri1_theta+contri2_theta);%��i��bin��õķ�ֵȨֵ
                contri2_weiht=contri2_theta/(contri1_theta+contri2_theta);%��i+1��bin��õķ�ֵȨֵ
                
                temp_C_bin(temp_sort)=temp_C_bin(temp_sort)+temp_magnitude*contri1_weiht;%��i��bin��õķ�ֵ
                temp_C_bin(temp_sort+1)=temp_C_bin(temp_sort+1)+temp_magnitude*contri2_weiht;%��i+1��bin��õķ�ֵ
            end
        end
      
        %���ڴ���315�ȵĽǶȣ���i+1��bin����ĵķ�ֵӦ�����0�ȵ�bin
        temp_C_bin(1)=temp_C_bin(1)+temp_C_bin(n_bin+1);
        temp_C_bin=temp_C_bin(1:n_bin);
        temp_B_bin(count,:)=temp_C_bin;
        count=count+1;
    end
end

hog_descriptors=temp_B_bin(:);

end

%�Ƕȷ������������ݶȷ���������������������bin
function out=sorter(theta,n_bin)
[H,W]=size(theta);
list_bin=linspace(0,360,n_bin+1);
out=zeros(H,W);
for i=1:H
    for j=1:W
        for k=1:n_bin
            if theta(i,j)<=list_bin(k+1)
                out(i,j)=k;
                break;
            end
        end
    end
end
end
