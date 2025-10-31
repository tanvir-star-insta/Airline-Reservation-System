#include "airline.h"
#include <iostream>
#include <string>
#include "utils.h"

Airline::Airline() : authenticated(false) {}

bool Airline::login() {
    std::string userInput, passInput;
    std::cout << "Airline Username: ";
    std::getline(std::cin, userInput);
    passInput = Utils::getPassword("Airline Password: ");

    if (userInput == username && passInput == password) {
        authenticated = true;
        std::cout << "Login successful.\n";
        return true;
    } else {
        std::cout << "Invalid username or password.\n";
        return false;
    }
}

void Airline::showFlights(const std::vector<Flight>& flights) const {
    std::cout << "Available Flights for " << username << ":\n";
    for (const auto& flight : flights) {
        flight.showInfo();
    }
}

void Airline::showPassengerList(const std::vector<Booking>& bookings, const std::string& flightNumber) const {
    std::cout << "\nPassenger List for Flight: " << flightNumber << "\n";
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "BookingID\tPassengerName\tAadhaar\tFrom\tTo\tTrip\tDeparture\n";
    std::cout << "---------------------------------------------------------------------\n";
    bool found = false;
    for (const auto& booking : bookings) {
        if (booking.getFlightNumber() == flightNumber) {
            std::cout << booking.getBookingID() << "\t"
                      << booking.getPassengerName() << "\t"
                      << booking.getPassengerAadhaar() << "\t"
                      << booking.getFrom() << "\t"
                      << booking.getTo() << "\t"
                      << booking.getTripType() << "\t"
                      << booking.getDepartureTime() << '\n';
            found = true;
        }
    }
    if (!found) std::cout << "No passengers booked yet.\n";
    std::cout << "---------------------------------------------------------------------\n";
}
