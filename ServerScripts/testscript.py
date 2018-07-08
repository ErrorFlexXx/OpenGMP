handle = 0 # Handle to database connection

#include <db_con.py>

def Init():
	global handle # Modify global, not local
	print("Init: testscript.py")
	handle = connect()
	if ping(handle): # Connection open ?
		doIt()

def doIt():
	if	ping(handle):
		print("Updating worlds name.")
		mysql_query(handle, "Update worlds set worldname='TestWorld' where w_id = 1;")
	else:
		print("Db down :(")

def HelloWorld():
	print("Hello World!")

def Register(serverClient):
	print("Register called(Python)!")
	print("Loginname: " + serverClient.authData.loginname)

#def HelloWorld():
#	print("HelloWorldTestScript.py")


