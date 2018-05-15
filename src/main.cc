#include "Simulation.h"
#include "Elevator.h"

int main(int argc, char* argv[]) {
    Simulation s(3, 5);
    s.Pickup(2, 4);
    s.Pickup(1,2);
    s.Pickup(4,1);
    s.Step();
    s.Pickup(2,3);
    s.Step();
    s.Step();
    s.Pickup(1, 4);
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    s.Step();
    return 0;
}