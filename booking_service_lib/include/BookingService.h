#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Movie.h"
#include "MovieTheaterLink.h"
#include "ShowInfo.h"
#include "Theater.h"

/**
 * @brief Structure representing a booking information.
 */
struct Booking
{
    bool success;         /**< Indicates whether the booking was successful. */
    std::string errorMsg; /**< Error message in case of failure. */

    int id;                        /**< Booking ID. */
    int movieId;                   /**< ID of the booked movie. */
    int theaterId;                 /**< ID of the theater where the booking was made. */
    std::vector<Seat> seatNumbers; /**< List of seat numbers booked. */
};

/**
 * @brief Class providing booking services for movies and theaters.
 */
class BookingService
{
public:
    /**
     * @brief Constructs a BookingService object.
     */
    BookingService();

    /**
     * @brief Destructor for the BookingService object.
     */
    virtual ~BookingService();

    /**
     * \brief Adds a new movie with the given title.
     *
     * 
     * @param title The title of the movie.
     * @return The assigned ID of the added movie.
     */
    int addMovie(const std::string& title);

    /**
     * \brief Adds a new theater with the specified seating arrangement by rows.
     * 
     * @param name The name of the theater.
     * @param numSeatsByRows Vector specifying the number of seats in each row.
     * @return The assigned ID of the added theater.
     */
    int addTheater(const std::string& name, std::vector<uint16_t> numSeatsByRows);

    /**
     * @brief Adds a new theater with the specified seating arrangement.
     * 
     * @param name The name of the theater.
     * @param seats Vector containing the seats in the theater.
     * @return The assigned ID of the added theater.
     */
    int addTheater(const std::string& name, const std::vector<Seat>& seats);

    /**
     * \brief Links a movie to a theater by their IDs.
     *
     * This function make a link between movie and theater by its IDs.
     * If no movie or theater exists with such ID, or such link already exists, then false is returned.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @return True if the link was successfully created, false otherwise.
     */
    bool linkMovieToTheater(int movieId, int theaterId);

    /**
     * \brief Unlinks a movie from a theater by their IDs.
     *
     * This function remove a link between movie and theater by its IDs.
     * It also removes showInfo with all booked seats information.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     */
    void unlinkMovieToTheater(int movieId, int theaterId);

    /**
     * @brief Retrieves a list of all movies.
     * 
     * @return A vector containing pointers to all movies.
     */
    std::vector<Movie*> viewAllMovies();

    /**
     * @brief Selects a movie by its ID.
     * 
     * @param id The ID of the movie to select.
     * @return A pointer to the selected movie, or nullptr if not found.
     */
    Movie* selectMovie(int id);

    /**
     * @brief Retrieves a list of theaters showing a specific movie.
     * 
     * @param movieId The ID of the movie.
     * @return A vector containing pointers to theaters showing the specified movie.
     */
    std::vector<Theater*> viewTheatersShowingMovie(int movieId);

    /**
     * @brief Selects a theater by its ID.
     * 
     * @param id The ID of the theater to select.
     * @return A pointer to the selected theater, or nullptr if not found.
     */
    Theater* selectTheater(int id);

    /**
     * @brief Retrieves a list of available seats for a specific movie at a specific theater.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @return A vector containing available seats.
     */
    std::vector<Seat> viewAvailableSeats(int movieId, int theaterId);

    /**
     * @brief Books seats for a specific movie at a specific theater.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @param seatsToBook The seats to book.
     * @return A Booking object indicating the success or failure of the booking and also detailed information about the booking.
     */
    Booking bookSeats(int movieId, int theaterId, const std::vector<Seat>& seatsToBook);

private:
    /**
     * @brief Selects the ShowInfo object corresponding to the given movie and theater IDs.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @return A pointer to the selected ShowInfo object, or nullptr if not found.
     */
    ShowInfo* selectShowInfo(int movieId, int theaterId);

private:
    std::unordered_map<int, Movie*> movies;     /**< Map of movie IDs to Movie objects. */
    std::unordered_map<int, Theater*> theaters; /**< Map of theater IDs to Theater objects. */
    MovieTheaterLink* movieTheaterLink;         /**< Pointer to the MovieTheaterLink object. */
    std::vector<ShowInfo*> showInfos; /**< Vector containing pointers to ShowInfo objects. */
    std::vector<Booking> bookings;    /**< Vector containing booking information. */

    std::mutex mutex; /**< Mutex for thread safety. */
};

#endif