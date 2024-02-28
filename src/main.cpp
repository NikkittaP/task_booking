#include "BookingService.h"
#include <algorithm>
#include <iostream>

int main()
{
    BookingService* bookingService = new BookingService();

    int idMovie_1 = bookingService->addMovie("Movie 1");
    int idMovie_2 = bookingService->addMovie("Movie 2");
    int idMovie_3 = bookingService->addMovie("Movie 3");

    // Add theater by numSeatsByRows
    std::vector<uint16_t> numSeatsByRows = { 5, 5, 5, 5 };
    int idTheater_1 = bookingService->addTheater("Theater 1", numSeatsByRows);

    // Add theater by Seat struct
    // clang-format off
    std::vector<Seat> seats{ { 1, 1 }, { 1, 2 }, { 1, 3 },
                             { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 },
                             { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 },
                             { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 },
                             { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 } };
    // clang-format on
    int idTheater_2 = bookingService->addTheater("Theater 2", seats);

    bookingService->linkMovieToTheater(idMovie_1, idTheater_1);
    bookingService->linkMovieToTheater(idMovie_2, idTheater_2);
    bookingService->linkMovieToTheater(idMovie_3, idTheater_1);
    bookingService->linkMovieToTheater(idMovie_3, idTheater_2);

    std::cout << std::endl;
    
    Booking booking = bookingService->bookSeats(idMovie_1, idTheater_1,
                                                { { 1, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 2, 5 } });
    booking = bookingService->bookSeats(idMovie_3, idTheater_1,
                                        { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } });
    booking = bookingService->bookSeats(idMovie_2, idTheater_2,
                                        { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } });
    booking = bookingService->bookSeats(idMovie_3, idTheater_2, { { 1, 2 } });
    std::cout << "Made some bookings to show seat arrangement visualization" << std::endl;

    std::cout << std::endl;

    std::cout << "All movies:" << std::endl;
    auto allMovies = bookingService->viewAllMovies();
    for (const auto& movie : allMovies)
    {
        std::cout << "   [" << movie->getId() << "] " << movie->getTitle() << std::endl;
    }
    std::cout << std::endl;

    for (const auto& selectedMovie : allMovies)
    {
        std::cout << "Selected movie: " << selectedMovie->getTitle() << std::endl;

        std::cout << "   Theaters showing movie:" << std::endl;

        for (const auto& theater : bookingService->viewTheatersShowingMovie(selectedMovie->getId()))
        {
            std::cout << "      [" << theater->getId() << "] " << theater->getName() << std::endl;
        }
    }
    std::cout << std::endl;

    for (const auto& movie : allMovies)
    {
        for (const auto& theater : bookingService->viewTheatersShowingMovie(movie->getId()))
        {
            std::cout << "Showing  seats for Movie '" << movie->getTitle() << "' in Theater '"
                      << theater->getName() << "' (0 - seat is available):" << std::endl;

            auto totalSeats = theater->getSeats();
            auto availableSeats = bookingService->viewAvailableSeats(movie->getId(),
                                                                     theater->getId());
            int prevRow = 1;
            for (auto seat : totalSeats)
            {
                if (prevRow != seat.row)
                {
                    std::cout << std::endl;
                }

                if (std::find(availableSeats.begin(), availableSeats.end(), seat) !=
                    availableSeats.end())
                    std::cout << " 0 ";
                else
                    std::cout << " 1 ";

                prevRow = seat.row;
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Infinite loop in which the service could work" << std::endl;
    while (true)
    {
        // Further code to proccess request from frontend..
    }

    return 0;
}
