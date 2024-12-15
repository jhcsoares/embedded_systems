#ifndef IMAGES_H
#define IMAGES_H
#include <stdint.h>

#define HISTOGRAM_SIZE 256

#define WIDTH0 4
#define HEIGHT0 3
extern const uint8_t image0[HEIGHT0][WIDTH0]; 	

#define WIDTH1  160
#define HEIGHT1 120
extern const uint8_t image1[HEIGHT1][WIDTH1];
extern const uint8_t * const p_start_image1;
	
#endif
