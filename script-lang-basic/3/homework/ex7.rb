def arraycalc(a, b)
    i = 0
    while i < a.length do
        yield a[i], b[i]
        i += 1
    end
end

arraycalc([1,2,3], [4,5,6]){|x,y| x*y}
