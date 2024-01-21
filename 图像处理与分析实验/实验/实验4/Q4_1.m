img = imread('¸ñ×ÓÌõÎÆÔëÉùÍ¼.bmp');
img = rgb2gray(img);
fd_img = log(1+computeAmplitudeImage(img));

outimg = bandFilter(img,3,10);
outfdimg = log(1+computeAmplitudeImage(outimg));
subplot(2,2,1),imshow(img,[]),title('Ô­Í¼');
subplot(2,2,2),imshow(fd_img,[]),title('·ù¶ÈÍ¼');
subplot(2,2,3),imshow(outimg,[]),title('´ø×èÂË²¨Æ÷');
subplot(2,2,4),imshow(outfdimg,[]),title('ÂË²¨ºó·ù¶ÈÍ¼');
function img_fft_shift = computeAmplitudeImage(img)
    img_fft=fft2(img);%¶þÎ¬ÀëÉ¢¸µÁ¢Ò¶±ä»»
    img_fft_shift=fftshift(img_fft);%¾ÓÖÐ
    img_fft_shift=abs(img_fft_shift);
end
%´ø×èÂË²¨Æ÷
function filteredImage = bandFilter(image,width, distance)
    if size(image, 3) == 3
        image = rgb2gray(image);
    end

    F = fftshift(fft2(im2double(image)));
    [a, b] = size(F);
    a0 = round(a / 2);
    b0 = round(b / 2);

    notchMask = ones(a, b);
    
    for i = 1:a0-distance
        for j = b0-round(width/2):b0+round(width/2)
            notchMask(i,j) = 0;
            notchMask(a-i+1,j) = 0;
        end
    end
    for i = 1:a
        for j = b0 - 125-round(width/2):b0 - 125+round(width/2)
            notchMask(i,j) = 0;
            notchMask(i,b-j+1) = 0;
        end
    end
    for i = 1:a
        for j = b0 - 50-round(width/2):b0 - 50+round(width/2)
            notchMask(i,j) = 0;
            notchMask(i,b-j+1) = 0;
        end
    end
    for i = 1:a
        for j = b0 - 75-round(width/2):b0 - 75+round(width/2)
            notchMask(i,j) = 0;
            notchMask(i,b-j+1) = 0;
        end
    end
    for i = 1:a
        for j = b0 - 145-round(width/2):b0 -145+round(width/2)
            notchMask(i,j) = 0;
            notchMask(i,b-j+1) = 0;
        end
    end

    for i = a0-round(width/2):a0+round(width/2)
        for j = 1:b0-distance
            notchMask(i,j) = 0;
            notchMask(i,b-j+1) = 0;
        end
    end
    for i = a0-50-round(width/2):a0-50+round(width/2)
        for j = 1:b
            notchMask(i,j) = 0;
            notchMask(a-i+1,j) = 0;
        end
    end
    for i = a0-115-round(width/2):a0-115+round(width/2)
        for j = 1:b
            notchMask(i,j) = 0;
            notchMask(a-i+1,j) = 0;
        end
    end
    F = F .* notchMask;
    filteredImage = real(ifft2(ifftshift(F)));
end