#ifndef TEST_BOOKING_H
#define TEST_BOOKING_H

#include <gtest/gtest.h>

#include "BookingService.h"

class TestBooking : public testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

    void simulateBookingRequests(int movieId, int theaterId, const std::vector<Seat>& seatsToBook,
                                 bool shouldFail = false);
    void randomDelay();

    BookingService* bookingService;
};

#endif
