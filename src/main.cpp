#include "gtest/gtest.h"
#include <iostream>

#include "../include/account.h"
#include "../include/backingSystem.h"
#include "../include/creditAccount.h"
#include "../include/currency.h"
#include "../include/customer.h"
#include "../include/savingsAccount.h"
#include "../include/transaction.h"


int main (int argc, char *argv[]) {

    if (true) // make false to run unit tests
    {
        // debug section
    }
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}