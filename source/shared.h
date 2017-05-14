//3DS and lib includes
#include <3ds.h>

//Standard libs
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <sstream>

//Net stuff
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

//Ogg format things
#include <ivorbiscodec.h>
#include <ivorbisfile.h>

extern void displayError(const char * error);
extern bool romfsEnabled;
extern float delta;
extern char * flaskVersion;
//bool channelList[24];

//Util
#include "include/util.h"
#include "include/http.h"

//Class includes
#include "include/flask.h"