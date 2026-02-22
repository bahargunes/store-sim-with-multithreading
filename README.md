# Store Simulation with Multithreading

This project simulates a store with customers and suppliers using multithreading in C++. It demonstrates the use of mutexes and condition variables to manage concurrent access to shared resources.

## Features

- **Customers**: Customers attempt to buy items from the store.
- **Suppliers**: Suppliers add items to the store's inventory.
- **Thread Synchronization**: Ensures safe access to shared resources using `pthread` library.
- **Monitor Implementation**: Includes a monitor class for easier synchronization.

## File Structure

- **`hw2.cpp`**: Contains the implementation of the store's functionality.
- **`hw2.h`**: Header file for the store's functions.
- **`monitor.h`**: Provides a monitor class for thread synchronization.
- **`testrun.cpp`**: Simulates the store with customers and suppliers.
- **`Makefile`**: Build script for compiling the project.
