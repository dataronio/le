/* 
 * Copyright (c) 1993-1997 by Alexander V. Lukyanov (lav@yars.free.net)
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA. 
 */

#include <config.h>
#include <string.h>
#include <ctype.h>
#include "edit.h"
#include "keymap.h"

struct   graphchar
{
   byte  ch;
   byte  prol[4];
};

struct graphchar  DumbCoding[]=
{
/*   {'|',{0,1,0,1}},{'+',{1,1,1,1}},{'-',{1,0,1,0}},{'=',{2,0,2,0}},
   {'+',{1,1,0,0}},{'+',{0,1,1,0}},{'+',{0,0,1,1}},{'+',{1,0,0,1}},*/

   {'|',{0,1,0,1}},{'+',{1,1,0,1}},{'+',{2,1,0,1}},{'+',{1,2,0,2}},
   {'+',{1,0,0,2}},{'+',{2,0,0,1}},{'+',{2,2,0,2}},{'|',{0,2,0,2}},
   {'+',{2,0,0,2}},{'+',{2,2,0,0}},{'+',{1,2,0,0}},{'+',{2,1,0,0}},
   {'+',{1,0,0,1}},{'+',{0,1,1,0}},{'+',{1,1,1,0}},{'+',{1,0,1,1}},
   {'+',{0,1,1,1}},{'-',{1,0,1,0}},{'+',{1,1,1,1}},{'+',{0,1,2,1}},
   {'+',{0,2,1,2}},{'+',{0,2,2,0}},{'+',{0,0,2,2}},{'+',{2,2,2,0}},
   {'+',{2,0,2,2}},{'+',{0,2,2,2}},{'=',{2,0,2,0}},{'#',{2,2,2,2}},
   {'+',{2,1,2,0}},{'+',{1,2,1,0}},{'+',{2,0,2,1}},{'+',{1,0,1,2}},
   {'+',{0,2,1,0}},{'+',{0,1,2,0}},{'+',{0,0,2,1}},{'+',{0,0,1,2}},
   {'+',{1,2,1,2}},{'=',{2,1,2,1}},{'+',{1,1,0,0}},{'+',{0,0,1,1}},
   {' ',{0,0,0,0}},{0,{0,0,0,0}}
};

struct graphchar  AlternativeCoding[]=
{
   {'�',{0,1,0,1}},{'�',{1,1,0,1}},{'�',{2,1,0,1}},{'�',{1,2,0,2}},
   {'�',{1,0,0,2}},{'�',{2,0,0,1}},{'�',{2,2,0,2}},{'�',{0,2,0,2}},
   {'�',{2,0,0,2}},{'�',{2,2,0,0}},{'�',{1,2,0,0}},{'�',{2,1,0,0}},
   {'�',{1,0,0,1}},{'�',{0,1,1,0}},{'�',{1,1,1,0}},{'�',{1,0,1,1}},
   {'�',{0,1,1,1}},{'�',{1,0,1,0}},{'�',{1,1,1,1}},{'�',{0,1,2,1}},
   {'�',{0,2,1,2}},{'�',{0,2,2,0}},{'�',{0,0,2,2}},{'�',{2,2,2,0}},
   {'�',{2,0,2,2}},{'�',{0,2,2,2}},{'�',{2,0,2,0}},{'�',{2,2,2,2}},
   {'�',{2,1,2,0}},{'�',{1,2,1,0}},{'�',{2,0,2,1}},{'�',{1,0,1,2}},
   {'�',{0,2,1,0}},{'�',{0,1,2,0}},{'�',{0,0,2,1}},{'�',{0,0,1,2}},
   {'�',{1,2,1,2}},{'�',{2,1,2,1}},{'�',{1,1,0,0}},{'�',{0,0,1,1}},
   {' ',{0,0,0,0}},{0,{0,0,0,0}}
};
struct graphchar  KOI8Coding[]=
{

/* {'�',{0,1,0,1}},{'�',{1,1,0,1}},{'�',{2,1,0,1}},{'�',{1,2,0,2}},
   {'�',{1,0,0,2}},{'�',{2,0,0,1}},{'�',{2,2,0,2}},{'�',{0,2,0,2}},
   {'�',{2,0,0,2}},{'�',{2,2,0,0}},{'�',{1,2,0,0}},{'�',{2,1,0,0}},
   {'�',{1,0,0,1}},{'�',{0,1,1,0}},{'�',{1,1,1,0}},{'�',{1,0,1,1}},
   {'�',{0,1,1,1}},{'�',{1,0,1,0}},{'�',{1,1,1,1}},{'�',{0,1,2,1}},
   {'�',{0,2,1,2}},{'�',{0,2,2,0}},{'�',{0,0,2,2}},{'�',{2,2,2,0}},
   {'�',{2,0,2,2}},{'�',{0,2,2,2}},{'�',{2,0,2,0}},{'�',{2,2,2,2}},
   {'�',{2,1,2,0}},{'�',{1,2,1,0}},{'�',{2,0,2,1}},{'�',{1,0,1,2}},
   {'�',{0,2,1,0}},{'�',{0,1,2,0}},{'�',{0,0,2,1}},{'�',{0,0,1,2}},
   {'�',{1,2,1,2}},{'�',{2,1,2,1}},{'�',{1,1,0,0}},{'�',{0,0,1,1}},*/

