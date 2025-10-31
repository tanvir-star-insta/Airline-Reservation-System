#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "user.h"
#include "flight.h"
#include "booking.h"
#include "airline.h"
#include "utils.h"

const std::string flightsFile = "flights.txt";
const std::string bookingsFile = "bookings.txt";

// Customer authentication (simple, stored in memory for demo)
std::vector<User> registeredUsers;

User* customerLogin() {
    std::string email, pass;
    std::cout << "Enter Email: ";
    std::getline(std::cin, email);
    pass = Utils::getPassword("Enter Password: ");

    for (auto& u : registeredUsers) {
        if (u.getEmail() == email && u.verifyPassword(pass)) {
            std::cout << "Login successful. Welcome " << u.getName() << "!\n";
            return &u;
        }
    }
    std::cout << "Invalid credentials.\n";
    return nullptr;
}

User* customerSignUp() {
    std::string pass, passConfirm;
    User newUser;
    newUser.fillProfile();
    std::cout << "Enter Password: ";
    pass = Utils::getPassword("");
    std::cout << "Confirm Password: ";
    passConfirm = Utils::getPassword("");
    while (pass != passConfirm) {
        std::cout << "Passwords do not match. Enter Password: ";
        pass = Utils::getPassword("");
        std::cout << "Confirm Password: ";
        passConfirm = Utils::getPassword("");
    }
    newUser = User(newUser.getName(), newUser.getEmail(), pass, newUser.getAadhar());
    registeredUsers.push_back(newUser);
    std::cout << "Signup successful! Please login to continue.\n";
    return nullptr;
}

void customerMenu(User& user, std::vector<Flight>& flights) {
    std::vector<Booking> bookings;
    Booking::loadBookings(bookings, bookingsFile);

    while (true) {
        std::cout << "\n--- Customer Menu ---\n";
        std::cout << "1. Book Tickets\n2. View Ticket Details\n3. Logout\nEnter choice: ";
        int choice; std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string from, to, tripType;
            std::cout << "From: "; std::getline(std::cin, from);
            std::cout << "To: "; std::getline(std::cin, to);
            std::cout << "Trip Type (single/round): "; std::getline(std::cin, tripType);

            // List available flights matching from-to
            std::vector<Flight*> availableFlights;
            for (auto& f : flights) {
                if (f.getFrom() == from && f.getTo() == to && f.getSeatsAvailable() > 0) {
                    availableFlights.push_back(&f);
                }
            }
            if (availableFlights.empty()) {
                std::cout << "No flights available matching your criteria.\n";
                continue;
            }
            std::cout << "Available flights:\n";
            for (size_t i = 0; i < availableFlights.size(); ++i) {
                std::cout << i+1 << ". ";
                availableFlights[i]->showInfo();
            }
            std::cout << "Select flight by number: ";
            size_t sel; std::cin >> sel; std::cin.ignore();
            if (sel < 1 || sel > availableFlights.size()) {
                std::cout << "Invalid selection.\n";
                continue;
            }
            Flight* chosen = availableFlights[sel-1];

            if (!chosen->bookSeat()) {
                std::cout << "Sorry, no seats available.\n";
                continue;
            }

            std::string bookingId = Booking::generateBookingID();
            Booking newBooking(bookingId, chosen->getFlightNumber(), user.getName(), user.getAadhar(), from, to, tripType, chosen->getDepartureTime());
            Booking::saveBooking(newBooking, bookingsFile);
            bookings.push_back(newBooking);

            Flight::saveFlights(flights, flightsFile);

            std::cout << "Booking successful! Your booking ID: " << bookingId << '\n';

        } else if (choice == 2) {
            std::string aid;
            std::cout << "Enter Aadhaar number for verification: ";
            std::getline(std::cin, aid);
            bool found = false;
            for (const auto& b : bookings) {
                if (b.getPassengerAadhaar() == aid) {
                    b.showBooking();
                    found = true;
                    std::cout << "Do you want to cancel this ticket? (y/n): ";
                    char ch; std::cin >> ch; std::cin.ignore();
                    if (ch == 'y' || ch == 'Y') {
                        // Cancel seat & booking
                        for (auto& f : flights) {
                            if (f.getFlightNumber() == b.getFlightNumber()) {
                                f.cancelSeat();
                                break;
                            }
                        }
                        // Remove from bookings vector
                        bookings.erase(std::remove_if(bookings.begin(), bookings.end(),
                            [&](const Booking& bk){ return bk.getBookingID() == b.getBookingID(); }), bookings.end());

                        Booking::overwriteBookings(bookings, bookingsFile);
                        Flight::saveFlights(flights, flightsFile);
                        std::cout << "Ticket cancelled successfully.\n";
                        break;
                    }
                }
            }
            if (!found) {
                std::cout << "No booking found with this Aadhaar.\n";
            }
        } else if (choice == 3) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void airlineMenu(Airline& airline, std::vector<Flight>& flights) {
    if (!airline.login()) return;

    std::vector<Booking> bookings;
    Booking::loadBookings(bookings, bookingsFile);

    while (true) {
        std::cout << "\n--- Airline Admin Menu ---\n";
        std::cout << "1. View Flights\n2. View Passenger List for a Flight\n3. Logout\nEnter choice: ";
        int choice; std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            airline.showFlights(flights);
        } else if (choice == 2) {
            std::string flightNum;
            std::cout << "Enter Flight Number: ";
            std::getline(std::cin, flightNum);
            airline.showPassengerList(bookings, flightNum);
        } else if (choice == 3) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

int main() {
    std::vector<Flight> flights = Flight::loadFlights(flightsFile);
    // If no flights file, create some defaults for demo
    if (flights.empty()) {
        flights.emplace_back("EK101", "Delhi", "Dubai", "15:30", 200);
        flights.emplace_back("EK102", "Dubai", "Delhi", "20:00", 200);
        flights.emplace_back("EK201", "Mumbai", "London", "13:00", 150);
        Flight::saveFlights(flights, flightsFile);
    }

    Airline airline;

    while (true) {
        std::cout << "Are you logging in as:\n1. Customer\n2. Airline\n3. Exit\nEnter choice: ";
        int choice; std::cin >> choice;
        std::cin.ignore();

        if(choice == 1){
            std::cout << "1. Sign Up\n2. Login\n3. Back\nEnter choice: ";
            int ch; std::cin >> ch; std::cin.ignore();
            if(ch == 1) {
                customerSignUp();
            } else if (ch == 2) {
                User* user = customerLogin();
                if (user) customerMenu(*user, flights);
            }
        } else if(choice == 2){
            airlineMenu(airline, flights);
        } else if(choice == 3){
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
