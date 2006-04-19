/*
 * Copyright (c) 1993-1997 by Alexander V. Lukyanov (lav@yars.free.net)
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

/*
 * This code actually is VERY old and must be reorganized or deleted,
 * but I don't have time nor wish to do that
 */
#ifdef WITH_MODIFYKEY

#include <config.h>
#include <string.h>
#include <unistd.h>
#include "edit.h"

#ifndef  MSDOS
/************************** TABLES FOR D211 *****************************/
char  rl_d211[]={
'�','Q','�','W','�','E','�','R','�','T','�','Y','�','U','�','I',
'�','O','�','P','�','[','�',']','�','A','�','S','�','D','�','F',
'�','G','�','H','�','J','�','K','�','L','�','\\','�','Z','�','X',
'�','C','�','V','�','B','�','N','�','M','�','q','�','w','�','e',
'�','r','�','t','�','y','','u','�','i','�','o','','p','�','{',
'�','}','�','a','','s','�','d','�','f','�','g','�','h','�','j',
'�','k','�','l','�','|','�','z','�','x','�','c','�','v','�','b',
'�','n','�','m','�','`','�','~','�','@','�','$','�','^','�','%',
0};

/************************* TABLES FOR VTA2000 ************************/
char  rl_vta2000[]={
'�','@','�','A','�','B','�','C','�','D','�','E',
'�','F','�','G','�','H','�','I','�','J','�','K','�','L','�','M',
'�','N','�','O','�','P','�','Q','�','R','�','S','�','T','�','U',
'�','V','�','W','�','X','�','Y','�','Z','�','[','�','\\','�',']',
'�','_','�','`','�','a','�','b','�','c','�','d','�','e','�','f',
'�','g','�','h','�','i','�','j','�','k','�','l','�','m','�','n',
'�','o','','p','�','q','�','r','','s','�','t','','u','�','v',
'�','w','�','x','�','y','�','z','�','{','�','|','�','}','�','~',
0};

/************************* TABLES FOR DEFAULT ************************/
char  rl_default[]={
0};

/*************************** FUNCTIONS ****************************/

char  *table=        rl_default;
#else
char  rl_ibm[]={0};
char  *table=rl_ibm;
#endif

void  InitTables()
{
   init_chset();
#ifndef  MSDOS
   if(!strcmp(TERM,"vta2000"))
      table=rl_vta2000;
   else if(!strcmp(TERM,"d211"))
      table=rl_d211;
#endif
}

#endif // WITH_MODIFYKEY
