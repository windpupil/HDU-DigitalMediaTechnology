%�����������ROI����Ļ���任
%��Ӧ�ı任�ǣ�
% rho = x * cos(theta) + y * sin(theta)
% �����ص�(x,y)�任�ɶ�Ӧ��sine-like����
% ����Ϊͼ��image
% ���Ϊ��
% accumulator: m*n�ľ���
% rhos: m*1������
% thetas: n*1������
function [accumulator, rhos, thetas] = hough_transform(img)

%   ȷ�� rho �� theta �ķ�Χ
    [W, H] = size(img);
    diag_len = ceil(sqrt(W.^2+H.^2));
    rhos = -diag_len:diag_len; %��ֹrhoԽ��
    thetas = -90:90;
%   Ԥ��һЩ���õ�ֵ����������ڽ��м���
    cos_t = cosd(thetas);
    sin_t = sind(thetas);
    num_thetas = length(thetas);
    
%   ��ʼ��������������
    accumulator = zeros(2*diag_len+1, num_thetas);
    [xs,ys] = find(img);%�ҳ���Ϊ0�����ص㣬��ʱ��������������ϽǶ��Ե�
    temp = ys;
    ys = size(img,1) - xs;
    xs = temp;          %��ʱԭ�������½�
    
%   �����в�Ϊ0�����ص����ת��
%   ����thetaȷ����Ӧ��rhoֵ
%   ���Լ����������ۼ�
%   ��Ĵ���

%   ��Ĵ���
end