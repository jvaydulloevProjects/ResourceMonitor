# Task Processing System

**Task Processing System** is a multithreaded task processing system in C++ with support for an event-driven model and logging. The project demonstrates working with **threads**, a **task queue**, **event subscriptions**, file I/O, and real-time data processing.

---

## 📌 Key Features

- **Multithreaded Task Processing**:
  - `Producer` adds tasks to the queue.
  - `Consumer` processes tasks (e.g., divides numbers by 2).
- **Task Queue (`TaskQueue`)** with thread-safe access and notifications.
- **Event System (`EventManager`)**:
  - Subscribe to events: `TaskAdded`, `TaskRemoved`, `TaskProcessed`.
  - Notify subscribers using delegates.
- **Logging (`Logger`)**:
  - Automatic console logging of events.
- **File I/O (`FileReader`)**:
  - Read tasks from a file.
  - Write processed tasks to a file.
- **Random data generation** for testing purposes.

---

## 🏗️ Project Structure
├── include/
│ ├── Consumer.hpp
│ ├── Producer.hpp
│ ├── Logger.hpp
│ ├── FileReader.hpp
│ ├── EventManager.hpp
│ ├── TaskQueue.hpp
│ └── interfaces.hpp
├── src/
│ └── main.cpp
├── logs/
│ └── log.txt
└── input.txt


### Main Classes

| Class | Purpose |
|-------|---------|
| `Producer<T>` | Adds tasks to the queue |
| `Consumer<T>` | Processes tasks and writes results |
| `TaskQueue<T>` | Thread-safe task queue |
| `EventManager<T>` | Manages events and subscribers |
| `Logger<T>` | Logs events to console |
| `FileReader<T>` | Reads tasks from file and writes results |
| `IProducable<T>, IConsumable<T>, IReadable<T>, IWriteable<T>` | Interfaces for abstraction |

---

## 🚀 Installation and Running

1. **Clone the repository**

```bash
git clone https://github.com/jvaydulloevProjects/ResourceMonitor.git
cd ResourceMonitor

2. **Compile the project**
g++ -std=c++17 src/main.cpp -Iinclude -pthread -o TaskProcessor

3.Run the program
./TaskProcessor

The program will generate an input.txt file with random numbers, process the tasks, log events to the console, and write results to logs/log.txt.
