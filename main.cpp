#include"CLEYERA/CLEYERA.h"
#include"Game/Game.h"

#define TriangleMax 3


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game::Initialize();

	Game::Run();

	Game::Finalize();


	return 0;
}
