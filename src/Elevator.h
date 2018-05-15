/**
 * \brief Elevator class
 * 
 * @file Elevator.h
 * \author Zihan Qi
 * \date 2018-05-15
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <tuple>
#include <vector>
#include <set>

class Elevator {
    private:
        int elevator_id_;
        int current_floor_;
        int story_number_;
        int state_;
        std::set<int> up_requests_;
        std::set<int, std::greater<int>> down_requests_;
  
    public:
        enum State {
            kUp = 1,
            kDown = -1,
            kIdle = 0,
        };

        /**
         * \brief Constructor for Elevator
         * 
         * \param elevator_id ID of an Elevator
         * \param story_number Number of stories in the building
         */
        Elevator(int elevator_id, int story_number);

        /**
         * \brief Getting function which returns the status of an Elevator
         * 
         * \return std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>> Status of an Elevator in a tuple: <ID, current floor, up requests, down requests>
         */
        std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>> GetStatus();

        /**
         * \brief Function which inserts pickup floor and goal floor into requests sets
         * 
         * \param pickup_floor pickup floor to be inserted
         * \param goal_floor goal floor to be inserted
         */
        void SetPickupGoal(int pickup_floor, int goal_floor);

        /**
         * \brief Setting function which sets the current floor and requests for an Elevator
         * 
         * \param current_floor Current floor
         * \param up_requests Requests for going up
         * \param down_requests Requests for going down
         */
        void SetCurrentGoal(int current_floor, std::set<int> up_requests, std::set<int, std::greater<int>> down_requests);

        /**
         * \brief Boolean function which check if an Elevator is idle
         * 
         * \return true Elevator is idle
         * \return false Elevator is not idle
         */
        bool IsIdle();

        /**
         * \brief Boolean function which check if an Elevator is going up
         * 
         * \return true Elevator goes up
         * \return false Elevator doesn't go up
         */
        bool IsUp();

        /**
         * \brief Boolean function which check if an Elevator is going down
         * 
         * \return true Elevator goes down
         * \return false Elevator doesn't go down
         */
        bool IsDown();

        /**
         * \brief Getting function which returns the current floor
         * 
         * \return int Current floor
         */
        int GetCurrentFloor();

        /**
         * \brief Setting function which sets the state of an Elevator
         * 
         * \param state State of an Elevator
         */
        void SetState(State state);

        /**
         * \brief Function which perform one step for all Elevators in simulation
         * 
         */
        void Move();
};

#endif // ELEVATOR_H