   {'�',{0,1,0,1}},{'�',{1,1,0,1}},{'�',{2,1,0,1}},{'�',{1,2,0,2}},
   {'�',{1,0,0,2}},{'�',{2,0,0,1}},{'�',{2,2,0,2}},{'�',{0,2,0,2}},
   {'�',{2,0,0,2}},{'�',{2,2,0,0}},{'�',{1,2,0,0}},{'�',{2,1,0,0}},
   {'�',{1,0,0,1}},{'�',{0,1,1,0}},{'�',{1,1,1,0}},{'�',{1,0,1,1}},
   {'�',{0,1,1,1}},{'�',{1,0,1,0}},{'�',{1,1,1,1}},{'�',{0,1,2,1}},
   {'�',{0,2,1,2}},{'�',{0,2,2,0}},{'�',{0,0,2,2}},{'�',{2,2,2,0}},
   {'�',{2,0,2,2}},{'�',{0,2,2,2}},{'�',{2,0,2,0}},{'�',{2,2,2,2}},
   {'�',{2,1,2,0}},{'�',{1,2,1,0}},{'�',{2,0,2,1}},{'�',{1,0,1,2}},
   {'�',{0,2,1,0}},{'�',{0,1,2,0}},{'�',{0,0,2,1}},{'�',{0,0,1,2}},
   {'�',{1,2,1,2}},{'�',{2,1,2,1}},{'�',{1,1,0,0}},{'�',{0,0,1,1}},
   {' ',{0,0,0,0}},{0,{0,0,0,0}}
};
struct graphchar  KOI8_linux_Coding[]=
{
   {'�',{0,1,0,1}},{'�',{1,1,0,1}},{'�',{2,1,0,1}},{'�',{1,2,0,2}},
   {'�',{1,0,0,2}},{'�',{2,0,0,1}},{'�',{2,2,0,2}},{'�',{0,2,0,2}},
   {'�',{2,0,0,2}},{'�',{2,2,0,0}},{'�',{1,2,0,0}},{'�',{2,1,0,0}},
   {'�',{1,0,0,1}},{'�',{0,1,1,0}},{'�',{1,1,1,0}},{'�',{1,0,1,1}},
   {'�',{0,1,1,1}},{'�',{1,0,1,0}},{'�',{1,1,1,1}},{'�',{0,1,2,1}},
   {'�',{0,2,1,2}},{'�',{0,2,2,0}},{'�',{0,0,2,2}},{'�',{2,2,2,0}},
   {'�',{2,0,2,2}},{'�',{0,2,2,2}},{'�',{2,0,2,0}},{'�',{2,2,2,2}},
   {'�',{2,1,2,0}},{'�',{1,2,1,0}},{'�',{2,0,2,1}},{'�',{1,0,1,2}},
   {'�',{0,2,1,0}},{'�',{0,1,2,0}},{'�',{0,0,2,1}},{'�',{0,0,1,2}},
   {'�',{1,2,1,2}},{'�',{2,1,2,1}},{'�',{1,1,0,0}},{'�',{0,0,1,1}},
   {' ',{0,0,0,0}},{0,{0,0,0,0}}
};

