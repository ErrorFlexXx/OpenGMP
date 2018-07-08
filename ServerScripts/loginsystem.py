#include <db_con.py>

handle = 0
stmtRegister = 0

def Init():
	global handle #Modify global var	
	handle = connect()
	if(ping(handle)):
		InitLoginSystemStatements()

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
		return
	if(mysql_stmt_prepare(stmtRegister, registerStatement, len(registerStatement)) != 0):
		print("LoginSystem stmtRegister prepare error: " + mysql_stmt_error(stmtRegister))
	print("InitLoginSystemStatements finished.")
	

def Register(serverClient):
	global stmtRegister
	bindHelper = ScriptMysqlBindHelper()
	bindHelper.AddString(serverClient.authData.loginname)
	bindHelper.AddString(serverClient.authData.password)
	bindHelper.Bind(stmtRegister);	
	if(mysql_stmt_execute(stmtRegister) != 0):
		print("LoginSystem Error stmtRegister: " + mysql_stmt_error(stmtRegister))
	else:
		print("Registered: " + serverClient.authData.loginname)
	bindHelper.ResetBinds()