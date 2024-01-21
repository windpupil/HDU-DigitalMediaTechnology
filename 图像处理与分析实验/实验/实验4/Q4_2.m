img = imread('lenaÌõÎÆÔëÉù.bmp');
img = rgb2gray(img);
fd_img = log(1+computeAmplitudeImage(img));
outimg = notchFilter(img,42,15);
outimg = notchFilter(outimg,90,18);
outimg = notchFilter(outimg,135,15);
outimg = notchFilter(outimg,190,15);
outimg = notchFilter(outimg,238,15);

outfdimg = log(1+computeAmplitudeImage(outimg));
subplot(2,2,1),imshow(img,[]),title('Ô­Í¼');
subplot(2,2,2),imshow(fd_img,[]),title('·ù¶ÈÍ¼');
subplot(2,2,3),imshow(outimg,[]),title('Ïİ²¨ÂË²¨Æ÷');
subplot(2,2,4),imshow(outfdimg,[]),title('ÂË²¨ºó·ù¶ÈÍ¼');
function img_fft_shift = computeAmplitudeImage(img)
    img_fft=fft2(img);%¶şÎ¬ÀëÉ¢¸µÁ¢Ò¶±ä»»
    img_fft_shift=fftshift(img_fft);%¾ÓÖĞ
    img_fft_shift=abs(img_fft_shift);  
end

%Ïİ²¨ÂË²¨Æ÷
function filteredImage = notchFilter(image,height,radius)
    if size(image, 3) == 3
        image = rgb2gray(image);
    end

    F = fftshift(fft2(im2double(image)));
    [a, b] = size(F);
    a0 = round(a / 2);
    b0 = round(b / 2);
    a1 = a0-height;
    a2 = a0+height;
    notchMask = ones(a, b);
 
    for i = 1:a
         for j = 1:b
              distance1 = sqrt((i - a1)^2 + (j - b0)^2);
              distance2 = sqrt((i - a2)^2 + (j - b0)^2);
              if distance1<= radius
                 notchMask(i,j) = 0;
              end
              if distance2<= radius
                 notchMask(i,j) = 0;
              end
         end
    end
   
    F = F .* notchMask;
    
    filteredImage = real(ifft2(ifftshift(F)));
end
