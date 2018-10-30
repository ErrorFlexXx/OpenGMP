#include <db_con.py>

def Register(serverClient):
	inst = GameServer.GetGameServerInstance()
	escapedLoginname = mysql.RealEscapeString(serverClient.loginData.loginname)
	escapedPassword = mysql.RealEscapeString(serverClient.loginData.password)
    
	query = "INSERT INTO `ServerClients` " \
			"(`loginname`, `password`, `register_time`) " \
			"VALUES('" + escapedLoginname + "', MD5('" + escapedPassword + "'), NOW());"
	if(mysql_query(mysql.handle, query)):
		print("Error Register query: " + mysql_error(mysql.handle))
		notify = NotificationText()
		notify.text = "Loginname bereits vergeben!"
		notify.color = Color(255, 0, 0, 255)
		notify.duration = 4
		notify.posY = 20
		return
	else:
		if(mysql_affected_rows(mysql.handle) != 0):
			print("Registered: " + serverClient.loginData.loginname)
			notify = NotificationText()
			notify.text = escapedLoginname + " erfolgreich registriert!"
			notify.color = Color(0, 255, 0, 255)
			notify.duration = 5
			notify.posY = 20
			inst.GetMenuSystem().ShowTimedNotification(serverClient, notify)
		else:
			print("Not registered " + serverClient.loginData.loginname + ". Loginname not free ?")

def Login(serverClient):
	inst = GameServer.GetGameServerInstance()
	escapedLoginname = mysql.RealEscapeString(serverClient.loginData.loginname)
	escapedPassword = mysql.RealEscapeString(serverClient.loginData.password)

	query = "SELECT `id`, `register_time` FROM `ServerClients` " \
			"WHERE `loginname` = '" + escapedLoginname + "' AND `password` = MD5('" + escapedPassword + "');"
	if(mysql_query(mysql.handle, query)):
		print("Error Login query: " + mysql_error(mysql.handle))
		notify = NotificationText()
		notify.text = "Abnormaler Fehler aufgetreten!"
		notify.color = Color(255, 0, 0, 255)
		notify.duration = 10
		notify.posY = 20
		inst.GetMenuSystem().ShowTimedNotification(serverClient, notify)
		return
	else:
		result = mysql_store_result(mysql.handle)
		if(mysql_num_rows(result) == 1):
			print("Login successfull. User: " + escapedLoginname)
			notify = NotificationText()
			notify.text = "Login erfolgreich!"
			notify.color = Color(0, 255, 0, 255)
			notify.duration = 4
			notify.posY = 20
			inst.GetMenuSystem().ShowTimedNotification(serverClient, notify)
		else:
			print("Login incorrect. User: " + serverClient.loginData.loginname)
			notify = NotificationText()
			notify.text = "Login fehlerhaft!"
			notify.color = Color(255, 0, 0, 255)
			notify.duration = 8
			notify.posY = 20
			inst.GetMenuSystem().ShowTimedNotification(serverClient, notify)
		#mysql_free_result(result)

def TestRegister();
    name = "Han'nes"
    password = "Johannes"
    escapedLoginname = mysql.RealEscapeString(serverClient.loginData.loginname)
	escapedPassword = mysql.RealEscapeString(serverClient.loginData.password)
    
	query = "INSERT INTO `ServerClients` " \
			"(`loginname`, `password`, `register_time`) " \
			"VALUES('" + escapedLoginname + "', MD5('" + escapedPassword + "'), NOW());"
	if(mysql_query(mysql.handle, query)):
		print("Error Register query: " + mysql_error(mysql.handle))
		return
	else:
		if(mysql_affected_rows(mysql.handle) != 0):
			print("Registered: " + serverClient.loginData.loginname)
		else:
			print("Not registered " + serverClient.loginData.loginname + ". Loginname not free ?")

#Initialization:
if mysql.Connect()
    print("Connected to database - " + mysql.database)
    TestRegister()
    print("Loginsystem startup complete!")
else
    print("Connection to database " + mysql.database + " failed!"
