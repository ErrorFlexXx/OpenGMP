handle = 0 # Handle to database connection

def Init():
	global handle # Want to modify global handle here.
	print("Hello from Init of testscript.py")
	handle = connect()
	if ping(handle): # Connection open ?
		doIt()

def doIt():
	if	ping(handle):
		print("Updating worlds name.")
		mysql_query(handle, "Update worlds set worldname='TestWorld' where w_id = 1;")
	else:
		print("Db down :(")

def Register(serverClient):
	print("Register called(Python)!")
	print("Loginname: " + serverClient.authData.loginname)


