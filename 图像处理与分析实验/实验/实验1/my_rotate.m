% [img_out,a,b]=my_rotate(img,angle)
% ���ܣ���ʾ�Զ����Ӻ�������תͼ��
% ���������img_out ��ת��ͼ��
% a,b 2���Զ�����������ر��壬��Ϊ����ʾ���Զ��庯���п����Զ������
% ���������img ����ͼ��
% angle ��ת�Ƕ�

function [img_out,a,b] = my_rotate( img_input, angle)

a=1;
b=2;
img_out=imrotate(img_input, angle);




