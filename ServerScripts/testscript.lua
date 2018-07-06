function Init ()
	print("Hello from testscript.lua")
	--[[
	handle = mysql_init(nil)
	handle = mysql_real_connect(handle, "127.0.0.1", "root", "password", "Anthera", 3306, nil, 0)
	mysql_query(handle, "UPDATE worlds SET worldname='LUAWorld' WHERE w_id = 1;")
	mysql_close(handle)
	]]
    print("Done")
end

function Register(serverClient)
	print("Register called(Lua)!")
	print("Loginname:" .. serverClient.authData.loginname)
end