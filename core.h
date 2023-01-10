class Timer {
	public:
		int current = 0;
		int previous = 0;
		int change = 0;
		void update() {
			previous = current;
			current = millis();
			if (previous <= current) change = current - previous;
			else change = 65536 - previous + current;
		}
};
Timer timer;

int alignValue(int val, int target) {
	if (val > target) val--;
	else if (val < target) val++;
	return val;
}
int alignValueDown(int val, int target, int amount) {
	val -= amount;
	if (val < target) return target;
	return val;
}

int range(int val, int maximum) {
	val++;
	if (val >= maximum) return 0;
	return val;
}
