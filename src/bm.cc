/*
 * Copyright (c) 2001 by Alexander V. Lukyanov (lav@yars.free.net)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* $Id$ */

#include <config.h>
#include <assert.h>
#include "edit.h"
#include "bm.h"

#define N 256

static TextPoint *bm[N];

void SetBookmark(int n)
{
   assert(n>=0 && n<N);
   if(bm[n])
      *bm[n]=CurrentPos;
   else
      bm[n]=new TextPoint(CurrentPos);
}

void ClearBookmark(int n)
{
   assert(n>=0 && n<N);
   if(bm[n])
   {
      delete bm[n];
      bm[n]=0;
   }
}

void GoBookmark(int n)
{
   assert(n>=0 && n<N);
   if(bm[n])
      CurrentPos=*bm[n];
}

void ResetBookmarks()
{
   for(int i=0; i<N; i++)
      ClearBookmark(i);
}
