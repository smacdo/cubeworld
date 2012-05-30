#ifndef SCOTT_CUBEWORLD_APPLICATION_H
#define SCOTT_CUBEWORLD_APPLICATION_H

#include <string>

#define raiseError(x) appExit((x),__FILE__,__FUNCTION__,__LINE__)

void runGame();
void doGameTick( float delta, float gameTime );

void appExit( const std::string& message,
	          const char * file,
			  const char * func,
			  size_t line );

void appExit( const char * message,
              const char * file,
              const char * func,
              size_t line );

#endif
