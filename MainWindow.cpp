#include "MainWindow.h"

#include <Application.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Button.h>
#include <Alert.h>
#include <View.h>
#include <String.h>
#include <Size.h>
#include <ScrollBar.h>

enum
{
	M_BUTTON_CLICKED = 'btcl',
	M_NEW_GAME = 'nwgm'
};

BString board[3][3];
BString currentPlayer = "X";
int buttonWidthHeight = 180;


MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,(buttonWidthHeight * 3) + 140,(buttonWidthHeight * 3) + 160 + B_H_SCROLL_BAR_HEIGHT),
			"Tic Tac Toe for Haiku", B_TITLED_WINDOW, B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS)
{

	BRect r(Bounds());
	r.bottom = B_H_SCROLL_BAR_HEIGHT - 1;
	fMenuBar = new BMenuBar(r,"menubar");
	fMenu = new BMenu("Game");
	fMenu->AddItem(new BMenuItem(
		"New game", new BMessage(M_NEW_GAME), 'N'));
	fMenu->AddSeparatorItem();
	fMenu->AddItem(new BMenuItem(
		"About Tic Tac Toe", new BMessage(B_ABOUT_REQUESTED)));
	fMenu->AddItem(new BMenuItem(
		"Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	fMenuBar->AddItem(fMenu);

	AddChild(fMenuBar);

	DrawBoard();

	// create status bar
	BRect s(Bounds());
	s.top = s.Height() - B_H_SCROLL_BAR_HEIGHT;
	fStatusBar = new Status(s, "Current player: X");
	fStatusBar->SetExplicitMinSize(BSize(B_SIZE_UNSET,
		B_H_SCROLL_BAR_HEIGHT - 1));
	fStatusBar->SetExplicitMaxSize(BSize(B_SIZE_UNSET,
		B_H_SCROLL_BAR_HEIGHT - 1));
	fStatusBar->SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
		B_ALIGN_BOTTOM));

	AddChild(fStatusBar);

}


void
MainWindow::DrawBoard() {
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
			button->SetFlat(false);
			AddChild(button);
		}
	}
}

// Function to check for a win
bool MainWindow::CheckWin()
{
	//Check rows, columns, and diagonals
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
			return true;
		if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
			return true;
	}
	if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
		return true;
	if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
		return true;
	return false;
}

bool MainWindow::CheckDraw()
{
	// Reset board array
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			if (board[i][j] == "") return false;
	}
	return true;
}

void
MainWindow::AnnounceWinner()
{
	BString text;
	text << "Player " << currentPlayer << " won the game!";
	BAlert *message = new BAlert("Congratulations", text, "OK");
	message->Go();

	ResetGame();
}

void
MainWindow::AnnounceDraw()
{
	BAlert *message = new BAlert("Draw", "The game ended in a draw!", "OK");
	message->Go();

	ResetGame();
}

void MainWindow::ResetGame()
{
	// Reset board array
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			board[i][j] = "";
	}

	// Set player to X
	currentPlayer = "X";
	fStatusBar->SetStatus("Current player: X");
	DrawBoard();
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
				DrawBoard();
				if (CheckWin()) {
					AnnounceWinner();
					break;
				}
				if (CheckDraw()) {
					AnnounceDraw();
					break;
				}
				currentPlayer = (currentPlayer == "X") ? "O" : "X";

				BString statusMessage = "Current player: ";
				statusMessage << currentPlayer;
				fStatusBar->SetStatus(statusMessage.String());
			} else {
				fStatusBar->SetStatus("Please click an empty button");
			}
		} break;

		case M_NEW_GAME:
		{
			ResetGame();
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
