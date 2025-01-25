% ��һ�����
function out=normalized_cross_correlation(image, kernel)
% ��Ĵ���
[a,b]=size(kernel);
all=sum(sum(kernel));
ave=all/(a*b);
s=std2(kernel);
for i=1:a
    for j=1:b
        kernel(i,j)=(kernel(i,j)-ave)/s;
    end
end
img=double(image);%�������ʱ��ʹ��double����


[m,n]=size(img);
result=zeros(m,n);
img1=zero_pad(img,a-1,b-1);
img2=img1;
for i=1:m
    for j=1:n
        x1=mean2(img1(i+1:i+a,j+1:j+b));
        x2=std2(img1(i+1:i+a,j+1:j+b));
        for k=1:a
            for l=1:b
                img2(i+k,j+l)=(img1(i+k,j+l)-x1)/x2;
            end
        end
        mat=img2(i+1:i+a,j+1:j+b).*kernel;
        result(i,j)=sum(mat(:));
    end
end
out=result;
% ��Ĵ���
end
