#include "test_booking.h"
#include "BookingService.h"

#include <chrono>
#include <random>
#include <thread>

namespace
{
const int total_movies = 3;
const int total_theaters = 2;

const std::string title_movie_1 = "Movie 1";
const std::string title_movie_2 = "Movie 2";
const std::string title_movie_3 = "Movie 3";

const std::string name_theater_1 = "Theater 1";
const std::string name_theater_2 = "Theater 2";
} // namespace

void TestBooking::SetUp()
{
    bookingService = new BookingService();

    int idMovie_1 = bookingService->addMovie(title_movie_1);
    int idMovie_2 = bookingService->addMovie(title_movie_2);
    int idMovie_3 = bookingService->addMovie(title_movie_3);

    // Add theater by numSeatsByRows
    std::vector<uint16_t> numSeatsByRows = { 5, 6, 7, 8, 8, 8 };
    int idTheater_1 = bookingService->addTheater(name_theater_1, numSeatsByRows);

    // Add theater by Seat struct
    // clang-format off
    std::vector<Seat> seats{ { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 },
                             { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 },
                             { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 }, { 3, 7 },
                             { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 4, 6 }, { 4, 7 },
                             { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 },
                             { 6, 1 }, { 6, 2 }, { 6, 3 } };
    // clang-format on
    int idTheater_2 = bookingService->addTheater(name_theater_2, seats);

    bookingService->linkMovieToTheater(idMovie_1, idTheater_1);
    bookingService->linkMovieToTheater(idMovie_2, idTheater_2);
    bookingService->linkMovieToTheater(idMovie_3, idTheater_1);
    bookingService->linkMovieToTheater(idMovie_3, idTheater_2);
}

void TestBooking::TearDown()
{
    delete bookingService;
}

void TestBooking::simulateBookingRequests(int movieId, int theaterId,
                                          const std::vector<Seat>& seatsToBook, bool shouldFail)
{
    randomDelay();

    Booking booking = bookingService->bookSeats(movieId, theaterId, seatsToBook);

    if (shouldFail)
    {
        ASSERT_FALSE(booking.success);
    }
    else
    {
        ASSERT_TRUE(booking.success);
        EXPECT_EQ(booking.movieId, movieId);
        EXPECT_EQ(booking.theaterId, theaterId);
        EXPECT_EQ(booking.seatNumbers, seatsToBook);
    }
}

void TestBooking::randomDelay()
{
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a uniform distribution for the delay range
    std::uniform_int_distribution<> delayDistribution(30, 300);

    // Generate a random delay
    int delayMs = delayDistribution(gen);

    // Sleep for the random duration
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
}

// Test view all movies
TEST_F(TestBooking, viewAllMovies)
{
    auto allMovies = bookingService->viewAllMovies();
    EXPECT_EQ(allMovies.size(), total_movies);
}

// Test select movie
TEST_F(TestBooking, selectMovie)
{
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    Movie* selectedMovie1 = bookingService->selectMovie(id1);
    EXPECT_EQ(selectedMovie1->getId(), id1);
    EXPECT_EQ(selectedMovie1->getTitle(), title_movie_1);

    Movie* selectedMovie2 = bookingService->selectMovie(id2);
    EXPECT_EQ(selectedMovie2->getId(), id2);
    EXPECT_EQ(selectedMovie2->getTitle(), title_movie_2);

    Movie* selectedMovie3 = bookingService->selectMovie(id3);
    EXPECT_EQ(selectedMovie3->getId(), id3);
    EXPECT_EQ(selectedMovie3->getTitle(), title_movie_3);

    Movie* selectedMovieNull = bookingService->selectMovie(99);
    EXPECT_EQ(selectedMovieNull, nullptr);
}

// Test view theaters showing movie
TEST_F(TestBooking, viewTheatersWithMovie)
{
    std::vector<Theater*> theatersForMovie1 = bookingService->viewTheatersShowingMovie(1);
    EXPECT_EQ(theatersForMovie1.size(), 1);
    EXPECT_EQ(theatersForMovie1[0]->getName(), name_theater_1);

    std::vector<Theater*> theatersForMovie2 = bookingService->viewTheatersShowingMovie(2);
    EXPECT_EQ(theatersForMovie2.size(), 1);
    EXPECT_EQ(theatersForMovie2[0]->getName(), name_theater_2);

    std::vector<Theater*> theatersForMovie3 = bookingService->viewTheatersShowingMovie(3);
    EXPECT_EQ(theatersForMovie3.size(), 2);
    EXPECT_EQ(theatersForMovie3[0]->getName(), name_theater_2);
    EXPECT_EQ(theatersForMovie3[1]->getName(), name_theater_1);

    // Try to get theaters with movie that does not exist
    std::vector<Theater*> theatersForMovieNull = bookingService->viewTheatersShowingMovie(99);
    EXPECT_EQ(theatersForMovieNull.size(), 0);
}

