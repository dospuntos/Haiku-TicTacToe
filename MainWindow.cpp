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
	M_BUTTON_CLICKED = 'btcl',
	M_BUTTON_0_0 = 'bt00',
	M_BUTTON_0_1 = 'bt01',
};




MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,380,400),"Tic Tac Toe for Haiku",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	
	BRect r(Bounds());
	r.bottom = 20;
	fMenuBar = new BMenuBar(r,"menubar");
	AddChild(fMenuBar);
	
	BString board[3][3] 
	{
		{"X", "0", "X"},
		{"X", "0", "X"},
		{"X", "0", "X"}
	};
	
	DrawBoard();
	
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
			//name << (row + 1) + (col) + (row * 2);
			name << board[row][col];
		
			BPoint start(x, y);
			BSize size(buttonWidthHeight, buttonWidthHeight);
		
			BRect buttonSize(start, size);
			BButton *button = new BButton(buttonSize,"button",name,
								new BMessage('bt00'));
			button->SetFlat(true);
			AddChild(button);
		}
	}
}

void DrawBoard() {
	BAlert *test = new BAlert("Alert","Drawing the board", "OK");
	test->Go();
}


void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case 'bt00':
		{
			BAlert *alert;
			alert = new BAlert("Alert","Thank you for clicking the button", "OK");
			alert->Go();
		}
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
