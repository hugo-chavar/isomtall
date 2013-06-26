#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define LOGFILE "../game.log"
#define CONFIGFILE_DIRECTORY "../Configuration/"
#define CONNECTION_DIRECTORY "../Connection/"
#define CONFIGFILE_EXTENSION ".yaml"
#define DEFAULT_SERVER_PORT 9443
#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_VISION_RANGE 5
#define MAX_VISION_RANGE 50

#define IMAGES_EXTENSION ".png"
#define IMAGES_DIR "../Images/"
#define DEFAULT_TILE_IMAGE "../Images/pisoPasto0.png"
#define ERROR_IMAGE "../Images/error.png"
#define DEFAULT_ANIMATED_DIR "../Images/default/"
#define ERROR_ANIMATED_DIR "../Images/error/"
#define NUMBER_OF_IMAGE_DIRECTORIES_MAIN_CHARACTER 16

#define DEFAULT_SCREEN_WIDTH 800
#define MIN_SCREEN_WIDTH 200
#define DEFAULT_SCREEN_HEIGHT 600
#define MIN_SCREEN_HEIGHT 200
#define DEFAULT_SCROLL_MARGIN 100
#define MIN_SCROLL_MARGIN 10
#define MAX_SCROLL_MARGIN 200
#define DEFAULT_SCROLL_SPEED 100
#define DEFAULT_VIDEO_BPP 32

#define DEFAULT_MAIN_CHARACTER_SPEED 2
#define MAX_MAIN_CHARACTER_SPEED 3
#define MIN_MAIN_CHARACTER_SPEED 0.05
#define DEFAULT_MAIN_CHARACTER_X 5
#define DEFAULT_MAIN_CHARACTER_Y 5
#define DEFAULT_CHARACTER_MIN_PRECISION 0.5
#define DEFAULT_CHARACTER_MAX_DAMAGE 20.0
#define DEFAULT_CHARACTER_MAX_LIFE 200.0
#define DEFAULT_CHARACTER_MAX_MAGIC 100.0
#define DEFAULT_ITEMS_PERCENTAGE 0

#define DEFAULT_BASE_WIDTH 1
#define DEFAULT_BASE_HEIGHT 1
#define DEFAULT_TILE_WIDTH 64
#define DEFAULT_TILE_HEIGHT 32
#define DEFAULT_ENTITY_OBJECT_PIXEL_REF_X 32
#define DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y 0
#define ERROR_IMAGE_PIXEL_REF_X 24
#define ERROR_IMAGE_PIXEL_REF_Y 24
#define DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X 32
#define DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y 32
#define ERROR_ANIMATED_PIXEL_REF_X 24
#define ERROR_ANIMATED_PIXEL_REF_Y 24
#define DEFAULT_FPS 10
#define DEFAULT_DELAY 0

#define DEFAULT_STAGE_SIZE_X 100
#define DEFAULT_STAGE_SIZE_Y 100
#define MAX_STAGE_SIZE_X 1024 //para manejar la vision del personaje necesito un limite

#define DEFAULT_FONT_PATH "../Fonts/Arial.ttf"

#define DEFAULT_NOTIFICATIONBOX_PATH "../Connection/notificationBox.png"
#define DEFAULT_BUTTON_PATH "../Connection/button.png"
#define DEFAULT_MENU_PATH "../Connection/startScreen.png"

#endif