#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include <MenuBar.h>

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

};

#endif
