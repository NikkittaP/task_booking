#ifndef THEATER_H
#define THEATER_H

#include <mutex>
#include <vector>

/**
 * @brief Represents a seat in a theater.
 */
struct Seat
{
    uint16_t row;      /**< The row number of the seat. */
    uint16_t numInRow; /**< The seat number within the row. */

    /**
     * @brief Overloaded equality operator to compare two seats.
     * 
     * @param other The other seat to compare with.
     * @return True if the seats are equal, false otherwise.
     */
    bool operator==(const Seat& other) const
    {
        return row == other.row && numInRow == other.numInRow;
    }

    /**
     * @brief Overloaded inequality operator to compare two seats.
     * 
     * @param other The other seat to compare with.
     * @return True if the seats are not equal, false otherwise.
     */
    bool operator!=(const Seat& other) const
    {
        return !(*this == other);
    }
};

/**
 * @brief Represents a theater with a seating arrangement.
 */
class Theater
{
public:
    /**
     * @brief Constructs a theater with the given ID, name, and seating arrangement specified by the number of seats in each row.
     * 
     * @param id The ID of the theater.
     * @param name The name of the theater.
     * @param numSeatsByRows A vector containing the number of seats in each row.
     */
    Theater(int id, const std::string& name, std::vector<uint16_t> numSeatsByRows);

    /**
     * @brief Constructs a theater with the given ID, name, and seating arrangement specified by a vector of Seat structs.
     * 
     * @param id The ID of the theater.
     * @param name The name of the theater.
     * @param seats A vector containing the Seat structs representing the seating arrangement.
     */
    Theater(int id, const std::string& name, const std::vector<Seat>& seats);

    /**
     * @brief Gets the ID of the theater.
     * 
     * @return The ID of the theater.
     */
    int getId();

    /**
     * @brief Gets the name of the theater.
     * 
     * @return The name of the theater.
     */
    std::string getName();

    /**
     * @brief Gets the seating arrangement of the theater.
     * 
     * @return A vector containing the Seat structs representing the seating arrangement.
     */
    std::vector<Seat> getSeats();

private:
    int id;           /**< The ID of the theater. */
    std::string name; /**< The name of the theater. */

    // Create a seating arrangement
    std::vector<Seat> theaterSeating; /**< The seating arrangement of the theater. */
};

#endif
