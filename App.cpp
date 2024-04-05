#include "App.h"
#include "MainWindow.h"


App::App(void)
	:	BApplication("application/x-vnd.jw-TicTacToe")
{
	MainWindow *mainwin = new MainWindow();
	mainwin->Show();
	mainwin->Activate();
}


int
main(void)
{
	App *app = new App();
	app->Run();
	delete app;
	return 0;
}
