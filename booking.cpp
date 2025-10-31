#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

Booking::Booking(const std::string& bID, const std::string& fNum, const std::string& pName, const std::string& pAadh, const std::string& f, const std::string& t, const std::string& trip, const std::string& depTime)
    : bookingID(bID), flightNumber(fNum), passengerName(pName), passengerAadhaar(pAadh), from(f), to(t), tripType(trip), departureTime(depTime) {}

void Booking::showBooking() const {
    std::cout << "Booking ID: " << bookingID << "\nPassenger: " << passengerName << "\nAadhaar: " << passengerAadhaar
              << "\nFlight: " << flightNumber << "\nFrom: " << from << "\nTo: " << to
              << "\nTrip: " << tripType << "\nDeparture Time: " << departureTime << '\n';
    if (isDeparturePassed(departureTime)) {
        std::cout << "Status: Flight has gone.\n";
    } else {
        std::cout << "Time left until departure: ";
        timeLeftMessage(departureTime);
    }
}

void Booking::saveBooking(const Booking& booking, const std::string& filename) {
    std::ofstream fout(filename, std::ios::app);
    if (fout) {
        fout << booking.bookingID << ' ' << booking.flightNumber << ' ' << booking.passengerName << ' '
             << booking.passengerAadhaar << ' ' << booking.from << ' ' << booking.to << ' '
             << booking.tripType << ' ' << booking.departureTime << '\n';
    }
}

void Booking::loadBookings(std::vector<Booking>& bookings, const std::string& filename) {
    bookings.clear();
    std::ifstream fin(filename);
    if (!fin) return;
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string bID, fNum, pName, pAadh, f, t, trip, dep;
        if (iss >> bID >> fNum >> pName >> pAadh >> f >> t >> trip >> dep) {
            bookings.emplace_back(bID, fNum, pName, pAadh, f, t, trip, dep);
        }
    }
}

void Booking::overwriteBookings(const std::vector<Booking>& bookings, const std::string& filename) {
    std::ofstream fout(filename);
    for (const auto& b : bookings) {
        fout << b.bookingID << ' ' << b.flightNumber << ' ' << b.passengerName << ' '
             << b.passengerAadhaar << ' ' << b.from << ' ' << b.to << ' '
             << b.tripType << ' ' << b.departureTime << '\n';
    }
}

std::string Booking::generateBookingID() {
    std::time_t t = std::time(nullptr);
    std::stringstream ss;
    ss << "BKG" << t;
    return ss.str();
}

bool Booking::isDeparturePassed(const std::string& departureTime) {
    std::time_t now = std::time(nullptr);
    std::tm tm_now{};
    std::tm* local_tm = std::localtime(&now);
    if (local_tm) tm_now = *local_tm;
    else return false;

    int depHour = std::stoi(departureTime.substr(0, 2));
    int depMin = std::stoi(departureTime.substr(3, 2));

    if (tm_now.tm_hour > depHour) return true;
    if (tm_now.tm_hour == depHour && tm_now.tm_min >= depMin) return true;
    return false;
}

void Booking::timeLeftMessage(const std::string& departureTime) {
    std::time_t now = std::time(nullptr);
    std::tm tm_now{};
    std::tm* local_tm = std::localtime(&now);
    if (!local_tm) {
        std::cout << "Unknown time left\n";
        return;
    }
    tm_now = *local_tm;

    int depHour = std::stoi(departureTime.substr(0, 2));
    int depMin = std::stoi(departureTime.substr(3, 2));
    int nowMins = tm_now.tm_hour * 60 + tm_now.tm_min;
    int depMins = depHour * 60 + depMin;
    int diff = depMins - nowMins;
    int hours = diff / 60;
    int mins = diff % 60;
    std::cout << hours << " hour(s) and " << mins << " minute(s)\n";
}

// Getters
std::string Booking::getFlightNumber() const { return flightNumber; }
std::string Booking::getPassengerAadhaar() const { return passengerAadhaar; }
std::string Booking::getBookingID() const { return bookingID; }

std::string Booking::getPassengerName() const { return passengerName; }
std::string Booking::getFrom() const { return from; }
std::string Booking::getTo() const { return to; }
std::string Booking::getTripType() const { return tripType; }
std::string Booking::getDepartureTime() const { return departureTime; }
