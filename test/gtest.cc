#include <iostream>
#include <tuple>
#include <vector>
#include <set>

#include "gtest/gtest.h"
#include "./../src/Elevator.h"
#include "./../src/Simulation.h"

TEST(ElevatorControlSystem, ElevatorTest){
    Elevator elevator = Elevator(0, 10);

    std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>> status;
    status = std::make_tuple(0, 0, std::set<int>{}, std::set<int, std::greater<int>>{});
    EXPECT_EQ(elevator.GetStatus(), status);

    EXPECT_EQ(elevator.GetCurrentFloor(), 0);

    EXPECT_TRUE(elevator.IsIdle());
    EXPECT_FALSE(elevator.IsUp());
    EXPECT_FALSE(elevator.IsDown());

    elevator.SetState(static_cast<Elevator::State>(1));

    EXPECT_FALSE(elevator.IsIdle());
    EXPECT_TRUE(elevator.IsUp());
    EXPECT_FALSE(elevator.IsDown());
}

TEST(ElevatorControlSystem, SimulationTest){
    Simulation simulation = Simulation(3, 10);

    std::vector<std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>>> status;
    for(int i = 0; i < 3; ++i) {
        status.push_back(std::make_tuple(i, 0, std::set<int>{}, std::set<int, std::greater<int>>{}));
    }
    EXPECT_EQ(simulation.Status(), status);
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}