#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Heating.h"

using namespace std;

int main() {
	srand(time(NULL));
	Heating test;
	test.RunSimulation();
	return 0;
}