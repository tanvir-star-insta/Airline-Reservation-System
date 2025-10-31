#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <vector>
#include "flight.h"
#include "booking.h"

class Airline {
private:
    const std::string username = "emirates";
    const std::string password = "test123";

    bool authenticated;
public:
    Airline();

    bool login();

    void showFlights(const std::vector<Flight>& flights) const;
    void showPassengerList(const std::vector<Booking>& bookings, const std::string& flightNumber) const;
};

#endif
