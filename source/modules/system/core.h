#pragma once

#include "shared.h"
#include "objects/flask.h"

extern char BUTTONS[32][32];

extern touchPosition touch;
extern bool touchDown;
extern int lastTouch[2];
extern bool channelList[24];


extern float deltaStep();
extern void scanInput(Flask * flask);
extern void keyIsDown(std::string key);