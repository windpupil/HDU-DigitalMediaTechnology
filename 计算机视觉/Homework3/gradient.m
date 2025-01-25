% %函数gradient完成了梯度大小和方向的计算
% G和theta的尺寸与img相同
% G中每个像素点都保存了梯度的大小
% theta中每个像素点都保存了梯度的方向，并且值在[0°,360°]之间
function [G, theta] = gradient(img)
    Gx = partial_x(img);
    Gy = partial_y(img);
    G=sqrt(Gx.^2+Gy.^2);
    theta=atan2d(Gy,Gx);
    theta(theta<0)=theta(theta<0)+360;
end