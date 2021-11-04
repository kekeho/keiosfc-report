result = ''
IO.foreach('CROSSWD.TXT') do | line |
    if result.length < line.length then
        result = line
    end
end

puts result
