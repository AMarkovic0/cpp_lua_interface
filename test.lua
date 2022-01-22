print("Hello From Lua!")

x = 1.11
x1 = 2
y = "Lua String"
z = nil

function addLua(x, y)
	return x + y
end


return 1, 2.33, add(x1, 2*x1)
