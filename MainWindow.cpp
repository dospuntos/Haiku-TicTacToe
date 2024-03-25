#include "MainWindow.h"

#include <Application.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Button.h>
#include <Alert.h>
#include <View.h>
#include <String.h>
#include <Size.h>

enum
{
	M_BUTTON_CLICKED = 'btcl'
};

BString board[3][3];
BString currentPlayer = "X";

MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,380,400),"Tic Tac Toe for Haiku",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{

	BRect r(Bounds());
	r.bottom = 20;
	fMenuBar = new BMenuBar(r,"menubar");
	AddChild(fMenuBar);

	DrawBoard();
}

void
MainWindow::DrawBoard() {
	/* Create multiple buttons */

	int buttonWidthHeight = 80;
	int x = 10; // Start top left
	int y = 30; // And below menu bar

	for (int row = 0; row < 3; row++)
	{
		if (row > 0) y =  y + buttonWidthHeight + 10;
		x = 10;
		for (int col = 0; col < 3; col++)
		{
			if (col > 0) x = x + buttonWidthHeight + 10;
			BString name("");
			name << board[row][col];

			BPoint start(x, y);
			BSize size(buttonWidthHeight, buttonWidthHeight);

			BMessage *msg = new BMessage(M_BUTTON_CLICKED);
			msg->AddInt16("row", row);
			msg->AddInt16("col", col);

			BRect buttonSize(start, size);
			BButton *button = new BButton(buttonSize,"button",name,msg);
			button->SetFlat(true);
			AddChild(button);
		}
	}
}


void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case M_BUTTON_CLICKED:
		{
			int16 row = msg->FindInt16("row");
			int16 col = msg->FindInt16("col");
			if (board[row][col] == "") { // Clicked on empty cell
				board[row][col] = currentPlayer;
				currentPlayer = (currentPlayer == "X") ? "O" : "X";
				DrawBoard();
			} else {
				BAlert *message = new BAlert("Not valid", "Please click an empty button", "OK");
				message->Go();
			}
		} break;
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
