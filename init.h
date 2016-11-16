/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| init.h
|**********************************************************************/

#ifndef __INIT_H__
#define __INIT_H__

//=======================================================
// Macros
//=======================================================

#define LOOP14 	int loop[14];\
for (loop[0]=0; loop[0]<2; loop[0]++) for (loop[1]=0; loop[1]<2; loop[1]++) for (loop[2]=0; loop[2]<2; loop[2]++)\
for (loop[3]=0; loop[3]<2; loop[3]++) for (loop[4]=0; loop[4]<2; loop[4]++) for (loop[5]=0; loop[5]<2; loop[5]++)\
for (loop[6]=0; loop[6]<2; loop[6]++) for (loop[7]=0; loop[7]<2; loop[7]++) for (loop[8]=0; loop[8]<2; loop[8]++)\
for (loop[9]=0; loop[9]<2; loop[9]++) for (loop[10]=0; loop[10]<2; loop[10]++) for (loop[11]=0; loop[11]<2; loop[11]++)\
for (loop[12]=0; loop[12]<2; loop[12]++) for (loop[13]=0; loop[13]<2; loop[13]++)

#define LOOP3 int loop[3];\
for (loop[0]=0; loop[0]<2; loop[0]++) for (loop[1]=0; loop[1]<2; loop[1]++) for (loop[2]=0; loop[2]<2; loop[2]++)

#define LOOP4 int loop[4];\
for (loop[0]=0; loop[0]<2; loop[0]++) for (loop[1]=0; loop[1]<2; loop[1]++) for (loop[2]=0; loop[2]<2; loop[2]++)\
for (loop[3]=0; loop[3]<2; loop[3]++)

#define RESET_POS sh = pos; go = true;

//=======================================================
// Prototype
//=======================================================

class Init
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		static void all();
		static void squareDistance();
		static void zobristKeys();
		static void rookSlides();
		static void bishopSlides();
		static void pawnSlides();
};

#endif
