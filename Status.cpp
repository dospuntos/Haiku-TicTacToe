/*
 *
 *	Copyright 1996, 1997, 1998, 2002
 *	        Hekkelman Programmatuur B.V.  All rights reserved.
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *	1. Redistributions of source code must retain the above copyright notice,
 *	   this list of conditions and the following disclaimer.
 *	2. Redistributions in binary form must reproduce the above copyright notice,
 *	   this list of conditions and the following disclaimer in the documentation
 *	   and/or other materials provided with the distribution.
 *	3. All advertising materials mentioning features or use of this software
 *	   must display the following acknowledgement:
 *	    This product includes software developed by Hekkelman Programmatuur B.V.
 *	4. The name of Hekkelman Programmatuur B.V. may not be used to endorse or
 *	   promote products derived from this software without specific prior
 *	   written permission.
 *
 *
 * Copyright 2018-2019 Adam Fowler <adamfowleruk@gmail.com>
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Adam Fowler, adamfowleruk@gmail.com
 */

#include "Status.h"

Status::Status(BRect frame, BString txt)
	: BView(frame, "status", B_FOLLOW_BOTTOM | B_FOLLOW_LEFT, B_WILL_DRAW)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	BFont font(be_plain_font);
	font.SetSize(10);
	SetFont(&font);

	font_height fh;
	font.GetHeight(&fh);
	fBaseline = fh.descent + fh.ascent - 3;

	fOffset = 0;
	fMsg = txt;
}

Status::~Status()
{
}

void
Status::SetStatus(BString msg) {
	fMsg = msg;
	Draw(Bounds());
}

void
Status::Draw(BRect updateRect)
{
	BRect bounds(Bounds());

	FillRect(bounds,B_SOLID_LOW);

	SetHighColor(tint_color(ViewColor(), B_DARKEN_2_TINT));
	StrokeLine(bounds.LeftTop(), bounds.RightTop());

	SetHighColor(ui_color(B_PANEL_TEXT_COLOR));
	MovePenTo(3, fBaseline);
	DrawString(fMsg);
}

void
Status::SetOffset(int newOffset)
{
	fOffset = newOffset;
	Draw(Bounds());
}