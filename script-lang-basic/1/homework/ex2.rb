# 引数として数値を1個受け取り、それが素数なら true そうでなければ false を返すメソッド(関数)を作れ。ただし、標準のPrimeクラスを使ってはいけない。
def is_prime?(x)
    i = 2
    while i < x do
        if (x.modulo(i) == 0) then
            return false
        end
        i += 1
    end

    return true
end


x = gets().to_i()
puts is_prime?(x)
