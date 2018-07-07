require("db_con")

function testscript2 ()
	print("Init: testscript2.lua")
	handle = connect()
	if ping(handle) then
		doIt()
	end
end

function doIt ()
	if ping(handle) then
		print("Updateing worlds name.")
		mysql_query(handle, "Update worlds set worldname='LuaWorld' where w_id = 1;")
	else
		print("Db down :(")
	end
end

function Register(serverClient)
	print("Register called(Lua)!")
	print("Loginname:" .. serverClient.authData.loginname)
end

function HelloWorld ()
	print("HelloWorldTestScript")
end
