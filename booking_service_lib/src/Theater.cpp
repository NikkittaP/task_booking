#include "Theater.h"

Theater::Theater(int id, const std::string& name, std::vector<uint16_t> numSeatsByRows) :
    id(id),
    name(name)
{
    uint16_t currentRow = 1;
    for (uint16_t seats : numSeatsByRows)
    {
        for (uint16_t seatNum = 1; seatNum <= seats; seatNum++)
        {
            Seat seat{ currentRow, seatNum };
            theaterSeating.push_back(seat);
        }

        currentRow++;
    }
}

Theater::Theater(int id, const std::string& name, const std::vector<Seat>& seats) :
    id(id),
    name(name),
    theaterSeating(seats)
{
}

int Theater::getId()
{
    return id;
}

std::string Theater::getName()
{
    return name;
}

std::vector<Seat> Theater::getSeats()
{
    return theaterSeating;
}
