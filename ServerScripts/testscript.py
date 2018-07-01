def init():
	print("Hello from testscript.py :)")

def Register(serverClient):
	print("Register called!")
	print("Loginname: " + serverClient.authData.loginname)
