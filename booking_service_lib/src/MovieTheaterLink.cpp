#include "MovieTheaterLink.h"

#include <algorithm>

MovieTheaterLink::MovieTheaterLink()
{
}

void MovieTheaterLink::addLink(int movieId, int theaterId)
{
    // Check if the theater already exists in the map
    auto it = linkMapMoviesToTheater.find(theaterId);
    if (it != linkMapMoviesToTheater.end())
    {
        // Theater already exists, add the movie to its list
        it->second.push_back(movieId);
    }
    else
    {
        // Theater doesn't exist, create a new entry
        linkMapMoviesToTheater.emplace(theaterId, std::vector<int>{ movieId });
    }
}

void MovieTheaterLink::removeLink(int movieId, int theaterId)
{
    // Find the theater in the map
    auto it = linkMapMoviesToTheater.find(theaterId);
    if (it != linkMapMoviesToTheater.end())
    {
        // Theater found, remove the movie from its list
        auto& moviesIds = it->second;
        moviesIds.erase(std::remove(moviesIds.begin(), moviesIds.end(), movieId), moviesIds.end());
    }
}

std::vector<int> MovieTheaterLink::getMoviesIds(int theaterId)
{
    // Find the theater in the map
    auto it = linkMapMoviesToTheater.find(theaterId);
    if (it != linkMapMoviesToTheater.end())
    {
        // Theater found, return the list of movies
        return it->second;
    }
    else
    {
        // Theater not found, return an empty list
        static std::vector<int> emptyList;
        return emptyList;
    }
}

std::vector<int> MovieTheaterLink::getTheatersIds(int movieId)
{
    std::vector<int> theatersIds;

    // Iterate through links and get current theaterId
    for (auto it = linkMapMoviesToTheater.begin(); it != linkMapMoviesToTheater.end(); it++)
    {
        int theaterId = it->first;

        // Check whether such movie is shown in current theater
        if (std::find(it->second.begin(), it->second.end(), movieId) != it->second.end())
        {
            theatersIds.push_back(theaterId);
        }
    }
    return theatersIds;
}

bool MovieTheaterLink::exist(int movieId, int theaterId)
{
    // Find the theater in the map
    auto it = linkMapMoviesToTheater.find(theaterId);
    if (it != linkMapMoviesToTheater.end())
    {
        // Check whether such movie is shown in current theater
        if (std::find(it->second.begin(), it->second.end(), movieId) != it->second.end())
        {
            return true;
        }
    }
    return false;
}
