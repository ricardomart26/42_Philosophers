# 42 Philosophers Overview #

42 Philosophers is a project that simulates the dining philosophers problem using multithreading. The dining philosophers problem is a classic problem in computer science, where a group of philosophers sit around a table and alternate between thinking and eating. However, there are only a limited number of forks, and philosophers can only eat when they have two forks. This creates a deadlock scenario where philosophers can starve if not managed properly.

The goal of this project is to implement a simulation of the dining philosophers problem using multithreading and synchronization techniques to avoid deadlock and starvation.

## How to Use ##

To use this project, simply clone this repository and navigate to the root directory. From there, you can compile the program by running make.

Once compiled, you can run the program with the following command:

```bash

./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_times_each_philo_must_eat]
```

Where num_philosophers is the number of philosophers at the table, time_to_die is the time in milliseconds after which a philosopher dies if they have not eaten, time_to_eat is the time in milliseconds it takes for a philosopher to eat, time_to_sleep is the time in milliseconds it takes for a philosopher to sleep, and num_times_each_philo_must_eat (optional) is the number of times each philosopher must eat before the simulation ends.

For example, to run a simulation with 5 philosophers who each must eat 7 times before the simulation ends, with a time to die of 800 milliseconds, a time to eat of 200 milliseconds, and a time to sleep of 300 milliseconds, you would run the following command:

```bash

./philo 5 800 200 300 7
```

If you're interested in learning more about the dining philosophers problem, or multithreading and synchronization techniques in general, here are a few resources you might find helpful:

    The Dining Philosophers Problem on Wikipedia
    Synchronization in Operating Systems on GeeksforGeeks
    Multithreading and Concurrency - A Beginner's Guide on Section.io