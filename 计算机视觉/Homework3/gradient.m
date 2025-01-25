% %����gradient������ݶȴ�С�ͷ���ļ���
% G��theta�ĳߴ���img��ͬ
% G��ÿ�����ص㶼�������ݶȵĴ�С
% theta��ÿ�����ص㶼�������ݶȵķ��򣬲���ֵ��[0��,360��]֮��
function [G, theta] = gradient(img)
    Gx = partial_x(img);
    Gy = partial_y(img);
    G=sqrt(Gx.^2+Gy.^2);
    theta=atan2d(Gy,Gx);
    theta(theta<0)=theta(theta<0)+360;
end