#include "BookingService.h"
#include <algorithm>
#include <iostream>

BookingService::BookingService()
{
    movieTheaterLink = new MovieTheaterLink();
}

BookingService::~BookingService()
{
}

int BookingService::addMovie(const std::string& title)
{
    // Simple logic for assigning ids.
    // I would prefer UUID from some third-party library,
    // but for simplicity of the test task such approach will do.
    int id = movies.size() + 1;

    Movie* movie = new Movie(id, title);
    movies.insert(std::make_pair(id, movie));

    return id;
}

int BookingService::addTheater(const std::string& name, std::vector<uint16_t> numSeatsByRows)
{
    // Simple logic for assigning ids.
    // I would prefer UUID from some third-party library,
    // but for simplicity of the test task such approach will do.
    int id = theaters.size() + 1;

    Theater* theater = new Theater(id, name, numSeatsByRows);
    theaters.insert(std::make_pair(id, theater));

    return id;
}

int BookingService::addTheater(const std::string& name, const std::vector<Seat>& seats)
{
    // Simple logic for assigning ids.
    // I would prefer UUID from some third-party library,
    // but for simplicity of the test task such approach will do.
    int id = theaters.size() + 1;

    Theater* theater = new Theater(id, name, seats);
    theaters.insert(std::make_pair(id, theater));

    return id;
}

bool BookingService::linkMovieToTheater(int movieId, int theaterId)
{
    auto itMovies = movies.find(movieId);
    if (itMovies == movies.end())
        return false;

    auto itTheaters = theaters.find(theaterId);
    if (itTheaters == theaters.end())
        return false;

    if (movieTheaterLink->exist(movieId, theaterId))
        return false;

    movieTheaterLink->addLink(movieId, theaterId);

    // While linking movie to theater let's also create single show info.
    // It could be extended to multiple shows if we add date and time.
    showInfos.push_back(new ShowInfo(movieId, selectTheater(theaterId)));

    return true;
}

void BookingService::unlinkMovieToTheater(int movieId, int theaterId)
{
    movieTheaterLink->removeLink(movieId, theaterId);

    auto it = std::find_if(showInfos.begin(), showInfos.end(), [&](ShowInfo* showInfo) {
        return showInfo->getMovieId() == movieId && showInfo->getTheaterId() == theaterId;
    });

    if (it != showInfos.end())
    {
        delete *it;
        showInfos.erase(it);
    }
}

std::vector<Movie*> BookingService::viewAllMovies()
{
    std::vector<Movie*> movieVector;
    for (const auto& pair : movies)
    {
        movieVector.push_back(pair.second);
    }
    return movieVector;
}

Movie* BookingService::selectMovie(int id)
{
    auto it = movies.find(id);
    if (it != movies.end())
        return movies[id];
    else
        return nullptr;
}

std::vector<Theater*> BookingService::viewTheatersShowingMovie(int movieId)
{
    std::vector<Theater*> result;

    auto theatersIds = movieTheaterLink->getTheatersIds(movieId);

    for (auto theaterId : theatersIds)
    {
        result.push_back(selectTheater(theaterId));
    }

    return result;
}

Theater* BookingService::selectTheater(int id)
{
    auto it = theaters.find(id);
    if (it != theaters.end())
        return theaters[id];
    else
        return nullptr;
}

std::vector<Seat> BookingService::viewAvailableSeats(int movieId, int theaterId)
{
    auto showInfo = selectShowInfo(movieId, theaterId);
    if (showInfo != nullptr)
    {
        return showInfo->getAvailableSeats();
    }
    return std::vector<Seat>{};
}

Booking BookingService::bookSeats(int movieId, int theaterId, const std::vector<Seat>& seatsToBook)
{
    // Lock the mutex to ensure thread safety
    std::lock_guard<std::mutex> lock(mutex);

    auto showInfo = selectShowInfo(movieId, theaterId);
    std::string errorMsg;

    if (showInfo != nullptr)
    {
        bool success = true;

        // Check seat availability that every seat is available
        for (const auto& seat : seatsToBook)
        {
            if (showInfo->isSeatReserved(seat))
            {
                success = false;
                errorMsg = "Seat [" + std::to_string(seat.row) + ", " +
                           std::to_string(seat.numInRow) + "] is already booked";
                break;
            }
        }

        // Book seats only if all of them are available
        if (success)
        {
            for (const auto& seat : seatsToBook)
            {
                showInfo->reserveSeat(seat);
            }

            // Simple logic for assigning ids.
            // I would prefer UUID from some third-party library,
            // but for simplicity of the test task such approach will do.
            int id = bookings.size();

            Booking booking;
            booking.id = id;
            booking.movieId = movieId;
            booking.theaterId = theaterId;
            booking.success = true;
            booking.seatNumbers = seatsToBook;
            bookings.push_back(booking);
            return booking;
        }
    }
    else
    {
        errorMsg = "No such movie with id " + std::to_string(movieId) + " in theater with id " +
                   std::to_string(theaterId) + " was found";
    }

    // Let's also return info about requested seat in the booking record even if the booking failed
    return { false, errorMsg, -1, movieId, theaterId, seatsToBook };
}

ShowInfo* BookingService::selectShowInfo(int movieId, int theaterId)
{
    for (auto showInfo : showInfos)
    {
        if (showInfo->getMovieId() == movieId && showInfo->getTheaterId() == theaterId)
        {
            return showInfo;
        }
    }

    return nullptr;
}
