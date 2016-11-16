/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| utils.h
|**********************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#define SSTR(X) 		dynamic_cast< std::ostringstream & >( \
        				( std::ostringstream() << std::dec << X ) ).str()

#define FOREACH(TYPE,ITEM,VECTOR)	for (std::vector<TYPE>::iterator ITEM = VECTOR.begin();\
                                    ITEM!=VECTOR.end(); ++ITEM)

#endif
