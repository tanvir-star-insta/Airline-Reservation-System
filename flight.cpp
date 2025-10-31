#include "flight.h"
#include <iostream>
#include <fstream>
#include <sstream>

Flight::Flight(const std::string& fn, const std::string& f, const std::string& t, const std::string& depTime, int seats)
    : flightNumber(fn), from(f), to(t), departureTime(depTime), totalSeats(seats), seatsBooked(0) {}

std::string Flight::getFlightNumber() const { return flightNumber; }
std::string Flight::getFrom() const { return from; }
std::string Flight::getTo() const { return to; }
std::string Flight::getDepartureTime() const { return departureTime; }
int Flight::getTotalSeats() const { return totalSeats; }
int Flight::getSeatsBooked() const { return seatsBooked; }
int Flight::getSeatsAvailable() const { return totalSeats - seatsBooked; }

bool Flight::bookSeat() {
    if (seatsBooked < totalSeats) {
        seatsBooked++;
        return true;
    }
    return false;
}

void Flight::cancelSeat() {
    if (seatsBooked > 0) {
        seatsBooked--;
    }
}

void Flight::showInfo() const {
    std::cout << "Flight: " << flightNumber << " From: " << from << " To: " << to
              << " Departure: " << departureTime
              << " Seats: " << seatsBooked << "/" << totalSeats << '\n';
}

// Static functions to load/save flights from file
std::vector<Flight> Flight::loadFlights(const std::string& filename) {
    std::vector<Flight> flights;
    std::ifstream fin(filename);
    if (!fin) return flights;
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string fn, f, t, dep;
        int seats, booked;
        if (iss >> fn >> f >> t >> dep >> seats >> booked) {
            Flight fl(fn, f, t, dep, seats);
            fl.seatsBooked = booked;
            flights.push_back(fl);
        }
    }
    return flights;
}

void Flight::saveFlights(const std::vector<Flight>& flights, const std::string& filename) {
    std::ofstream fout(filename);
    for (const auto& f : flights) {
        fout << f.flightNumber << ' ' << f.from << ' ' << f.to << ' '
             << f.departureTime << ' ' << f.totalSeats << ' ' << f.seatsBooked << '\n';
    }
}
