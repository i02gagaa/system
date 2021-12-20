// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"
#include "date.h"
#include "gtest/gtest.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

TEST(System, addUser) {
  System system;
  EXPECT_TRUE(system.addUser("u1"));
  EXPECT_FALSE(system.addUser("u2"));
}

TEST(System, deleteUser) {
  System system;
  EXPECT_TRUE(system.deleteUser("u3"));
  EXPECT_FALSE(system.deleteUser("u4"));
}
