#include <db_con.py>
#include <globals.py>

gameServer = GameServer.GetGameServerInstance()
menuSys = gameServer.GetMenuSystem()
worldSys = gameServer.GetWorldSystem()
playerCtrl = gameServer.GetPlayerController()

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

def ClientEnteredWorld(serverClient):
    print("GetNewPlayer")
    player = playerCtrl.GetNewPlayer(serverClient)
    print("Got new player.")
    player.visual.bodyModel = "Hum_Body_Naked0"
    player.visual.bodyTextureId = 9
    player.visual.headModel = "Hum_Head_Pony"
    player.visual.headTextureId = 18
    player.visual.fatness = 1
    player.position = Position(29912.9, 5253.92, -15710, 0)
    player.attributes.health = 100
    player.attributes.max_health = 100
    playerCtrl.SpawnPlayer(player, worldSys.GetStoredWorld(1))
    print("Spawn player.")
    playerCtrl.ControlPlayer(serverClient, player)
    print("Control player")

#Initialization:
if mysql.Connect():
    print("Loginsystem startup complete!")
else:
    print("Connection to database " + mysql.database + " failed!")
