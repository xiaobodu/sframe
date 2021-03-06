
#include <stdio.h>
#include <thread>
#include "ConfigManager.h"
#include "ClientManager.h"
#include "util/Log.h"
#include "net/SendBuffer.h"
#include "util/TimeHelper.h"

bool g_running = true;

void Exec()
{
	while (g_running)
	{
		ClientManager::Instance().Update();
	}
}

int main()
{
	SET_LOG_DIR("./client_log");

	std::string err;
	if (!ConfigManager::InitializeConfig("./client_data", err))
	{
		LOG_ERROR << "config error:" << err << ENDL;
		return -1;
	}

	if (!ClientManager::Instance().Init())
	{
		LOG_ERROR << "Init ClientManager error" << ENDL;
		return -1;
	}

	std::thread t(Exec);
	getchar();
	/*while (true)
	{
		sframe::TimeHelper::ThreadSleep(2000);
	}*/

	ClientManager::Instance().Close();
	g_running = false;
	t.join();

	return 0;
}