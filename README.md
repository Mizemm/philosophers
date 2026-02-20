# 🍝 Philosophers
**Dining Philosophers: A project about Multithreading and Resource Management.**

## 📖 Overview
In this project, I explored the basics of threading a process. I learned how to create threads and how to use mutexes to solve the classic "Dining Philosophers" problem—a famous illustration of synchronization issues and techniques to resolve them.

The goal is to prevent the philosophers from dying of starvation by managing their access to a limited number of "forks" (resources) using synchronization primitives.



## 🛠️ Technical Implementation
* **Language:** C
* **Concepts:** Multithreading, Mutexes, Data Races, Deadlocks, Shared Resources.
* **Architecture:** * Each philosopher is a **thread**.
    * Each fork is protected by a **mutex** to ensure only one philosopher can hold it at a time.
    * A monitoring system checks for death or completion status to safely terminate the simulation.

## 🚀 Key Challenges Solved
* **Avoiding Deadlocks:** Implemented logic to ensure philosophers don't get stuck waiting for each other forever.
* **Preventing Data Races:** Every shared variable (e.g., the "last meal time") is strictly protected by mutexes.
* **Optimizing CPU Usage:** Used precise time-tracking and small sleeps (`usleep`) to prevent the program from consuming 100% of the CPU while waiting.

## 💻 Usage

1. **Compile the project:**
   ```bash
   make
