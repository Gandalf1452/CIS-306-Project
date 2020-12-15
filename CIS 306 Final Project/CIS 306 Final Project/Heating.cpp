#include "Heating.h"
#include <cmath>

using namespace std;

Heating::Heating() {
	current_state = IDLE;
	target_temp = 70;
	current_temp = 70;
	idle_rate = 0.05;
	threshold = 2;
}

Heating::Heating(double target) {
	current_state = IDLE;
	target_temp = target;
	current_temp = 70;
	idle_rate = 0.05;
	threshold = 2;
}

Heating::Heating(double target, double start_temp) {
	current_state = IDLE;
	target_temp = target;
	current_temp = start_temp;
	idle_rate = 0.05;
	threshold = 2;
}

Heating::Heating(double target, double start_temp, double start_idle_rate) {
	current_state = IDLE;
	target_temp = target;
	current_temp = start_temp;
	idle_rate = start_idle_rate;
	threshold = 2;
}

state Heating::CheckState() {
	if ((current_temp - target_temp) > threshold) {
		current_state = COOLING;
	}
	else if ((current_temp - target_temp) < -threshold) {
		current_state = HEATING;
	}
	else if ((current_state == COOLING || current_state == HEATING) && (abs(current_temp - target_temp) <= 0.10)) {
		current_state = IDLE;
	}
}