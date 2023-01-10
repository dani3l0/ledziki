				//	R, Or, Ye, Gn, Sky, Blu, Prp
#include "animations.h"

// Use HUE color palette
const int HUEs[] = {0, 15, 40, 96, 135, 160, 196};
const int HGs[][2] = {
	{160, 0},
	{160, 30},
	{96, 160},
	{135, 196},
	{196, 40},
	{0, 25},
};
const int colors = sizeof(HUEs) / sizeof(int);
const int gradients = sizeof(HGs) / sizeof(int) / 2;

class RGB_Strip {
	int ref = 0;
	const int B[4] = {0, 70, 140, 210};
    public:
	    int pixs, id;
		const int Bs = sizeof(B) / sizeof(int);
		int brightness = 0;
		int b = B[brightness];
		int mode = 0;
		const int modes = 3;
		Animations a;

		int current_color = 0;
		int current_gradient = 0;
		bool reverse_gradient = false;
		int animation_id = 0;
		const int animations = 5;

        void init(int _id, int _pixs) {
        	id = _id;
            pixs = _pixs;
        }
        void nextColor() {
        	if (mode == 0) current_color = range(current_color, colors);
        	else if (mode == 1) {
        		if (reverse_gradient) current_gradient = range(current_gradient, gradients);
        		reverse_gradient = !reverse_gradient;
        	}
        	else if (mode == 2) animation_id = range(animation_id, animations);
        }
        void nextMode() {
        	mode = range(mode, modes);
        	if (mode == 1 && pixs == 1) mode++;
        }
		void lightsUp() {
			brightness = range(brightness, Bs);
		}
        void update() {
            ref += timer.change;
            if (ref < 18) {
	            if (mode == 2) {
	            	if (animation_id == 0) a.rainbow(id, pixs, b);
	            	else if (animation_id == 1) a.rainbow2(id, pixs, b);
	            	else if (animation_id == 2) a.fire(id, pixs, b);
	            	else if (animation_id == 3) {
	            		if (pixs < 4) animation_id++;
	            		a.scanner(id, pixs, b, false);
	            	}
	            	else if (animation_id == 4) a.scanner(id, pixs, b, true);
	            }
	            return;
            }
            ref -= 10;
            b = alignValue(b, B[brightness]);
            if (mode == 0) {
            	for (int i = 0; i < pixs; i++) {
		            int _r = leds[id][i].r;
		            int _g = leds[id][i].g;
	            	int _b = leds[id][i].b;
            		leds[id][i] = CHSV(HUEs[current_color], 255, b);
		            leds[id][i].r = alignValue(_r, leds[id][i].r);
		            leds[id][i].g = alignValue(_g, leds[id][i].g);
		            leds[id][i].b = alignValue(_b, leds[id][i].b);
            	}
            }
            if (mode == 1) {
            	for (int i = 0; i < pixs; i++) {
            		int index = (!reverse_gradient) ? i : pixs - i - 1;
		            int _r = leds[id][index].r;
		            int _g = leds[id][index].g;
	            	int _b = leds[id][index].b;
           			int g1 = HGs[current_gradient][0];
           			int g2 = HGs[current_gradient][1];
           			uint8_t r = g2 - g1;
            		int a = i * r / (pixs - 1);
            		uint8_t h = g1 + a;
            		leds[id][index] = CHSV(h, 255, b);
		            leds[id][index].r = alignValue(_r, leds[id][index].r);
		            leds[id][index].g = alignValue(_g, leds[id][index].g);
		            leds[id][index].b = alignValue(_b, leds[id][index].b);
            	}
            }
        }
};
RGB_Strip* RGBs = new RGB_Strip[LED_STRIPS];
