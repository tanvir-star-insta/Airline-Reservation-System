# Airline Reservation System in C++

## Overview

A console-based Airline Reservation System developed in C++11 utilizing Object-Oriented Programming (OOP) principles. It simulates a real-world flight booking experience with distinct passenger and airline admin interfaces.

## Features

- **Passenger Module**: Sign up/login systems with Aadhaar verification; search, book, and cancel flights; view ticket details with real-time departure status.
- **Airline Admin Module**: Secure login (username: `emirates`, password: `test123`) with masked password input; manage flights and passenger lists with clear, professional layouts.
- **File Persistence**: Flight and booking data saved and loaded from text files to ensure data consistency.
- **Time-Based Status**: Displays time left until departure or flight gone status using system clock.
- **Password Security**: Password inputs are masked to enhance privacy during login/signup.
- **OOP Design**: Modular architecture with classes for clean separation of concerns and extensibility.

## Security Considerations

- Password masking protects user input on login screens.
- Separate roles for passengers and airline admins with login authentication.
- Stored user data and bookings are managed securely in text files with controlled access.
- Airline admin credentials are fixed but can be extended to role-based access control.
- The system design supports further encryption and multi-factor authentication enhancements.

## Compilation

Compile with: g++ -std=c++11 main.cpp user.cpp flight.cpp booking.cpp airline.cpp utils.cpp -o AirlineReservationSystem


## Usage

Run the executable and follow the menu to log in as a passenger or airline admin. Passengers can book, view, and cancel tickets; airlines can view flights and passenger details.

---

This project offers a functional foundation for airline booking simulations that can be expanded with web interfaces, encrypted databases, and advanced security mechanisms.

Contributions and improvements are welcome!

---


