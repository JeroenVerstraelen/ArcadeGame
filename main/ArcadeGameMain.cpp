//============================================================================
// Name        : ArcadeGameMain.cpp
// Author      : Jeroen Verstraelen & Nisse Strauven			
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include "Entity.h"
#include "Board.h"
#include "utils/parsers/AbstractParser.h"
#include "utils/parsers/GameParser.h"
#include "utils/DesignByContract.h"

using namespace std;


void writeActionsToFile(Board& board){
	REQUIRE(board.properlyInitialized(), "Board wasn't initialized when calling writeActionsToFile");

 	ofstream outputFile;
  	outputFile.open ("ResterendeActies.txt");
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
  	outputFile.open (name.c_str());
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
  	outputFile.open (name.c_str());
	ostringstream onStream;

  	if(board.writeOn(onStream))
		outputFile << onStream.str();
	else
		cout << onStream.str();
  	outputFile.close();
}


void mainMenu() {
	GameParser gameParser;
	Board board;
	vector<pair<pair<string, string>, string> > actions;

	while(true){
		cout << "\n";
		cout << "Main Menu:" << endl;
		cout << "----------" << endl;
		cout << "\n";
		cout << "1: Import a board" << endl;
		cout << "2: Import actions" << endl;
		cout << "3: Run simulation" << endl;
		cout << "4: export output" << endl;
		cout << "5: Show board" << endl;
		cout << "6: Quit" << endl;
		cout << "\n";

		int input;
		string strInput;
		cin >> strInput;
		input = atoi(strInput.c_str());
		cout << "\n";

		if(input == 1){
			cout << "Please provide an input file:" << endl;
			cout << "\n";
			string file;
			cin >> file;
			if(!gameParser.loadFile("xmlDocuments/" + file + ".xml")){
				cout << "This file is not usable." << endl;
				continue;	
			}
			cout << "Importing board..." << endl;
			gameParser.parseBoard(gameParser.getRoot(), board);
			continue;	
		}
		else if(input == 2){
			if (board.getWidth() == 0){
				cout << "Please import a board first.";
				cout << "\n";
				continue;
			}
			else{
				cout << "Please provide an input file:" << endl;
				cout << "\n";
				string file;
				cin >> file;
				if(!gameParser.loadFile("xmlDocuments/" + file + ".xml")) {
					cout << "This file is not usable." << endl;
					continue;
				}
				cout << "Importing actions..." << endl;
				gameParser.parseMovement(gameParser.getRoot(), board);
				continue;
			}
		}
		else if(input == 3){
			if (board.getActions().empty() or board.getWidth() == 0) {
				cout << "Please import a board and movements first.";
				cout << "\n";
				continue;
			}
			else {
				actions = board.getActions();
				string strSteps = "0";
				int steps = 0;
				cout << "How many steps of the simulation do you want to run?" << endl;
				cin >> strSteps;
				steps = atoi(strSteps.c_str());
				if(steps == 0 or steps < 0 or (unsigned) steps > actions.size()-1){
					cout << "Invalid input." << endl;
					continue;
				}
				else{
					vector<pair<pair<string, string>, string> > actionSteps;
					for(int index = 0; index < steps; index++){
						actionSteps.push_back(actions[index]);
					}
					board.setActions(actionSteps);
					if(!board.doActions()){
						cout << "Simulation failed." << endl;
						cout << "All actions have been removed." << endl;
						actions.erase(actions.begin(), actions.end());
						board.setActions(actions);
					}
					else{
						cout << "Done." << endl;
						if(steps == 1)
							actions.erase(actions.begin());
						actions.erase(actions.begin(), actions.begin()+steps-1);
						board.setActions(actions);
					}
				}
			}
		}
		else if(input == 4){
			while (true) {
				if (board.getWidth() == 0) {
					cout << "Please import a board first.";
					cout << "\n";
					break;
				}
				else {
					cout << "\n";
					cout << "Export output:" << endl;
					cout << "--------------" << endl;
					cout << "\n";
					cout << "1: Project board to file" << endl;
					cout << "2: Write board to file" << endl;
					cout << "3: Write actions to file" << endl;
					cout << "4: Quit" << endl;
					cout << "\n";

					int exportInput;
					string strExportInput;
					cin >> strExportInput;
					exportInput = atoi(strExportInput.c_str());	

					if(exportInput == 1){
						cout << "Projecting board to file: Bord.txt";
						projectBoardToFile(board);
					}
					else if(exportInput == 2){
						cout << "Writing board to file: HuidigSpeelveld.txt";
						writeBoardToFile(board);
					}
					else if(exportInput == 3){
						if(board.getActions().empty()){
							cout << "Please import movements first.";
							cout << "\n";
							continue;
						}
						cout << "Writing actions to file: ResterendeActies.txt";
						writeActionsToFile(board);
					}
					else if(exportInput == 4)
						break;
					else{
						cout << "invalid input" << endl;
						continue;
					}
				}
			}
		}
		else if(input == 5){
			if (board.getWidth() == 0) {
				cout << "Please import a board first.";
				cout << "\n";
				continue;;
			}
			else {
				ostringstream onStream;
				board.project(onStream);
				cout << onStream.str();
			}
		}
		else if(input == 6){
			cout << "Quitting..." << endl;
			return;
		}
		else{
			cout << "invalid input" << endl;
			continue;
		}
	}
}

int main(int argc, char **argv) {
	mainMenu();
	return 0;
}
