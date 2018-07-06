def Init():
	print("Hello from testscript.py")
	'''
	handle = mysql_init(0)
	handle = mysql_real_connect(handle, "127.0.0.1", "root", "password", "Anthera",  3306, 0, 0)
	mysql_query(handle, "Update worlds set worldname='PYTHONWorld' where w_id = 1;")
	mysql_close(handle)
	'''
	print("Done")

def Register(serverClient):
	print("Register called(Python)!")
	print("Loginname: " + serverClient.authData.loginname)


