#pragma once

#include <3ds.h>
#include <citro3d.h>

#include <lodepng.h>

#include <ivorbiscodec.h>
#include <ivorbisfile.h>

#include <json.hpp>

#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <malloc.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

#include "objects/console.h"
#include "types.h"

#define CONFIG_3D_SLIDERSTATE (*(volatile float *)0x1FF81080)

extern love::Console * console;
extern bool QUIT_APP;

extern bool screenEnable[1];
extern volatile bool updateAudioThread;

extern gfxScreen_t currentScreen;
extern gfxScreen_t renderScreen;
extern gfx3dSide_t currentSide;
extern GPU_TEXTURE_FILTER_PARAM minFilter;
extern GPU_TEXTURE_FILTER_PARAM magFilter;

extern touchPosition touch;
extern bool touchDown;
extern int lastTouch[2];
extern bool channelList[24];