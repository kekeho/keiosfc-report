dictionary = {"dog" => "犬", "cat" => "猫"}

loop do
    print "英語: "
    en = gets.chomp()
    if dictionary[en] then
        puts "日本語: #{dictionary[en]}"
    else
        print "#{en}の日本語訳を教えて下さい: "
        ja = gets.chomp()
        dictionary[en] = ja
    end
end
