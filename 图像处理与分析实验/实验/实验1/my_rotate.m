% [img_out,a,b]=my_rotate(img,angle)
% 功能：演示自定义子函数，旋转图像。
% 输出参数：img_out 旋转后图像
% a,b 2个自定义参数，无特别含义，仅为了演示在自定义函数中可以自定义参数
% 输入参数：img 输入图像
% angle 旋转角度

function [img_out,a,b] = my_rotate( img_input, angle)

a=1;
b=2;
img_out=imrotate(img_input, angle);




