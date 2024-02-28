#include <iostream>

#include "ShowInfo.h"

ShowInfo::ShowInfo(int movieId, Theater* theater) : movieId(movieId), theaterId(theater->getId())
{
    // Make all seats available
    for (auto theaterSeat : theater->getSeats())
    {
        seats.push_back(std::make_pair(theaterSeat, false));
    }
}

bool ShowInfo::isSeatReserved(Seat seat)
{
    for (const auto& pair : seats)
    {
        if (pair.first == seat)
        {
            // Found the seat, check if it's occupied
            return pair.second; // Return the boolean flag
        }
    }
    // Seat not found, return true (assumes occupied if seat not found)
    return true;
}

void ShowInfo::reserveSeat(Seat seat)
{
    for (auto& pair : seats)
    {
        if (pair.first == seat)
        {
            // Seat found, reserve it by setting the boolean flag to true
            pair.second = true;
            //std::cout << "Seat [" << seat.row << ", " << seat.numInRow << "] reserved.\n";
            return;
        }
    }
}

int ShowInfo::getId()
{
    return id;
}

int ShowInfo::getMovieId()
{
    return movieId;
}

int ShowInfo::getTheaterId()
{
    return theaterId;
}

std::vector<Seat> ShowInfo::getAvailableSeats()
{
    std::vector<Seat> availableSeats;

    for (auto& pair : seats)
    {
        if (pair.second == false)
        {
            availableSeats.push_back(pair.first);
        }
    }

    return availableSeats;
}