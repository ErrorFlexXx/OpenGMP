def init():
	print("Script init...")
	inst = GameServer.GetGameServerInstance()
	inst.testAttribute = 10
	inst.Shutdown()