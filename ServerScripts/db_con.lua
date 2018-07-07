-- Database connection information:
hostname = "127.0.0.1"
port = 3306
username = "root"
password = "password"
database = "Anthera"

function db_con ()
	print("init: db_con.lua")
end

function connect ()
	handle = mysql_init(nil)
	if mysql_real_connect(handle, hostname, username, password, database, port, nil, 0) == nil then
		print("Database connect failed: " .. mysql_error(handle))
		return nil
	end
	print("Database connect - Success")
	return handle
end

function ping (handle)
	if handle ~= nil then
		if mysql_ping(handle) ~= 0 then
			print(mysql_error(handle))
			return false
		end
		return true
	end
	return false
end

function disconnect (handle)
	print("Mysql connection closing...")
	mysql_close(handle)
end
