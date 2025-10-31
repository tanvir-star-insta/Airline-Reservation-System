#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "flight.h"
#include "user.h"

class Booking {
private:
    std::string bookingID;
    std::string flightNumber;
    std::string passengerName;
    std::string passengerAadhaar;
    std::string from;
    std::string to;
    std::string tripType; // "single" or "round"
    std::string departureTime; // time of flight
public:
    Booking() = default;
    Booking(const std::string& bID, const std::string& fNum, const std::string& pName, const std::string& pAadh, const std::string& f, const std::string& t, const std::string& trip, const std::string& depTime);

    void showBooking() const;
    std::string getFlightNumber() const;
    std::string getPassengerAadhaar() const;
    std::string getBookingID() const;

    // Added getters for private members
    std::string getPassengerName() const;
    std::string getFrom() const;
    std::string getTo() const;
    std::string getTripType() const;
    std::string getDepartureTime() const;

    static void saveBooking(const Booking& booking, const std::string& filename);
    static void loadBookings(std::vector<Booking>& bookings, const std::string& filename);
    static void overwriteBookings(const std::vector<Booking>& bookings, const std::string& filename);

    static std::string generateBookingID();
    static bool isDeparturePassed(const std::string& departureTime);
    static void timeLeftMessage(const std::string& departureTime);
};

#endif
