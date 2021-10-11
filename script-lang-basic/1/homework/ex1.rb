# 課題1: 数値を入力して、次のように高さがその段数になるような三角形を表示せよ

n = gets().to_i

i = 1
while i <= n do
    print(' ' * (n-i))
    puts('*'*(i*2-1))
    i += 1
end
