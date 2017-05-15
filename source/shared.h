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
#include <sstream>
#include <fstream>
#include <iostream>

//Other libs
#include "starlight/_incLib/json.hpp"
#include "starlight/ui/Image.h"
#include "starlight/ui/Button.h"
#include "starlight/ui/Form.h"
#include "starlight/ui/Label.h"

using std::string;
using std::ifstream;
using std::iostream;

using starlight::ui::Image;
using starlight::ui::Button;
using starlight::ui::Form;
using starlight::ui::Label;

using nlohmann::json;

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
extern bool channelList[24];

//Util
#include "include/util.h"
#include "include/http.h"

//Class includes
#include "include/oggvorbis.h"
#include "include/homebrew.h"
#include "include/flask.h"