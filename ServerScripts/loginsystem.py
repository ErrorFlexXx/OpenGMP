#include <db_con.py>

handle = 0
stmtRegister = 0
bindHelper = ScriptMysqlBindHelper()

#cpgf._import(None, "builtin");
#cpgf._import("cpgf", "builtin.collections.bytearray");


def InitLoginSystemStatements():
	
	# Register statement
	registerStatement = (
	"INSERT INTO `ServerClients` "
	"(`loginname`, `password`, `register_time`) "
	"VALUES(?, MD5(?), NOW());")
	global stmtRegister	
	stmtRegister = mysql_stmt_init(handle)
	if stmtRegister == None:
		print("LoginSystem initLoginSystemStatements - Out of memory")
		return False
	if mysql_stmt_prepare(stmtRegister, registerStatement, len(registerStatement)) != 0:
		print("LoginSystem stmtRegister prepare error: " + mysql_stmt_error(stmtRegister))
		return False
	return True

def Register(serverClient):
	global stmtRegister
	global bindHelper
	bindHelper.AddString(serverClient.authData.loginname)
	bindHelper.AddString(serverClient.authData.password)
	bindHelper.Bind(stmtRegister)
	
	if mysql_stmt_execute(stmtRegister) != 0:
		print("LoginSystem Error stmtRegister: " + mysql_stmt_error(stmtRegister))
	else:
		print("Registered: " + serverClient.authData.loginname)
	bindHelper.ResetBinds()

#Initialization:
handle = connect()
if ping(handle) == False:
	print("LoginSystem startup failed - Database not available!")
elif InitLoginSystemStatements() == False:
	print("LoginSystem startup failed - InitLoginSystemStatements failed!")
else:
	print("LoginSystem startup complete!")
