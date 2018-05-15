/**
 * \brief Simulation class
 * 
 * @file Simulation.h
 * \author Zihan Qi
 * \date 2018-05-15
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Elevator.h"

class Simulation {
    private:
        int elevator_number_;
        int story_number_;
        std::vector<Elevator> elevators_;

    public:
        /**
         * \brief Constructor for Simulation
         * 
         * \param elevator_number Number of Elevators in simulation
         * \param story_number Number of stories in the building
         */
        Simulation(int elevator_number, int story_number);

        /**
         * \brief Function which returns the status of Elevators in simulation
         * 
         * \return std::vector<std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>>> Vector of status of Elevators
         */
        std::vector<std::tuple<int, int, std::set<int>, std::set<int, std::greater<int>>>> Status();

        /**
         * \brief Function which updates information about an Elevator
         * 
         * \param elevator_id ID
         * \param current_floor Current floor
         * \param up_requests Requests for going up
         * \param down_requests Requests for going down
         */
        void Update(int elevator_id, int current_floor, std::set<int> up_requests, std::set<int, std::greater<int>> down_requests);

        /**
         * \brief Function which picks up passengers in simulation
         * 
         * \param pickup_floor Pickup floor
         * \param goal_floor Goal floor
         */
        void Pickup(int pickup_floor, int goal_floor);

        /**
         * \brief Function which performs one moving step for simulation system
         * 
         */
        void Step();
};

#endif // SIMULATION_H