/**
 * \brief Implementation of Elevator class
 * 
 * @file Elevator.cc
 * \author Zihan Qi
 * \date 2018-05-15
 */

#include "Elevator.h"
#include <tuple>
#include <vector>
#include <set>

Elevator::Elevator(int elevator_id, int story_number) {
    elevator_id_ = elevator_id;
    story_number_ = story_number;
    state_ = kIdle;
    current_floor_ = 0;
}

std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>> Elevator::GetStatus() {
    return std::make_tuple(elevator_id_, current_floor_, up_requests_, down_requests_);
}

void Elevator::SetPickupGoal(int pickup_floor, int goal_floor) {
    if(IsIdle()) {
        if(pickup_floor < goal_floor) {
            // if coming request is a hitchhiker, set state to UP. Otherwise, set to DOWN.
            if(GetCurrentFloor() <= pickup_floor) {
                SetState(kUp);
            }
            else {
                SetState(kDown);
            }
            // Insert both pickup floor and goal floor to requests sets, since we also need to stop to pickup
            up_requests_.insert(pickup_floor);
            up_requests_.insert(goal_floor);
        }
        else if(pickup_floor > goal_floor) {
            if(GetCurrentFloor() >= pickup_floor) {
                SetState(kDown);
            }
            else {
                SetState(kUp);
            }
            down_requests_.insert(pickup_floor);
            down_requests_.insert(goal_floor);
        }
        else {
            SetState(kIdle);
        }
    }
    else if(IsUp()) {
        up_requests_.insert(pickup_floor);
        up_requests_.insert(goal_floor);
    }
    else if(IsDown()) {
        down_requests_.insert(pickup_floor);
        down_requests_.insert(goal_floor);
    }
    else {
        throw std::invalid_argument("Invalid State");
    }
}

void Elevator::SetCurrentGoal(int current_floor, std::set<int> up_requests, std::set<int, std::greater<int>> down_requests) {
    current_floor_ = current_floor;
    up_requests_ = up_requests;
    down_requests_ = down_requests;
}

bool Elevator::IsIdle() {
    return state_ == kIdle;
}

bool Elevator::IsUp() {
    return state_ == kUp;
}

bool Elevator::IsDown() {
    return state_ == kDown;
}

int Elevator::GetCurrentFloor() {
    return current_floor_;
}

void Elevator::SetState(State state) {
    //state_ = static_cast<State>(state);
    state_ = state;
}

void Elevator::Move() {
    std::cout << "ID: " << elevator_id_ << "    Current: " << current_floor_;
    if(state_ == kUp) std::cout << "    State: UP" << std::endl;
    else if(state_ == kDown) std::cout << "    State: DOWN" << std::endl;
    else std::cout << "    State: IDLE" << std::endl;

    if(state_ == kUp) {
        // Coming request is a hitchhicker
        if(current_floor_ < story_number_ - 1) {
            auto it = up_requests_.find(current_floor_);
            if(it != up_requests_.end()) {
                // Picking up or droping passengers all require stopping
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *it << std::endl;
                up_requests_.erase(it);
            }
            // Guarded to ensure the floor will not change when the requests sets are empty
            if(!(up_requests_.empty() && down_requests_.empty()))
                current_floor_++;
        }
        // Border situation for UP
        else {
            auto itup = up_requests_.find(current_floor_);
            if(itup != up_requests_.end()) {
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *itup << std::endl;
                up_requests_.erase(itup);
            }
            SetState(kDown);
            auto itdown = down_requests_.find(current_floor_);
            if(itdown != down_requests_.end()) {
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *itdown << std::endl;
                down_requests_.erase(itdown);
            }
            if(!(up_requests_.empty() && down_requests_.empty()))
                current_floor_--;
        }
    }
    else if(state_ == kDown) {
        if(current_floor_ > 0) {
            auto it = down_requests_.find(current_floor_);
            if(it != down_requests_.end()) {
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *it << std::endl;
                down_requests_.erase(it);
            }
            if(!(up_requests_.empty() && down_requests_.empty()))
                current_floor_--;
        }
        else {
            auto itdown = down_requests_.find(current_floor_);
            if(itdown != down_requests_.end()) {
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *itdown << std::endl;
                down_requests_.erase(itdown);
            }
            SetState(kUp);
            auto itup = up_requests_.find(current_floor_);
            if(itup != up_requests_.end()) {
                std::cout << "ID: " << elevator_id_ << "    Stop at: " << *itup << std::endl;
                up_requests_.erase(itup);
            }
            if(!(up_requests_.empty() && down_requests_.empty()))
                current_floor_++;
        }
    }
    // If there are no requests, set Evelator to IDLE
    if(up_requests_.empty() && down_requests_.empty()) {
        SetState(kIdle);
    }
}