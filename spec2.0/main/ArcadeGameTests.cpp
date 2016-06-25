//============================================================================
// Name        : ArcadeGameTests.cpp
// Author      : Jeroen Verstraelen & Nisse Strauven
// Version     :
// Description : ArcadeGame in C++
//============================================================================


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "Board.h"
#include "Entity.h"
#include "utils/parsers/GameParser.h"
#include "utils/DesignByContract.h"

using namespace std;

void writeActionsToFile(Board& board, string name){
	REQUIRE(board.properlyInitialized(), "Board wasn't initialized when calling writeActionsToFile");

 	ofstream outputFile;
  	outputFile.open(name.c_str());
	ostringstream onStream;

  	if(board.writeActions(onStream))
		outputFile << onStream.str();
	else
		cout << onStream.str();
  	outputFile.close();	
}

void projectBoardToFile(Board& board, string name){
	REQUIRE(board.properlyInitialized(), "Board wasn't initialized when calling projectBoardToFile");

 	ofstream outputFile;
  	outputFile.open(name.c_str());
	ostringstream onStream;
	
  	if(board.project(onStream))
		outputFile << onStream.str();
	else
		cout << onStream.str();
  	outputFile.close();	
}

void writeBoardToFile(Board& board, string name){
	REQUIRE(board.properlyInitialized(), "Board wasn't initialized when calling writeBoardToFile");
 	ofstream outputFile;
  	outputFile.open(name.c_str());
	ostringstream onStream;

  	if(board.writeOn(onStream))
		outputFile << onStream.str();
	else
		cout << onStream.str();
  	outputFile.close();
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

class ArcadeGameTest: public ::testing::Test {
protected:

	virtual void SetUp() {
		p_ = new Player();
		o_ = new Object();
	}

	virtual void TearDown() {

	}

	Board b_;
	Player* p_;
	Object* o_;
};


TEST_F(ArcadeGameTest, DefaultConstructor) {
	EXPECT_TRUE(b_.properlyInitialized());
	EXPECT_TRUE(p_->properlyInitialized());	
	EXPECT_TRUE(o_->properlyInitialized());	
}

TEST_F(ArcadeGameTest, isValidBoard){
	b_.generateBoard();
	EXPECT_FALSE(b_.isValid());
	b_.setWidth(10);
	b_.setHeight(10);
	o_->setX(1);
	b_.addEntity((*o_));
	b_.setPlayer((*p_));
	b_.setName("TestBoard");
	b_.generateBoard();
	EXPECT_TRUE(b_.isValid());
}

TEST_F(ArcadeGameTest, HappyXMLBoard) {
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(b_.getBoardName() == "HappyDay1");
	EXPECT_TRUE(b_.getHeight() == 10);
	EXPECT_TRUE(b_.getWidth() == 12);
	EXPECT_TRUE(b_.getPlayer() != NULL);
	EXPECT_TRUE((*b_.getPlayer()).getPlayerName() == "HappyDayGuy");
	EXPECT_TRUE(b_.getEntities().size() == 3);
	EXPECT_TRUE(b_.getEntities().size() == 3);
	EXPECT_TRUE(b_.getBoard()[0].size() == 10);
}

TEST_F(ArcadeGameTest, BadXMLBoard) {
	GameParser gameParser;
	EXPECT_FALSE(gameParser.loadFile("xmlDocuments/Tests/badDay1.xml"));
}

TEST_F(ArcadeGameTest, HappyXMLMoves) {
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay2.xml"));	
	gameParser.parseMovement(gameParser.getRoot(),b_);
	writeActionsToFile(b_, "xmlDocuments/Tests/happydayXMLMovesTest.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/happydayXMLMovesTest.txt",
		"xmlDocuments/Tests/happydayXMLMovesExpected.txt"));
}

TEST_F(ArcadeGameTest, BadXMLMoves) {
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/badDay2.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	writeActionsToFile(b_, "xmlDocuments/Tests/BadXMLMovesTest.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/BadXMLMovesTest.txt",
		"xmlDocuments/Tests/BadXMLMovesExpected.txt"));
}

TEST_F(ArcadeGameTest, setHeightContractViolation){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_DEATH(b_.setHeight(-1), "");
}

TEST_F(ArcadeGameTest, setWidthContractViolation){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_DEATH(b_.setWidth(-1), "");
}

TEST_F(ArcadeGameTest, CopyPlayerContractViolation){
	Player player;
	EXPECT_TRUE(player.properlyInitialized());
	Player player2 = player;
	EXPECT_DEATH(player2.getPlayerName(), "");
}

