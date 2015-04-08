/*#include "stdafx.h"
#include "gtest/gtest.h"

class CRectTest : public ::testing::Test {
};

TEST_F(CRectTest, CheckPerimeter)
{
    CSomeRect rect;
    rect.x = 5;
    rect.y = 6;
    ASSERT_TRUE(rect.GetPerimeter() == 22);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/

#include <iostream>
#include <algorithm>
#include "deque.h"

using namespace std;

const size_t DEQUE_SIZE = 10u;

int main()
{
    Deque<int> d;
    for (size_t i = 0u; i < DEQUE_SIZE; i++)
    {
        d.pushBack(rand());
    }
    d.print();
    sort(d.begin(), d.end());
    d.print();
    sort(d.rbegin(), d.rend());
    d.print();
    //cout << d[100];
    /*for (Deque<int>::iterator it = d.begin(); it != d.end(); it++)
        cout << *it << endl;
    for (size_t i = 0u; i <= DEQUE_SIZE; i++)
    {
        if (!d.empty())
        {
            cout << d.size() << ' ' << d.front() << endl;
            d.popFront();
        }
        else
        {
            cout << "EMPTY\n";
        }
    }*/
    system("pause");
    return 0;
}
