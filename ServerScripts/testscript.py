def init():
	print("Hello from testscript.py :)")
	mysqlSystem = MySqlSystem()
	print("After construction!")
	mysqlSystem.TestFunctionVariadic(1, 2, 3, 4, 5, 6, 7)
	print(mysqlSystem)
	print("Done")

def Register(serverClient):
	print("Register called(Python)!")
	print("Loginname: " + serverClient.authData.loginname)