struct graphchar  *GraphSets[]=
{
   AlternativeCoding,
   KOI8Coding,
   KOI8_linux_Coding,
   DumbCoding,
   NULL
};
struct graphchar  *CurrGraphSet;
int               grsetno=0;

int   CharIndex(byte ch)
{
   int i;
   for(i=0; CurrGraphSet[i].ch && CurrGraphSet[i].ch!=ch; i++);
   return i;
}
int   DirIndex(int x,int y)
{
   return(x==0?y+2:x+1);
}
void  TurnXY(int *x,int *y)
{
   int x1=*y;
   *y=-*x;
   *x=x1;
}
byte  HowProlonged(byte ch,int x,int y)
{
   return(CurrGraphSet[CharIndex(ch)].prol[DirIndex(x,y)]);
}

int   IsProlonged(byte ch,int x,int y,byte how)
{
   int   dir=DirIndex(x,y);

   for(int i=0; CurrGraphSet[i].ch; i++)
      if(ch==CurrGraphSet[i].ch && how==CurrGraphSet[i].prol[dir])
         return(1);

   return(how==0);
}

void  Prolong(int x,int y,byte how)
{
   struct graphchar  need;
   int               best;
   int               bestdist;
   int               dist;
   int               i;
   int               j;

   need=CurrGraphSet[CharIndex(Char())];
   need.prol[DirIndex(x,y)]=how;

   for(i=1,TurnXY(&x,&y); i<4; i++,TurnXY(&x,&y))
      need.prol[DirIndex(x,y)]=HowProlonged(CharAtLC(GetLine()+y,GetCol()+x),-x,-y);

   best=-1;
   bestdist=30000;
   for(i=0; CurrGraphSet[i].ch; i++)
   {
      j=DirIndex(x,y);
      dist=16*abs(need.prol[j]-CurrGraphSet[i].prol[j]);
      j=(j+1)&3;
      dist+=4*abs(need.prol[j]-CurrGraphSet[i].prol[j]);
      j=(j+1)&3;
      dist+=abs(need.prol[j]-CurrGraphSet[i].prol[j]);
      j=(j+1)&3;
      dist+=4*abs(need.prol[j]-CurrGraphSet[i].prol[j]);

      if(dist<bestdist)
      {
         bestdist=dist;
         best=i;
      }
   }
   ReplaceChar(CurrGraphSet[best].ch);
}

void  Draw(int x,int y,byte how)
{
   if(IsProlonged(Char(),x,y,how))
   {
      if(GetCol()<-x || GetLine()<-y)
         return;
      Prolong(x,y,how);
      if(y)
         RedisplayLine();
      HardMove(GetLine()+y,GetCol()+x);
      Prolong(-x,-y,how);
   }
   else
      Prolong(x,y,how);
   RedisplayLine();
}

void    DrawFrames(void)
{
   extern
   char  **FramesHelp[];
   static
   int   curr_frame=1;
   int   action;
   char  sign[4];

   if(hex || View)
      return;

   CurrGraphSet=GraphSets[grsetno];

   do
   {
      LocateCursor();
      attrset(STATUS_LINE_ATTR->attr);
      sprintf(sign," $%d",curr_frame);
      mvaddstr(StatusLineY,COLS-4,sign);
      SetCursor();
      action=GetNextAction();
      switch(action)
      {
      case(EDITOR_HELP):
         Help(FramesHelp," Frame-Drawing Help ");
         break;
      case(CHAR_LEFT):
         Draw(-1,0,curr_frame);
         break;
      case(CHAR_RIGHT):
         Draw(1,0,curr_frame);
         break;
      case(LINE_UP):
         Draw(0,-1,curr_frame);
         break;
      case(LINE_DOWN):
         Draw(0,1,curr_frame);
         break;
      case(REFRESH_SCREEN):
         UserRefreshScreen();
         break;
      default:
         if(StringTypedLen!=1)
         {
            beep();
            break;
         }
         switch(StringTyped[0])
         {
         case('\t'):
            curr_frame=(curr_frame==2)?0:curr_frame+1;
            break;
         default:
            beep();
            return;
         }
      }
   }
   while(1);
}
