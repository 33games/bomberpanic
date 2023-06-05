#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")


enum class main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[])
{
	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = main_states::MAIN_CREATION;


	srand(time(0));

	while (state != main_states::MAIN_EXIT)
	{
		switch (state)
		{
			case main_states::MAIN_CREATION:
			{
				LOG("Application Creation --------------\n");
				App = new Application();
				state = main_states::MAIN_START;
			}	break;

			case main_states::MAIN_START:
			{
				LOG("Application Start --------------\n");
				if(App->Init() == false)
				{
					LOG("Application Init exits with error -----\n");
					state = main_states::MAIN_EXIT;
				}
				else
				{
					state = main_states::MAIN_UPDATE;
				}
			}	break;

			case main_states::MAIN_UPDATE:
			{
				Update_Status status = App->Update();

				if (status == Update_Status::UPDATE_ERROR)
				{
					LOG("Application Update exits with error -----\n");
					state = main_states::MAIN_EXIT;
				}
				else if (status == Update_Status::UPDATE_STOP)
				{
					state = main_states::MAIN_FINISH;
				}
			}	break;

			case main_states::MAIN_FINISH:
			{
				LOG("Application Finish --------------\n");
				if (App->CleanUp() == true)
				{
					main_return = EXIT_SUCCESS;
				}
				else
				{
					LOG("Application CleanUp exits with error -----\n");
				}
				state = main_states::MAIN_EXIT;
			}
		}
	}

	LOG("\nStopping...\n");

	delete App;

	return main_return;
}