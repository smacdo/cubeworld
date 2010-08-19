#ifndef SCOTT_ROGUELIKE_GAMEAPP_H
#define SCOTT_ROGUELIKE_GAMEAPP_H

#define raiseError(x) appExit((x),__FILE__,__func__,__LINE__)

void runGame();
void doGameTick( float delta, float gameTime );

void appExit( const char * message,
              const char * file,
              const char * func,
              int line );

#endif
