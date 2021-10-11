# ex2.rbを, 2より小さい数値を入力したら再入力させるように改良する
def is_prime?(x)
    if x < 2 then
        raise RuntimeError
    end


    i = 2
    while i < x do
        if (x.modulo(i) == 0) then
            return false
        end
        i += 1
    end

    return true
end


while true do
    x = gets().to_i()
    begin
        puts is_prime?(x)
        return
    rescue RuntimeError
        puts "数字を再入力してください"
    end
end
