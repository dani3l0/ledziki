void fadeBlack(int id, int pixs, int amount) {
	for (int i = 0; i < pixs; i++) {
		leds[id][i].r = alignValueDown(leds[id][i].r, 0, amount);
		leds[id][i].g = alignValueDown(leds[id][i].g, 0, amount);
		leds[id][i].b = alignValueDown(leds[id][i].b, 0, amount);
	}
}

class Animations {
public:
	uint8_t RAINBOW_HUE = 0;
	int rainbow_timer = 0;
	void rainbow(int id, int pixs, int b) {
		rainbow_timer += timer.change;
		if (rainbow_timer >= 12) {
			RAINBOW_HUE++;
			rainbow_timer -= 12;
		}
		for (int i = 0; i < pixs; i++) {
			int toadd = i * 6;
			uint8_t h = RAINBOW_HUE + toadd;
			leds[id][i] = CHSV(h, 255, b);
		}
	}
	
	uint8_t RAINBOW2_HUE = 0;
	int rainbow2_timer = 0;
	void rainbow2(int id, int pixs, int b) {
		rainbow2_timer += timer.change;
		if (rainbow2_timer >= 60) {
			RAINBOW2_HUE++;
			rainbow2_timer -= 60;
		}
		for (int i = 0; i < pixs; i++) {
			int toadd = i * 4;
			uint8_t h = RAINBOW2_HUE + toadd;
			leds[id][i] = CHSV(h, 255, b);
		}
	}
	
	int a_fire_inkrement = 0;
	int a_fire_timer = 0;
	int a_fire_timer2 = 0;
	void fire(int id, int pixs, int b) {
		a_fire_timer += timer.change;
		a_fire_timer2 += timer.change;
		if (a_fire_timer >= 30) {
			a_fire_timer -= 30;
			if (b > 200) fadeBlack(id, pixs, 2);
			if (b > 100) fadeBlack(id, pixs, 2);
			a_fire_inkrement = range(a_fire_inkrement, 4);
			if (!a_fire_inkrement) fadeBlack(id, pixs, 1);
		}
		if (a_fire_timer2 < 4) return;
		a_fire_timer2 -= 4;
		float multiplier = (float) b / 255.0;
		bool spark = random8() > 220;
		if (spark) {
			int middle = ceil(pixs / 2);
			for (int i = middle; i >= 0; i--) {
				int h = map(i, middle, 0, 10, 40);
				leds[id][middle + i] = CHSV(h, 255, b);
				leds[id][middle - i] = CHSV(h, 255, b);
			}
		}
	}
	
	uint8_t SCANNER_HUE = 0;
	int SCANNER_INDEX = 0;
	int SCANNER_FNC = 1;
	int a_scanner_timer = 0;
	int a_scanner_timer2 = 0;
	void scanner(int id, int pixs, int b, bool pause) {
		a_scanner_timer += timer.change;
		a_scanner_timer2 += timer.change;
		if (a_scanner_timer2 >= 20) {
			a_scanner_timer2 -= 20;
			if (b > 200) fadeBlack(id, pixs, 1);
			if (b > 100) fadeBlack(id, pixs, 3);
			fadeBlack(id, pixs, 1);
		}
		if (a_scanner_timer >= 35) {
			a_scanner_timer -= 35;
			SCANNER_HUE++;
			SCANNER_INDEX += SCANNER_FNC;
			if (SCANNER_INDEX < 0) {
				SCANNER_FNC = 1;
				a_scanner_timer -= 1000 * pause;
			}
			else if (SCANNER_INDEX >= pixs - 1) {
				SCANNER_FNC = -1;
				a_scanner_timer -= 1000 * pause;
			}
			leds[id][SCANNER_INDEX] = CHSV(SCANNER_HUE, 255, b);
		}
	}
};
