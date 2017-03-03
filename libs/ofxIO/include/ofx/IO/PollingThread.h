
//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/IO/Thread.h"


namespace ofx {
namespace IO {


/// \brief A thread that repeatedly calls a function based on a polling interval.
class PollingThread: public Thread
{
public:
    /// \brief Create a thread that repeats according to the \p pollingInterval.
    /// \param threadedFunction The function to run in a seperate thread.
    /// \param pollingInterval The polling interval in milliseconds.
    PollingThread(std::function<void()> threadedFunction,
                  uint64_t pollingInterval = DEFAULT_POLLING_INTERVAL);

    /// \brief Destroy the PollingThread.
    virtual ~PollingThread();

    /// \brief Set the maximum polling interval.
    /// \param pollingInterval The polling interval in milliseconds.
    void setPollingInterval(uint64_t pollingInterval);

    /// \returns the polling interval in milliseconds.
    uint64_t getPollingInterval() const;

    /// \brief Set the maximum number of repeats.
    /// \param maximumPollingCount The maximum number of repeats to set.
    void setMaximumPollingCount(int64_t maximumPollingCount);

    /// \returns the maximum number of repeats allowed.
    int64_t getMaximumPollingCount() const;

    /// \brief Reset repeat counts.
    void reset();

    /// \returns the number of times the the function has been repeated.
    uint64_t pollingCount() const;

    enum
    {
        /// \brief The maximum number of repetitions.
        UNLIMITED_POLLING_COUNT = -1,

        /// \brief The default polling repeats.
        DEFAULT_MAXIMUM_POLLING_COUNT = UNLIMITED_POLLING_COUNT,

        /// \brief The default polling interval in milliseconds.
        DEFAULT_POLLING_INTERVAL = 1000
    };

protected:
    bool shouldRepeatWithDelay(uint64_t& delay) override;

private:
    /// \brief The maximum number of times to repeat. -1 is unlimited.
    std::atomic<int64_t> _maximumPollingCount;

    /// \brief The number of repeats so far.
    std::atomic<int64_t> _pollingCount;

    /// \brief The polling interval in milliseconds.
    std::atomic<uint64_t> _pollingInterval;

};


} } // namespace ofx::IO
