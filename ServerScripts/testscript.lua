function init ()
	print("Hello from testscript.lua")
	mysqlSystem = MySqlSystem()
	mysqlSystem.TestFunctionVariadic(8, 9, 10, 11, 12, 13, 14)
    print("Done")
end

function Register(serverClient)
	print("Register called(Lua)!")
	print("Loginname:" .. serverClient.authData.loginname)
end