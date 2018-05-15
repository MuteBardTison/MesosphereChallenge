/**
 * \brief Implementation of Simulation class
 * 
 * @file Simulation.cc
 * \author Zihan Qi
 * \date 2018-05-15
 */

#include "Simulation.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "Elevator.h"

const int kMaxElevatorNumber = 16;

Simulation::Simulation(int elevator_number, int story_number) {
    if(elevator_number < 1 || elevator_number > kMaxElevatorNumber) {
        throw std::invalid_argument("Number of elevators should be in range 1 - 16");
    }
    else {
        elevator_number_ = elevator_number;
        story_number_ = story_number;
        for(int i = 0; i < elevator_number; i++) {
            elevators_.emplace_back(i, story_number);
        }
    }
}

std::vector<std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>>> Simulation::Status() {
    std::vector<std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>>> status;
    for(auto elevator : elevators_) {
        status.push_back(elevator.GetStatus());
    }
    return status;
}

void Simulation::Update(int elevator_id, int current_floor, std::set<int> up_requests, std::set<int, std::greater<int>> down_requests) {
    if(elevator_id < 0 || elevator_id >= elevators_.size()) {
        throw std::invalid_argument("Invalid elevator id");
    }
    else if(current_floor < 0 || current_floor >= story_number_) {
        throw std::invalid_argument("Invalid current floor number");
    }
    else {
        elevators_.at(elevator_id).SetCurrentGoal(current_floor, up_requests, down_requests);
    }
}

void Simulation::Pickup(int pickup_floor, int goal_floor) {
    int floor_distance = 0, closest_elevator = story_number_ + 1, picked_elevator = -1, index = 0;

    if(pickup_floor < 0 || pickup_floor >= story_number_) {
        throw std::invalid_argument("Invalid pickup floor number");
    }
    else if(goal_floor < 0 || goal_floor >= story_number_) {
        throw std::invalid_argument("Invalid goal floor number");
    }
    else {
        // Calculate the minimal distance an Elevator needs to travel to pick up
        for(auto& elevator : elevators_) {
            if(pickup_floor < goal_floor) {
                if(elevator.IsUp()) {
                    if(elevator.GetCurrentFloor() <= pickup_floor) {
                        floor_distance = abs(elevator.GetCurrentFloor() - pickup_floor);
                    }
                    else {
                        floor_distance = abs((story_number_ - 1) - elevator.GetCurrentFloor() + story_number_ + pickup_floor);
                    }
                }
                else if(elevator.IsDown()) {
                    floor_distance = abs(elevator.GetCurrentFloor() + pickup_floor);
                }
                else {
                    elevators_.at(index).SetPickupGoal(pickup_floor, goal_floor);
                    return;
                }
            }
            else if(pickup_floor > goal_floor) {
                if(elevator.IsDown()) {
                    if(elevator.GetCurrentFloor() >= pickup_floor) {
                        floor_distance = abs(elevator.GetCurrentFloor() - pickup_floor);
                    }
                    else {
                        floor_distance = abs((story_number_ - 1) - pickup_floor + story_number_ + elevator.GetCurrentFloor());
                    }
                }
                else if(elevator.IsUp()) {
                    floor_distance = abs((story_number_ - 1) - elevator.GetCurrentFloor() + (story_number_ - 1) - pickup_floor);
                }
                else {
                    elevators_.at(index).SetPickupGoal(pickup_floor, goal_floor);
                    return;
                }
            }
            else {
                if(elevator.IsUp()) {
                    if(elevator.GetCurrentFloor() <= pickup_floor) {
                        floor_distance = abs(elevator.GetCurrentFloor() - pickup_floor);
                    }
                    else {
                        floor_distance = abs((story_number_ - 1) - elevator.GetCurrentFloor() + story_number_ + pickup_floor);
                    }
                }
                else if(elevator.IsDown()) {
                    if(elevator.GetCurrentFloor() >= pickup_floor) {
                        floor_distance = abs(elevator.GetCurrentFloor() - pickup_floor);
                    }
                    else {
                        floor_distance = abs((story_number_ - 1) - pickup_floor + story_number_ + elevator.GetCurrentFloor());
                    }
                }
                else {
                    elevators_.at(index).SetPickupGoal(pickup_floor, goal_floor);
                    return;
                }
            }

            if(floor_distance < closest_elevator) {
                closest_elevator = floor_distance;
                picked_elevator = index;
            }
            index++;
        }
        elevators_.at(picked_elevator).SetPickupGoal(pickup_floor, goal_floor);
    }
}

void Simulation::Step() {
    for(auto& elevator : elevators_) {
        elevator.Move();
    }
    std::cout << std::endl;
}