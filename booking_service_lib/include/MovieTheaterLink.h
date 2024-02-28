#include <unordered_map>
#include <vector>

/**
 * @brief Class to manage the links between movies and theaters.
 */
class MovieTheaterLink
{
public:
    /**
     * @brief Constructs a MovieTheaterLink object.
     */
    MovieTheaterLink();

    /**
     * @brief Adds a link between a movie and a theater.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     */
    void addLink(int movieId, int theaterId);

    /**
     * @brief Removes a link between a movie and a theater.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     */
    void removeLink(int movieId, int theaterId);

    /**
     * @brief Gets the IDs of the movies shown in a specific theater.
     * 
     * @param theaterId The ID of the theater.
     * @return A vector containing the IDs of the movies shown in the theater.
     */
    std::vector<int> getMoviesIds(int theaterId);

    /**
     * @brief Gets the IDs of the theaters showing a specific movie.
     * 
     * @param movieId The ID of the movie.
     * @return A vector containing the IDs of the theaters showing the movie.
     */
    std::vector<int> getTheatersIds(int movieId);

    /**
     * @brief Checks whether a link between a movie and a theater already exists.
     * 
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @return True if the link exists, false otherwise.
     */
    bool exist(int movieId, int theaterId);

private:
    std::unordered_map<int, std::vector<int>>
        linkMapMoviesToTheater; /**< Map to store the links between movies and theaters. */
};
