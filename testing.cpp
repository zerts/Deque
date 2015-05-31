#include <gtest/gtest.h>
#include "deque.h"
#include <ctime>
#include <vector>
#include <deque>
#include <algorithm>
#include <random>

std::default_random_engine generateRandom;

const size_t MIN_NUMBER_OF_ELEMENTS = 10;

using std::deque;

enum TestType
{
    PUSH_BACK,
    POP_BACK,
    PUSH_FRONT,
    POP_FRONT,
    SORT,
    REVERSE_SORT,
    REVERSE,
    EQUALITY_CHECK,
    NUMBER_OF_TESTS
};

class DequeTest : public ::testing::TestWithParam<size_t>{};

std::pair<size_t, size_t> getSegment(size_t size)
{
    std::uniform_int_distribution<int> dequeSize(0, size - 1);
    size_t left = dequeSize(generateRandom);
    size_t right = dequeSize(generateRandom);
    if (left > right)
        std::swap(left, right);
    right++;
    return std::make_pair(left, right);
}

TEST_P(DequeTest, PushTests)
{
    Deque<int> myDeque;
    size_t currentSize = 0u;
    std::uniform_int_distribution<int> chooseDirection(0, 1);
    size_t tests = GetParam();
    ASSERT_EQ(myDeque.size(), currentSize);
    for (size_t i = 0; i < tests; ++i)
    {
        int newKey = generateRandom();
        if (chooseDirection(generateRandom) == PUSH_BACK)
        {
            myDeque.pushBack(newKey);
            ASSERT_EQ(myDeque.back(), newKey);
        }
        else
        {
            myDeque.pushFront(newKey);
            ASSERT_EQ(myDeque.front(), newKey);
        }
        currentSize++;
        ASSERT_EQ(myDeque.size(), currentSize);
    }
}

TEST_P(DequeTest, AllTests)
{
    Deque<int> myDeque;
    deque<int> standartDeque;
    std::uniform_int_distribution<int> queryGetter(0, NUMBER_OF_TESTS - 1);
    generateRandom.seed(1);
    ASSERT_EQ(myDeque.size(), standartDeque.size());
    size_t numberOfTests = GetParam();
    clock_t start = clock();
    for (size_t i = 0; i < numberOfTests; ++i)
    {
        int currKey;
        TestType currTest = static_cast<TestType> (queryGetter(generateRandom));
        if (myDeque.size() < MIN_NUMBER_OF_ELEMENTS)
            currTest = TestType::PUSH_BACK;
        std::pair<size_t, size_t> EndsOfSegment;
        switch (currTest)
        {
        case PUSH_BACK:
            currKey = generateRandom();
            myDeque.pushBack(currKey);
            standartDeque.push_back(currKey);
            ASSERT_EQ(myDeque.back(), currKey);
            break;
        case POP_BACK:
            if (myDeque.size() > 0u)
            {
                myDeque.popBack();
                standartDeque.pop_back();
            }
            break;
        case PUSH_FRONT:
            currKey = generateRandom();
            myDeque.pushFront(currKey);
            standartDeque.push_front(currKey);
            ASSERT_EQ(myDeque.front(), currKey);
            break;
        case POP_FRONT:
            if (myDeque.size() > 0u)
            {
                myDeque.popFront();
                standartDeque.pop_front();
            }
            break;
        case SORT:
            if (myDeque.size() > 0u)
            {
                EndsOfSegment = getSegment(myDeque.size());
                std::sort(myDeque.begin() + EndsOfSegment.first, myDeque.begin() + EndsOfSegment.second);
                std::sort(standartDeque.begin() + EndsOfSegment.first, standartDeque.begin() + EndsOfSegment.second);
            }
            break;
        case REVERSE_SORT:
            if (myDeque.size() > 0u)
            {
                EndsOfSegment = getSegment(myDeque.size());
                std::sort(myDeque.rbegin() + EndsOfSegment.first, myDeque.rbegin() + EndsOfSegment.second);
                std::sort(standartDeque.rbegin() + EndsOfSegment.first, standartDeque.rbegin() + EndsOfSegment.second);
            }
            break;
        case REVERSE:
            if (myDeque.size() > 0u)
            {
                EndsOfSegment = getSegment(myDeque.size());
                std::reverse(myDeque.begin() + EndsOfSegment.first, myDeque.begin() + EndsOfSegment.second);
                std::reverse(standartDeque.begin() + EndsOfSegment.first, standartDeque.begin() + EndsOfSegment.second);
            }
            break;
        case EQUALITY_CHECK:
            if (myDeque.size() > 0u)
            {
                EndsOfSegment = getSegment(myDeque.size());
                ASSERT_EQ(static_cast<int>(std::equal(myDeque.crbegin() + EndsOfSegment.first, myDeque.crbegin() + EndsOfSegment.second, standartDeque.crbegin() + EndsOfSegment.first)) + i - 1, i);
            }
            break;
        }
        ASSERT_EQ(myDeque.size(), standartDeque.size());
        ASSERT_EQ(myDeque.front(), standartDeque.front());
        ASSERT_EQ(myDeque.back(), standartDeque.back());
        ASSERT_EQ(myDeque.empty(), standartDeque.empty());
        for (size_t j = 0; j < myDeque.size(); j++)
            ASSERT_EQ(myDeque[j], standartDeque[j]);
    }
    ASSERT_TRUE(std::equal(myDeque.crbegin(), myDeque.crend(), standartDeque.crbegin()));
}


INSTANTIATE_TEST_CASE_P(CurrentName, DequeTest, ::testing::Values(
    1, 2, 3, 4, 5, 6, 7, 9,
    10, 20, 30, 40, 60, 70, 80, 90,
    100, 200, 300, 400, 500, 700, 800, 900,
    1000, 2000, 3000, 5000, 6000, 7000, 8000, 9000,
    10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
    100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000)
    );

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
