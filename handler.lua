function ReceivedFromNetwork(buffer)
	dbg(buffer)
	return 1
end

function dbg(...)
	print("LUA DBG:", ...)
end

return 1
