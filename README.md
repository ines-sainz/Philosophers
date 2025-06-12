# 🧠 Philosophers

Philosophers is a project that simulates the classical Dining Philosophers Problem, a well-known exercise in concurrent programming and process synchronization.
The goal is to create a simulation where several philosophers alternate between thinking, eating, and sleeping, while competing for shared resources (forks) placed between them.

It helps with the fundamentals of thread, concurrent programming, resource managment and process management, including the usage of mutexes in C.
This project helps you understand how to manage threads and mutexes to avoid common issues in concurrent environments such as deadlocks and race conditions.

---

## 🛠️ What You'll Learn

* How to create and manage threads **(pthread)** 🧵
* How to synchronize access to shared memory using mutexes 🔒
* How to prevent race conditions, deadlocks, and ensure data integrity 🧩
* How to manage timing and logs precisely in a concurrent environment ⏱️

---

## 🍝 The Simulation

* A number of philosophers sit around a table.
* There are as many forks as philosophers.
* Each philosopher alternates between thinking, eating, and sleeping.
* To eat, a philosopher needs two forks, one on the left and one on the right.
* Forks are shared resources, and their access must be protected.
* If only one philosopher is present, they will never be able to eat and eventually die.
* If a philosopher doesn't eat within a certain time (`time_to_die`), they die and the simulation ends.
* The simulation also supports an optional condition where it ends once each philosopher has eaten a certain number of times (optional argument).
* The death notifications should not have a delay.

---

## 🧵 Threads

A thread is a lightweight unit of execution within a process.
Threads share the same memory space, which makes them ideal for situations where multiple tasks (like our philosophers) need to access shared data (forks) efficiently.
In this project:

* Each philosopher is implemented as a separate thread `pthread`.
* Threads run in parallel, simulating independent philosophers.
* Mutexes are used to control access to forks to avoid two philosophers taking the same fork at the same time.

By using threads, we can simulate real-life concurrency where actions happen at the same time, while still keeping the shared resources synchronized and safe.
