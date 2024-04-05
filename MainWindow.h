#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include <MenuBar.h>
#include <Menu.h>
#include "Status.h"

class MainWindow : public BWindow
{
public:
						MainWindow(void);
			void		MessageReceived(BMessage *msg);
			bool		QuitRequested(void);
			void		DrawBoard();
			bool 		CheckWin();
			bool		CheckDraw();
			void		AnnounceWinner();
			void		AnnounceDraw();
			void		ResetGame();

private:
			BMenuBar	*fMenuBar;
			BMenu 		*fMenu;
			Status		*fStatusBar;
};

#endif
