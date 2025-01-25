% ���룺
% image��(H*W*3)ͼ��������ȡpatch�е�����ֵ����������������
% corners��(H*W)ͼ��Harris�ǵ��⺯��harris_corners( )�����Ľǵ�ͼ��
% patch_size��patch�Ĵ�С��patch_size*patch_size����
% 
% �����
% keypoints��(m*2)��������Ϊ�ǵ�����������i�д洢������(x,y)���ǵ�i���ǵ���ԭͼ�е�x�����y���ꡣ
% descriptors��m*(patch_size*patch_size)��������Ϊ�ǵ�����������i�д洢��(1*(patch_size*patch_size))���о��ǵ�i���ǵ�������ӡ�

function [keypoints,descriptors]=describe_keypoints(image,corners,patch_size)

%��RGBͼ��ת��Ϊ�Ҷ�ͼ
if length(size(image))==3
    image = rgb2gray(double(image)/255);
end

%�ó��ǵ�ͼcorners�нǵ���ԭͼ�е�����
[x,y]=find(corners==1);
keypoints=zeros(length(x),2);
keypoints(:,1)=x;
keypoints(:,2)=y;

%��ʼ��������������
ps=floor(patch_size*0.5);
descriptors=zeros(length(x),(ps*2)^2);

%����ÿ���ǵ����������
for i=1:length(keypoints)
    tempx=keypoints(i,1);%�ǵ�x����
    tempy=keypoints(i,2);%�ǵ�y����
    patch1=image(tempx-ps:tempx-1,tempy-ps:tempy-1);
    patch2=image(tempx+1:tempx+ps,tempy-ps:tempy-1);
    patch3=image(tempx-ps:tempx-1,tempy+1:tempy+ps);
    patch4=image(tempx+1:tempx+ps,tempy+1:tempy+ps);
    patch=[patch1,patch2;patch3,patch4];%ȡ�ǵ���Χ16*16��������Ϊpatch
    v=simple_descriptor(patch);%չ��patch������׼��̬�����ӹ����ȶ���
    descriptors(i,:)=v;
end