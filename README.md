# C---Bitboard-Chess-Engine
This is a work-in-progress C++ Bitboard Chess Engine

PLEASE FEEL FREE TO LEAVE ANY COMMENTS OR SUGGESTIONS!

This is an extremely simple chess engine that as of right now compiles fine with the latest version of Orwell Dev-C++
To compile, just start a new project and add all the .cpp files to it. Do not add the "magicmoves.c" to the project. You must build the tinythreads library for the engine's support fo threading; the engine will not compile without the .a file library. When it is built with a 32-bit compiler, place it in the main source directory and the engine should build perfectly. There is a makefile if anyone wants to compile it from the command line(I sometimes do). At any rate, I will try to keep support for the command line users with the makefile. By the way, you must use a 32-bit compiler  to compile from the command line. Sorry for the 64-bit users! If you do not know how to compile, I have compiled an .exe. Just go to the release section of this repository. I only do a release when I get a major amount of progress done, so you may have to wait a while for the next release!
The whole goal of my program is clarity and simplicity. I want to teach beginners at chess programming and at chess how to do both. We were all beginner programmers once. I struggled with the concept of bitboards for a long time and this is my contribution to those who don't understand them.
Feel absolutely free to make a pull request and make a comment. That's what programming is all about!

Thank you! 
