// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
    % valgrind RunLife.c++.app > RunLife.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>
#include <string>

#include "Life.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"

using namespace std;

/**
* given an input file's name, creates a new game of life from the input
* @return Life the new game of life constructed
*/
template <typename T>
Life<T> fileToLife(string fileName) {
	// init vals to be filled
	string currentLine;
	int population = 0;
	vector< vector<T> > gameBoard;
	// open the file stream
	ifstream inStream(fileName);
	// if successful, process input
	if (inStream.is_open()) {
		// ySize
		getline (inStream, currentLine);
		// xSize
		getline (inStream, currentLine);
		while (inStream.good()) {
			getline (inStream, currentLine);
			const char *currSymbol = currentLine.c_str();
			vector<T> currRow;
			while (*currSymbol != '\0' && *currSymbol != '\r') {
				//cout << *currSymbol << endl; // REMOVE
				T currCell(*currSymbol);
				*currSymbol++;				
				if (currCell.isLiving()){
					population++;
				}
				currRow.push_back(currCell);
			}
			// if the row isn't right right size (blank line) don't append
			if (currRow.size() > 0){
				gameBoard.push_back(currRow);
			}			
		}
		// close the stream
		inStream.close();
	}
	// if this happens, you likely input a bad file name
	else {
		assert(false && "Something is wrong with the file read");
	}
	Life<T> currGame(gameBoard, population);
	return currGame;
}


// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
    	string outputToFile = "";
    	string retString = "*** Life<ConwayCell> 109x69 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";

        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 283 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        Simulate 2500 moves.
        Print grid.
        */
		
		string fileName = "RunLifeConway.in";
        Life<ConwayCell> currLife = fileToLife<ConwayCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 1; i < 283+40+2500+1; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (i == 283 || i == (283+40) || i == (283+40+2500)){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeConway.out");
		outFile << outputToFile;
		outFile.close();
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
    	string outputToFile = "";
    	string retString = "*** Life<FredkinCell> 20x20 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
    	
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
		string fileName = "RunLifeFredkin.in";
        Life<FredkinCell> currLife = fileToLife<FredkinCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 2; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeFredkin.out");
		outFile << outputToFile;
		outFile.close();        
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<Cell> 20x20 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeCell.in";
        Life<Cell> currLife = fileToLife<Cell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeCell.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
     catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Conway 15x17
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<ConwayCell> 15x17 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput1.in";
        Life<ConwayCell> currLife = fileToLife<ConwayCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput1.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}

	// ----------
    // Conway 8x17
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<ConwayCell> 8x17 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput2.in";
        Life<ConwayCell> currLife = fileToLife<ConwayCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput2.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}		

	// ----------
    // Conway 12x17
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<ConwayCell> 12x17 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput3.in";
        Life<ConwayCell> currLife = fileToLife<ConwayCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput3.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}	

	// ----------
    // FredkinCell 8x17
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<FredkinCell> 8x17 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput4.in";
        Life<FredkinCell> currLife = fileToLife<FredkinCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 50; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (i % 10 == 0){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput4.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}		

	// ----------
    // FredkinCell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<FredkinCell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput5.in";
        Life<FredkinCell> currLife = fileToLife<FredkinCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 25; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (i % 5 == 0){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput5.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}	

	// ----------
    // FredkinCell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<FredkinCell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput6.in";
        Life<FredkinCell> currLife = fileToLife<FredkinCell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput6.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}	
		
	// ----------
    // Cell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<Cell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput7.in";
        Life<Cell> currLife = fileToLife<Cell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput7.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Cell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<Cell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput8.in";
        Life<Cell> currLife = fileToLife<Cell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput8.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Cell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<Cell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput9.in";
        Life<Cell> currLife = fileToLife<Cell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput9.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Cell 8x16
    // ----------

    try {
    
    	string outputToFile = "";
    	string retString = "*** Life<Cell> 8x16 ***";
        cout << retString << endl;
    	outputToFile += retString + "\n";
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		string fileName = "RunLifeInput10.in";
        Life<Cell> currLife = fileToLife<Cell>(fileName);
		
		retString = currLife.gameBoardToString();
		cout << retString << endl;
		outputToFile += retString + "\n";
		for (int i = 0; i < 5; i++){
			currLife.driveGeneration();
			// if we are on a print generation, print
			if (true){ 
				retString = currLife.gameBoardToString();
				cout << retString << endl;
				outputToFile += retString + "\n";
			}			
		}	
		// write the output to a file
		ofstream outFile;
		outFile.open ("RunLifeInput10.out");
		outFile << outputToFile;
		outFile.close();   
        
        }
    catch (const invalid_argument&) {
        assert(false);}
	catch (const out_of_range&) {
        assert(false);}
		
    return 0;}
