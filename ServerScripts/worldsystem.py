#include <db_con.py>

def LoadWorlds():
    gameserver = GameServer.GetGameServerInstance()
    query = "SELECT `id`, `world_name` FROM `Worlds`;"
    if(mysql_query(mysql.handle, query)):
        print("Error while reading worlds from db: " + mysql_error(mysql.handle))
    else:
        result = mysql_store_result(mysql.handle)
        for i in range(mysql_num_rows(result)):
            row = mysql_fetch_row(result)
            id        = mysql.FetchRowElement(row, 0)
            worldName = mysql.FetchRowElement(row, 1)
            gameserver.GetWorldSystem().AddWorld(int(id), worldName)
            print("Added world: " + worldName)
        mysql_free_result(result)

#Initialization:
print("Startup of WorldSystem!")
if mysql.Connect():
    print("Database connected.")
    LoadWorlds()
    print("Worldsystem startup complete!")
else:
    print("Error connecting to the database: " + mysql.database)
