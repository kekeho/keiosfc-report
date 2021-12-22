results = []

while true do
    print('数値? ')
    x = gets().to_i()

    if x <= 0 then
        break
    end

    results.push(x)
end

results.length.times do |i|
    x = results[results.length - (i+1)]
    puts(x)
end