// Test select theater
TEST_F(TestBooking, selectTheater)
{
    int id1 = 1;
    int id2 = 2;

    Theater* selectedTheater1 = bookingService->selectTheater(id1);
    EXPECT_EQ(selectedTheater1->getId(), id1);
    EXPECT_EQ(selectedTheater1->getName(), name_theater_1);

    Theater* selectedTheater2 = bookingService->selectTheater(id2);
    EXPECT_EQ(selectedTheater2->getId(), id2);
    EXPECT_EQ(selectedTheater2->getName(), name_theater_2);

    Theater* selectedTheaterNull = bookingService->selectTheater(99);
    EXPECT_EQ(selectedTheaterNull, nullptr);
}

// Test view available seats
TEST_F(TestBooking, viewAvailableSeats)
{
    // All seats are empty
    auto availableSeats = bookingService->viewAvailableSeats(3, 2);
    int expectedSeatsNum = 36;
    EXPECT_EQ(availableSeats.size(), expectedSeatsNum);

    // Book multiple seats to check that viewAvailableSeats works after reservation is made
    std::vector<Seat> seatsToBook{ { 3, 3 }, { 3, 4 }, { 3, 5 } };
    bookingService->bookSeats(3, 2, seatsToBook);
    expectedSeatsNum -= 3;
    availableSeats = bookingService->viewAvailableSeats(3, 2);
    EXPECT_EQ(availableSeats.size(), expectedSeatsNum);

    // Check for not existing movie/theater
    availableSeats = bookingService->viewAvailableSeats(99, 99);
    expectedSeatsNum = 0;
    EXPECT_EQ(availableSeats.size(), expectedSeatsNum);
}

// Test book seats
TEST_F(TestBooking, bookSeats)
{
    std::vector<Seat> seatsToBook = { { 1, 1 }, { 1, 3 }, { 1, 5 } };
    Booking booking = bookingService->bookSeats(1, 1, seatsToBook);
    ASSERT_TRUE(booking.success);
    EXPECT_EQ(booking.movieId, 1);
    EXPECT_EQ(booking.theaterId, 1);
    EXPECT_EQ(booking.seatNumbers, seatsToBook);

    // Try to book same seats to check that such booking fails
    booking = bookingService->bookSeats(1, 1, seatsToBook);
    ASSERT_FALSE(booking.success);

    // Try to book movie that is not shown in the theater
    booking = bookingService->bookSeats(1, 2, seatsToBook);
    ASSERT_FALSE(booking.success);

    // Try to book seats that do not exist
    seatsToBook = { { 99, 99 } };
    booking = bookingService->bookSeats(2, 2, seatsToBook);
    ASSERT_FALSE(booking.success);
}

// Test simultaneous book seats requests
TEST_F(TestBooking, simulateMultipleBookingRequests)
{
    int movieId = 2;
    int theaterId = 2;
    // clang-format off
    std::vector<Seat> seatsToBook1 = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 } };
    std::vector<Seat> seatsToBook2 = { { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 } };
    std::vector<Seat> seatsToBook3 = { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 }, { 3, 7 } };
    std::vector<Seat> seatsToBook4 = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 4, 6 }, { 4, 7 } };
    std::vector<Seat> seatsToBook5 = { { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 } };
    std::vector<Seat> seatsToBook6 = { { 6, 1 }, { 6, 2 }, { 6, 3 } };
    // clang-format off

    std::vector<std::thread> threads;

    threads.emplace_back([this, movieId, theaterId, seatsToBook1]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook1);
    });
    threads.emplace_back([this, movieId, theaterId, seatsToBook2]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook2);
    });
    threads.emplace_back([this, movieId, theaterId, seatsToBook3]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook3);
    });
    threads.emplace_back([this, movieId, theaterId, seatsToBook4]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook4);
    });
    threads.emplace_back([this, movieId, theaterId, seatsToBook5]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook5);
    });
    threads.emplace_back([this, movieId, theaterId, seatsToBook6]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook6);
    });

    for (auto& thread : threads)
    {
        thread.join();
    }

    // Try to book same seats to check that error is returned
    threads.emplace_back([this, movieId, theaterId, seatsToBook1]() {
        simulateBookingRequests(movieId, theaterId, seatsToBook1, true);
    });

    threads.back().join();
}