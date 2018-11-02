#include <db_con.py>
#include <globals.py>

gameServer = GameServer.GetGameServerInstance()
menuSys = gameServer.GetMenuSystem()
worldSys = gameServer.GetWorldSystem()

def Register(serverClient):
    inst = GameServer.GetGameServerInstance()
    escapedLoginname = mysql.RealEscapeString(serverClient.loginData.loginname)
    escapedPassword = mysql.RealEscapeString(serverClient.loginData.password)
    
    query = "INSERT INTO `Clients` " \
            "(`loginname`, `password`, `register_time`) " \
            "VALUES('" + escapedLoginname + "', MD5('" + escapedPassword + "'), NOW());"
    if(mysql_query(mysql.handle, query)):
        print("Error Register query: " + mysql_error(mysql.handle))
        menuSys.ShowTimedNotification(serverClient, NotificationText("Loginname bereits vergeben!", notifyPosY, red, 4))
        return
    else:
        if(mysql_affected_rows(mysql.handle) != 0):
            print("Registered: " + serverClient.loginData.loginname)
            menuSys.ShowTimedNotification(serverClient, NotificationText(escapedLoginname + " erfolgreich registriert!", notifyPosY, green, 4))

def Login(serverClient):
    inst = GameServer.GetGameServerInstance()
    escapedLoginname = mysql.RealEscapeString(serverClient.loginData.loginname)
    escapedPassword = mysql.RealEscapeString(serverClient.loginData.password)

    query = "SELECT `id`, `register_time` FROM `Clients` " \
			"WHERE `loginname` = '" + escapedLoginname + "' AND `password` = MD5('" + escapedPassword + "');"
    if(mysql_query(mysql.handle, query)):
        print("Error Login query: " + mysql_error(mysql.handle))
        menuSys.ShowTimedNotification(serverClient, NotificationText("Abnormaler Fehler aufgetreten!", notifyPosY, red, 10))
        return
    else:
        result = mysql_store_result(mysql.handle)
        if(mysql_num_rows(result) == 1):
            print("Login successfull. User: " + escapedLoginname)
            menuSys.ShowTimedNotification(serverClient, NotificationText("Login erfolgreich!", notifyPosY, green, 4))
            worldSys.LoadWorld(serverClient, worldSys.GetStoredWorld(1))
        else:
            print("Login incorrect. User: " + serverClient.loginData.loginname)
            menuSys.ShowTimedNotification(serverClient, NotificationText("Login fehlerhaft!", notifyPosY, red, 8))
            mysql_free_result(result)

#Initialization:
if mysql.Connect():
    print("Loginsystem startup complete!")
else:
    print("Connection to database " + mysql.database + " failed!")
