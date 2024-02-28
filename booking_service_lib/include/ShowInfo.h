#include <unordered_map>
#include <utility>
#include <vector>

#include "Theater.h"

/**
 * @brief Class to store data for a specific show, including information about the movie and seat reservations.
 * 
 * This class can be extended to include additional information such as date and time.
 * 
 * @note This is an internal class used internally within the task application.
 */
class ShowInfo
{
public:
    /**
     * @brief Constructs a ShowInfo object with the given movie ID and theater.
     * 
     * @param movieId The ID of the movie being shown.
     * @param theater A pointer to the Theater object representing the theater where the show takes place.
     */
    ShowInfo(int movieId, Theater* theater);

    /**
     * @brief Checks if a seat is reserved for this show.
     * 
     * @param seat The seat to check.
     * @return True if the seat is reserved or not found, false otherwise.
     */
    bool isSeatReserved(Seat seat);

    /**
     * @brief Reserves a seat for this show.
     * 
     * @param seat The seat to reserve.
     */
    void reserveSeat(Seat seat);

    /**
     * @brief Gets the ID of the show.
     * 
     * @return The ID of the show.
     */
    int getId();

    /**
     * @brief Gets the ID of the movie associated with this show.
     * 
     * @return The ID of the movie.
     */
    int getMovieId();

    /**
     * @brief Gets the ID of the theater where the show takes place.
     * 
     * @return The ID of the theater.
     */
    int getTheaterId();

    /**
     * @brief Gets a vector of available seats for this show.
     * 
     * @return A vector containing Seat objects representing the available seats.
     */
    std::vector<Seat> getAvailableSeats();

private:
    int id;        /**< The ID of the show. */
    int movieId;   /**< The ID of the movie associated with the show. */
    int theaterId; /**< The ID of the theater where the show takes place. */
    std::vector<std::pair<Seat, bool>>
        seats; /**< A vector of pairs representing seats and their reservation status. */
};
