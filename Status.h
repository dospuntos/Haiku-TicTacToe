/*
 * Copyright 1996, 1997, 1998, 2002 Hekkelman Programmatuur B.V.  All rights reserved.
 * Copyright 2018 Adam Fowler <adamfowleruk@gmail.com>
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Adam Fowler, adamfowleruk@gmail.com
 */
#ifndef STATUS_H
#define STATUS_H

#include <StringView.h>

class Status : public BView
{
public:
							Status(BRect frame, BString msg);
							~Status();

	virtual	void 			Draw(BRect updateRect);

			void 			SetOffset(int newOffset);

			void			SetStatus(BString msg);

private:
			BString			fMsg;
			int 			fOffset;
			float 			fBaseline;
};


#endif