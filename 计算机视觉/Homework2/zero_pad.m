%�˺�������˶�ԭͼ���0���
%����: ����һ�Ž���һ�����ص��ͼ��[1]�����pad_height = 1, pad_width = 2��
%��ô�����ͼ�����һ��3*5��ͼ��
%          [0, 0, 0, 0, 0],
%          [0, 0, 1, 0, 0],
%          [0, 0, 0, 0, 0]
function result=zero_pad(img, pad_height, pad_width)
% ��Ĵ���
[a,b]=size(img);
img1=zeros(a+pad_height*2,b+pad_width*2);
img1(pad_height+1:pad_height+a,pad_width+1:pad_width+b)=img(1:a,1:b);
result=img1;
% ��Ĵ���
end
