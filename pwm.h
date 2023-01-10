class PWM {
	public:
		const int B[4] = {0, 50, 128, 255};
		const int Bs = sizeof(B) / sizeof(int) - 1;
		int target = 0;
		int brightness = 0;
		int value = 0;
		int pin;
		long change;
		PWM(int _pin) {
			pin = _pin;
			pinMode(pin, OUTPUT);
            analogWrite(pin, 0);
		}
		void set(int amount) {
			brightness += amount;
			if (brightness > Bs) brightness = 0;
			else if (brightness < 0) brightness = Bs;
		}
		void update() {
            change += timer.change;
            if (change < 10) return;
            change -= 10;
            target = B[brightness];
            value = alignValue(value, target);
            analogWrite(pin, value);
		}
};
