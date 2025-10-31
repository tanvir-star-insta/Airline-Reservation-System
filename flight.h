#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>

class Flight {
private:
    std::string flightNumber;
    std::string from;
    std::string to;
    std::string departureTime; // format "HH:MM"
    int totalSeats;
    int seatsBooked;
public:
    Flight() = default;
    Flight(const std::string& fn, const std::string& f, const std::string& t, const std::string& depTime, int seats);

    std::string getFlightNumber() const;
    std::string getFrom() const;
    std::string getTo() const;
    std::string getDepartureTime() const;
    int getTotalSeats() const;
    int getSeatsBooked() const;
    int getSeatsAvailable() const;

    bool bookSeat();
    void cancelSeat();

    void showInfo() const;

    static std::vector<Flight> loadFlights(const std::string& filename);
    static void saveFlights(const std::vector<Flight>& flights, const std::string& filename);
};

#endif
