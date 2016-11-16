#**********************************************************************
#
# Bogart
# Chess Engine
#
# Copyright (C) 2009-2013 Dr.Kameleon
#
#**********************************************************************
# Makefile
#**********************************************************************

#=======================================================
# Definitions
#=======================================================

APP 		= bogart

# Tools & commands
CLANG = clang++
CPP	  = g++
RM    = rm
CLOC  = tools/cloc-1.51.pl

# C++ stuff
SOURCES 	= main.cpp\
			  cmdline.cpp\
			  init.cpp\
			  bitboard.cpp\
			  timer.cpp\
			  log.cpp\
			  board.cpp\
			  board_helper.cpp\
			  board_gen.cpp\
			  board_eval.cpp\
			  board_search.cpp\
			  engine.cpp\
			  benchmark.cpp

OBJECTS    	= main.o\
			  cmdline.o\
			  init.o\
			  bitboard.o\
			  timer.o\
			  log.o\
			  board.o\
			  board_helper.o\
			  board_gen.o\
			  board_eval.o\
			  board_search.o\
			  engine.o\
			  benchmark.o

# Flags
CLANG_FLAGS	= -I /usr/local/include/boost -lboost_program_options
CLOC_FLAGS	= --exclude-lang=Perl

#=======================================================
# Functions
#=======================================================

all: ${APP}

${APP}: ${OBJECTS}
	${CLANG} ${OBJECTS} -flto -o ${APP} ${CLANG_FLAGS}

${OBJECTS}: ${SOURCES}
	${CLANG} -O4 -c ${SOURCES}

count:
	./${CLOC} . ${CLOC_FLAGS}

clean:
	${RM} *.o

cleanall:
	${RM} *.o ${APP}

#=======================================================
# Finita la musica, passata la fiesta...
#=======================================================
