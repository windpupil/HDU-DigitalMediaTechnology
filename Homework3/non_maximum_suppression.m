%����`non_maximum_suppression`����˷Ǽ���ֵ����
function result = non_maximum_suppression(G ,theta)
    % ���Ƕ�round�������45����ȥ
    theta = floor((theta + 22.5) / 45) * 45;
    result = zeros(size(G));
    
    %��ʾ������theta��ʱ������Ĭ������Ϊx������������Ϊy��������
    %���ԣ�����45��ȽǶȵĴ����ע�⡣
    %   ��Ĵ���
for i = 2: length(G(:, 1)) - 1
    for j = 2: length(G(1, :)) - 1
        dirc = alpha(i, j);         % �ĸ����������жϲ����з�������ƣ����������
                                    % [1 2 3;4 5 6;7 8 9]����Ե��[4 5 6]������
                                    % ô���ǹ��ĵ���Ԫ��2��Ԫ��8��Ԫ��5�Ĵ�С��ϵ
        if abs(dirc) <= pi / 8
            if G(i, j) == max([(G(i, j - 1)), G(i, j), G(i, j + 1)])%��ֱ�ݶȣ�ˮƽ��Ե
                result(i, j) = G(i, j);
            end
        elseif abs(dirc) >= 3 * pi / 8
            if G(i, j) == max([(G(i - 1, j)), G(i, j), G(i + 1, j)])%ˮƽ�ݶȣ���ֱ��Ե
                result(i, j) = G(i, j);
            end
        elseif dirc > pi / 8 && dirc < 3 * pi / 8
            if G(i, j) == max([(G(i - 1, j - 1)), G(i, j), G(i + 1, j + 1)])
                result(i, j) = G(i, j);
            end
        elseif dirc > - 3 * pi / 8 && dirc < - pi / 8
            if G(i, j) == max([(G(i + 1, j - 1)), G(i, j), G(i - 1, j + 1)])
                result(i, j) = G(i, j);
            end
        end
    end
end
    %   ��Ĵ���
end