# Database connection information:
hostname = "127.0.0.1" 				#Hostname (default localhost/127.0.0.1)
port = 3306 											#Port (Default Mysql port: 3306)
username = "root" 							#Mysql Username
password = "password" 				#Mysql Password
database = "Database"				#Database name

# Initially connects to the database server.
def connect():
	handle = mysql_init(0)	
	if mysql_real_connect(handle, hostname, username, password, database,  port, 0, 0) == None:
		print("Database connect FAILED: " + mysql_error(handle))
		return 0
	print("Database connect - Success")
	return handle

# Checks connection - reopens if necessary.
def ping(handle):
	if handle != 0:	
		if mysql_ping(handle) != 0:
			print(mysql_error(handle))
			return False #Con broken
		return True #Con ok
	return False # handle is 0

def disconnect(handle):
	print("Mysql connection closing...")
	mysql_close(handle)