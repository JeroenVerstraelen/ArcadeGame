
//============================================================================
// Name        : ArcadeGameTests.cpp
// Author      : Jeroen Verstraelen
// Version     :
// Description : ArcadeGame in C++
//============================================================================


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "Board.h"
#include "Entity.h"

using namespace std;


class ArcadeGameTest: public ::testing::Test {
protected:

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}

	/**
	Declares the variables your tests want to use.
	*/
	Board b_;
	Player p_;
	Object o_;
};


TEST_F(ArcadeGameTest, DefaultConstructor) {
	EXPECT_TRUE(b_.properlyInitialized());
	EXPECT_TRUE(p_.properlyInitialized());	
	EXPECT_TRUE(o_.properlyInitialized());	
}

TEST_F(ArcadeGameTest, isValidBoard){
	b_.generateBoard();
	EXPECT_FALSE(b_.isValid());
	b_.setWidth(10);
	b_.setHeight(10);
	b_.addEntity(o_);
	b_.setPlayer(p_);
	b_.setName("TestBoard");
	b_.generateBoard();
	EXPECT_TRUE(b_.isValid());
}


/**
Auxiliary function for file manipulation in unit tests.
*/
bool DirectoryExists(const char *dirname) {
	struct stat st;
	return stat(dirname, &st) == 0;
}

/**
Auxiliary function for file manipulation in unit tests.
*/
bool FileCompare(const char *leftFileName, const char *rightFileName) {
	ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		// last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}

int main(int argc, char **argv) {
       	::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}

