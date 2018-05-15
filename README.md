# Mesosphere Software Engineer Intern Challenge

## Elevator Control System

### Deployment

**CMake**

A CMakeLists.txt is provided for compilation and building.

**Usage**

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

A test case is given in main.cc, to access, after building with CMake:

```
$ cd build/src/
$ ./ElevatorControlSystem
```

### Unit Test

**Google Test**

Google Test is used as unit testing framework (Should be installed).

**Usage**

After building with CMake (I kept the build folder with submission which contains the test result excutable file)

```
$ cd build/test/
$ ./gtest
```

### Integration Test

**Travis CI**

A basic .travis.yml file is provided.

## Discussion

### Improvement on Interface

The origninal Interface is defined as:

```
trait ElevatorControlSystem {
  def status(): Seq[(Int, Int, Int)]
  def update(Int, Int, Int)
  def pickup(Int, Int)
  def step()
}
```

Since the goals could be more than one, the Status and Update functions are changed accordingly to show each Elevator's destinations and update accordingly. The Pickup function is also changed where I deleted the moving direction and added goal floor for each request, since the moving direction is easy to see when we have both pickup and goal. 

### Algorithm

In my implementation, the requests are stored in different sets, one for Up coming and one for Down going passengers. This is a mimic for real life scenario since obviously an Elevator can hold more than just one person, and thus the goal floors should be multiple. I chose the algorithm based on SCAN algorithm, which means the Elevator moves along single direction until reaching the top of building or the bottom, and then reverse its direction. This is much more efficient than FCFS implementation.

At first, the Simulation is initialized, the Elevators are created and stored in a vector, all with IDLE state. When assigning request to Elevators, I chose to utilize IDLE elevators first if possible, because this could help with balancing the loads. (We can also just focus on efficiency, but the following situation could possibly happen. Imagine if you are dealing with request with all perfect hitchhickers, who are perfectly picked up from your last destination and formed a loop or you simply reached the top of a really high building, and all following request are from relative high parts. Then this Elevator could be always running where the others are always idle.)

Then, if there is no IDLE Elevator, the expected picking up distances are calculated and compared between Elevators. The optimal is chosen to deal with the request.

The requests for each Elevator are stored in the UP and DOWN sets, which are arranged in order and have no duplicate destination, accoring to relation between goal and pickup floor.  In each step of Simulation, the destinations in the sets with same direction of Elevator is checked. (For instance, UP = [3, 5, 7, 8] and the Elevator is going up currently at 4th floor. Then the sublist [5, 7, 8] is checked in each step to decide whether to open door or not along the movement) If element in set is identical to current floor, this means one destination is arrived, then this element is erased, and Elevator stopped dropping or picking up passengers. 

One thing to be noticed is when dealing with border value, the top and bottom floors. When arriving, we need to check if it existd in both UP and DOWN sets.

### TODO

There exist serveral aspects that should be improved for this implementation.

1. Unit Test: Because of the time constraint, only partial basic functionalities are tested.
2. Algorithm improvement: I also considered to restrict the movement of Elevator within the existing highest and lowest destinations. But this could possibly lead to starvation problem and increase complexity.
3. Capacity of Elevator could be considered if we would like to simulate much more similar to real world.
4. Command line support

## Documentation

**Doxygen**

The commenting style adopts the Doxygen style comment blocks, which will allow an easier generation of the documentation file with Doxygen.

**Usage**

```
$ cd src/
$ doxygen doxygen_cofig
```

**To generate PDF**

```
$ cd src/latex/
$ make
```



## Author

**Zihan Qi** z.qi@jacobs-university.de



