handle = 0 # Handle to database connection

#include <db_con.py>

def doIt():
	if	ping(handle):
		print("Updating worlds name.")
		mysql_query(handle, "Update worlds set worldname='TestWorld' where w_id = 1;")
	else:
		print("Db down :(")

#Initialization:
print("Init: testscript.py")
handle = connect()
if ping(handle): # Connection open ?
	doIt()