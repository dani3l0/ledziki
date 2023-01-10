class Button {
	int pin;
	bool state_prev = false;
	bool holdlock = false;
	long t = 0;
	public:
		int value;
		bool state = false;
		Button(int pino) {
			pin = pino;
			pinMode(pin, INPUT_PULLUP);
		}
		void update() {
			state = !digitalRead(pin);
			if (state) {
				if (t < 1000) {
					value = 0;
					t += timer.change;
				}
				else if (holdlock) value = 0;
				else {
					value = 2;
					holdlock = true;
				}
			}
			else {
				t = 0;
				if (state_prev && !holdlock) value = 1;
				else {
					value = 0;
					holdlock = false;
				}
			}
			state_prev = state;
		}
};

//// Button pin definition ////
Button l1_up(2);
Button l1_dn(3);
Button l2_up(6);
Button l2_dn(5);
Button bulber(4);
///////////////////////////////

void updatebtns() {
	l1_up.update();
	l1_dn.update();
	bulber.update();
	l2_up.update();
	l2_dn.update();
}
