#include "Heating.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

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

void Heating::CheckState() {
	if ((current_temp - target_temp) > threshold) {
		current_state = COOLING;
	}
	else if ((current_temp - target_temp) < -threshold) {
		current_state = HEATING;
	}
	else if ((current_state == COOLING || current_state == HEATING) && (abs(current_temp - target_temp) <= 1.0)) {
		current_state = IDLE;
	}
}

double Heating::UpdateIdleRate() {
	idle_rate = ((float)rand() / RAND_MAX);
	if (((float)rand() / RAND_MAX) > 0.5) { // 50% chance idle rate is negative
		idle_rate = -idle_rate;
	}
	return idle_rate;
}

void Heating::StateCooling() {
	while (current_state == COOLING) {
		current_temp -= ((float)rand() / RAND_MAX);
		cout << "Current Temp: " << setprecision(4) << current_temp << " Degrees F" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		CheckState();
	}
}

void Heating::StateHeating() {
	while (current_state == HEATING) {
		current_temp += ((float)rand() / RAND_MAX);
		cout << "Current Temp: " << setprecision(4) << current_temp << " Degrees F" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		CheckState();
	}
}

void Heating::StateIdle() {
	while (current_state == IDLE) {
		current_temp += idle_rate;
		cout << "Current Temp: " << setprecision(4) << current_temp << " Degrees F" << endl;
		idle_rate = UpdateIdleRate();
		this_thread::sleep_for(chrono::seconds(1));
		CheckState();
	}
}

void Heating::RunSimulation() {
	cout << "SIMULATION STARTED" << endl;
	int i = 0;
	while (i < 10) {
		if (current_state == HEATING) {
			cout << "Current state changed to: HEATING" << endl;
			StateHeating();
		}
		else if (current_state == COOLING) {
			cout << "Current state changed to: COOLING" << endl;
			StateCooling();
		}
		else {
			cout << "Current state changed to: IDLE" << endl;
			StateIdle();
		}
		++i;
	}
	cout << "ENDING SIMULATION" << endl;
}