TEST_F(ArcadeGameTest, ValidActionsBefore1){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay2.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	writeActionsToFile(b_, "xmlDocuments/Tests/ValidMovesBefore1Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/ValidMovesBefore1Test.txt",
		"xmlDocuments/Tests/ValidMovesBefore1Expected.txt"));
}

TEST_F(ArcadeGameTest, ValidActionsBefore2){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay2.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	writeBoardToFile(b_, "xmlDocuments/Tests/ValidMovesBefore2Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/ValidMovesBefore2Test.txt",
		"xmlDocuments/Tests/ValidMovesBefore2Expected.txt"));
}

TEST_F(ArcadeGameTest, ValidActions1){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay2.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	b_.doActions();
	writeActionsToFile(b_, "xmlDocuments/Tests/ValidMoves1Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/ValidMoves1Test.txt",
		"xmlDocuments/Tests/ValidMoves1Expected.txt"));
}

TEST_F(ArcadeGameTest, ValidActions2){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay2.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	b_.doActions();
	writeBoardToFile(b_, "xmlDocuments/Tests/ValidMoves2Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/ValidMoves2Test.txt",
		"xmlDocuments/Tests/ValidMoves2Expected.txt"));
}

TEST_F(ArcadeGameTest, InvalidActions1){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay4.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	b_.doActions();
	writeActionsToFile(b_, "xmlDocuments/Tests/InvalidMoves1Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/InvalidMoves1Test.txt",
		"xmlDocuments/Tests/InvalidMoves1Expected.txt"));
}

TEST_F(ArcadeGameTest, InvalidActions2){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay3.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay4.xml"));		
	gameParser.parseMovement(gameParser.getRoot(), b_);
	b_.doActions();
	writeBoardToFile(b_, "xmlDocuments/Tests/InvalidMoves2Test.txt");
	EXPECT_TRUE(FileCompare("xmlDocuments/Tests/InvalidMoves2Test.txt",
		"xmlDocuments/Tests/InvalidMoves2Expected.txt"));
}

TEST_F(ArcadeGameTest, set){
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDay1.xml"));
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_DEATH(b_.setWidth(-1), "");
}

TEST_F(ArcadeGameTest, sameFileCompare){
	EXPECT_FALSE(FileCompare("xmlDocuments/Tests/compareTest.txt",
		"xmlDocuments/Tests/compareTest.txt"));
}

TEST_F(ArcadeGameTest, differentFileCompare){
	EXPECT_FALSE(FileCompare("xmlDocuments/Tests/compareTest.txt",
		"xmlDocuments/Tests/compareTest2.txt"));
}


TEST_F(ArcadeGameTest, emptyFileCompare){
	EXPECT_FALSE(FileCompare("xmlDocuments/Tests/emptyTest.txt",
		"xmlDocuments/Tests/emptyTest.txt"));
}


TEST_F(ArcadeGameTest, HappyXMLBoardMonster) {
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDayMonster1.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(b_.getBoardName() == "happyDayMonster1");
	EXPECT_TRUE(b_.getHeight() == 10);
	EXPECT_TRUE(b_.getWidth() == 12);
	EXPECT_TRUE(b_.getPlayer() != NULL);
	EXPECT_TRUE((*b_.getPlayer()).getPlayerName() == "HappyDayGuy");
	EXPECT_TRUE(b_.getEntities().size() == 4);
	EXPECT_TRUE(b_.getBoard()[0].size() == 10);
}

TEST_F(ArcadeGameTest, HappyXMLBoardWater) {
	GameParser gameParser;
	EXPECT_TRUE(gameParser.loadFile("xmlDocuments/Tests/happyDayWater1.xml"));	
	gameParser.parseBoard(gameParser.getRoot(), b_);
	EXPECT_TRUE(b_.getBoardName() == "happyDayWater1");
	EXPECT_TRUE(b_.getHeight() == 10);
	EXPECT_TRUE(b_.getWidth() == 12);
	EXPECT_TRUE(b_.getPlayer() != NULL);
	EXPECT_TRUE((*b_.getPlayer()).getPlayerName() == "HappyDayGuy");
	EXPECT_TRUE(b_.getEntities().size() == 4);
	EXPECT_TRUE(b_.getBoard()[0].size() == 10);
}


int main(int argc, char **argv) {
       	::testing::InitGoogleTest( &argc, argv );
       	::testing::FLAGS_gtest_death_test_style = "threadsafe";
        return RUN_ALL_TESTS();
}

