#pragma once

enum state { IDLE, HEATING, COOLING };

class Heating
{
private:
	state current_state;
	double target_temp;
	double current_temp;
	double idle_rate;
	int threshold;
public:
	Heating();
	Heating(double);
	Heating(double, double);
	Heating(double, double, double);
	state CheckState();
	double UpdateIdleRate();
	void StateHeating();
	void StateIdle();
	void StateCooling();
	void RunSimulation();
};

