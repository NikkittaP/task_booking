#ifndef MOVIE_H
#define MOVIE_H

#include <string>

/**
 * @brief The Movie class represents a movie entity.
 */
class Movie
{
public:
    /**
     * @brief Constructs a new Movie object with the given ID and title.
     * 
     * @param id The ID of the movie.
     * @param title The title of the movie.
     */
    Movie(int id, const std::string& title);

    /**
     * @brief Gets the ID of the movie.
     * 
     * @return The ID of the movie.
     */
    int getId();

    /**
     * @brief Gets the title of the movie.
     * 
     * @return The title of the movie.
     */
    std::string getTitle();

private:
    int id;            /**< The ID of the movie. */
    std::string title; /**< The title of the movie. */
};

#endif
