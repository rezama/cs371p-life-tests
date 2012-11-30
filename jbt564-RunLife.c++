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
// ----
// main
// ----
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "AbstractCell.h"


void getWH(int& width, int& height, ifstream& file_1);

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
  

  // ------------------
  // Conway Cell 109x69
  // ------------------

  try {
    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
   
	//READ FILE INFO
    ifstream file_1;
    string line;
    int width = 0;
    int height = 0;

	//OPEN FILE
    file_1.open("RunLifeConway.in");

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);

	//SET UP LIFE
    Life <ConwayCell> grid(width,height,true);
    vector <ConwayCell> c_cell(0);
    c_cell.reserve(width*height);
  

	//INITIALIZE CELL VECTOR
      for(int i = 0; i <= height; i++){
		getline (file_1, line);	//GET ONE LINE OF INPUT
	
	  	for(unsigned int j = 0; j < line.length(); j++){
	  		if(line[j] == '.')
	    		c_cell.push_back(ConwayCell(false));	//DEAD CONWAY
	  		else
	    		c_cell.push_back(ConwayCell(true));		//ALIVE CONWAY
		}
      }

	//WRITE FILE INFO
    ofstream file_2 ("RunLifeConway.out");
    
	//INITIALIZE GRID WITH CELLS
	grid.addLiveCells(c_cell);
	
	//OUTPUT
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 283 STEPS & OUTPUT      
    grid.simulateSteps(283);
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 40 STEPS & OUTPUT
    grid.simulateSteps(40);
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 2500 STEPS & OUTPUT
    grid.simulateSteps(2500);
    grid.output(file_2);
    file_2 << std::endl;

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


    
  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}

  // ------------------
  // Fredkin Cell 20x20
  // ------------------

  try {
    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    
	//READ FILE INFO
	ifstream file_1;
    string line;
    int width = 0;
    int height = 0; 

	//OPEN FILE
    file_1.open("RunLifeFredkin.in");

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);

	//INITIALIZE GRID
    Life <FredkinCell> grid(width,height,false);
    vector <FredkinCell> c_cell(0);
    c_cell.reserve(width*height);

  	//FILL VECTOR WILL CELLS
    for(int i = 0; i <= height; i++){
      getline (file_1, line);	//GET ONE LINE
    	for(unsigned int j = 0; j < line.length(); j++){
			if(line[j] == '-')	//IS IT DEAD
	  			c_cell.push_back(FredkinCell());				//DEAD FREDKIN
			else
	  			c_cell.push_back(FredkinCell(line[j]-'0'));		//ALIVE FREDKIN
      	}
    }

	//WRITE FILE INFO
    ofstream file_2 ("RunLifeFredkin.out");

	//INSERT CELLS INTO GRID
    grid.addLiveCells(c_cell);

	//OUTPUT FIRST GRID
    grid.output(file_2);
    file_2 << std::endl;
    
	//SIMULATE AND OUTPUT 2 MOVES
    for(int i = 0; i < 2; i ++){
      grid.step();
      grid.output(file_2);
      file_2 << std::endl;
    }

    /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
    */
  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}

  // ----------
  // Cell 20x20
  // ----------

  try {
    cout << "*** Life<Cell> 20x20 ***" << endl;
   
	//READ FILE INFO
	ifstream file_1;
    string line;
    int width = 0;
    int height = 0;

	//OPEN FILE
    file_1.open("RunLife.in");

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);

	//INITIALIZE GRID
    Life <Cell> grid(width,height,false);
    vector <Cell> c_cell(0);
    c_cell.reserve(width*height);

	//FILL VECTOR WITH CELLS
    for(int i = 0; i <= height; i++){
      getline (file_1, line);

      for(unsigned int j = 0; j < line.length(); j++){
        if(line[j] == '-')
          c_cell.push_back(Cell(new FredkinCell()));			//DEAD CELL WITH FREDKIN
        else
          c_cell.push_back(Cell(new FredkinCell(line[j]-'0')));	//ALIVE CELL WITH FREDKIN
      }
    }

	//WRITE FILE INFO
    ofstream file_2 ("RunLife.out");

	//INTIALIZE GRID WITH VECTOR OF CELLS
    grid.addLiveCells(c_cell);

	//OUTPUT FIRST GRID
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE AND OUTPUT 5 STEPS
    for(int i = 0; i < 5; i ++){
      grid.step();
      grid.output(file_2);
      file_2 << std::endl;
    }


    /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
    */
  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}

	//----------------------------------------------------------
	// Conway Tests 1,2,3
	// THE FOLLOWING THREE TESTS COME FROM A SINGLE INPUT FILE
	//----------------------------------------------------------

  try {
    cout << "*** Life<ConwayCell> 20x20 ***" << endl;
	
	//READ FILE INFO    
	ifstream file_1;
    string line;
    int width = 0;
    int height = 0;

	//OUR SINGLE INPUT FILE
    file_1.open("RunLifeTest1.in");

	//---------------------
	// BEGINNING OF TEST 1
	//---------------------

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);

	//INITIALIZE FIRST CONWAY GRID
    Life <ConwayCell> grid(width,height,true);
    vector <ConwayCell> c_cell(0);
    c_cell.reserve(width*height);
  
	//INTIALIZE CELL VECTOR    
	for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
			if(line[j] == '.')
	   			c_cell.push_back(ConwayCell(false));
			else
	  			c_cell.push_back(ConwayCell(true));
		}
    }

	//FIRST OUTPUT FILE INFO
    ofstream file_2 ("RunLifeConway1.out");

	//INITIALIZE GRID WITH CELLS    
	grid.addLiveCells(c_cell);

	//OUTPUT FIRST GRID
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 10 STEPS AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;  

	//SIMULATE 10 STEPS AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 10 STEPS AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//----------------
	// END OF TEST 1
	//----------------

	//---------------------
	// BEGINNING OF TEST 2
	//---------------------
    
	cout << "*** Life<ConwayCell> 4x4 ***" << endl;

	//RESET WIDTH AND HEIGHT
    width = 0; 
    height = 0;
 
	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);

	//REINITIALIZE GRID AND VECTOR
    grid = Life <ConwayCell>(width,height,true);
    vector <ConwayCell> c_cell2(0);
    c_cell2.reserve(width*height);

	//INITIALIZE CELL VECTOR
    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
	  		if(line[j] == '.')
	    		c_cell2.push_back(ConwayCell(false));
	  		else
	    		c_cell2.push_back(ConwayCell(true));
		}
    }

	//SECOND WRITE FILE INFO
    ofstream file_3("RunLifeConway2.out");
    
	//ADD CELLS
	grid.addLiveCells(c_cell2);
	
	//SIMULATE AND OUTPUT 3 GRIDS
	for(int i = 0; i < 3; i++){
	   grid.output(file_3);	   
	   file_3 << std::endl;
	   grid.step();
	}

	//---------------
	// END OF TEST 2
	//---------------

	//-----------------------
	//	BEGINNING OF TEST 3
	//-----------------------
	cout << "*** Life<ConwayCell> 30x3 ***" << endl;

	//RESET WIDTH AND HEIGHT
    width = 0; 
    height = 0;

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);
    
	//REINITIALIZE GRID AND CELL VECTOR
	grid = Life <ConwayCell>(width,height,true);
    vector <ConwayCell> c_cell3(0);
    c_cell3.reserve(width*height);

	//INSERT CELL VECTOR 
    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
	  		if(line[j] == '.')
	    		c_cell3.push_back(ConwayCell(false));
	  		else
	    		c_cell3.push_back(ConwayCell(true));
		}
    }

	//THIRD OUTPUT FILE
    ofstream file_4("RunLifeConway3.out");
      
	//INSERT CELLS INTO GRID
	grid.addLiveCells(c_cell3);
	
	//SIMULATE AND OUTPUT 5 STEPS
	for(int i = 0; i < 5; i++){
	   grid.output(file_4);	   
	   file_4 << std::endl;
	   grid.step();
	}
	//---------------
	// END OF TEST 3
	//---------------
  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}

	//----------------------------------------------------------
	// Fredkin Tests 1,2,3
	// THE FOLLOWING THREE TESTS COME FROM A SINGLE INPUTE FILE
	//----------------------------------------------------------

  try {
    cout << "*** Life<FredkinCell> 10x10 ***" << endl;

	//SET UP INPUT FILE
    ifstream file_1;
    string line;
    int width = 0;
    int height = 0;
    file_1.open("RunLifeTest2.in");

	//-----------------------
	// BEGINNING OF TEST ONE
	//-----------------------

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);
    
	//INITIALIZE GRID AND VECTOR
	Life <FredkinCell> grid(width,height,true);
    vector <FredkinCell> c_cell(0);
    c_cell.reserve(width*height);
  
	//FILL UP CELL VECTOR
    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
			if(line[j] == '-')
	    		c_cell.push_back(FredkinCell());
	  		else
	    		c_cell.push_back(FredkinCell(0));
		}
    }

	//FIRST OUTPUT FILE
    ofstream file_2 ("RunLifeFredkin1.out");
    
	//INSERT CELLS
	grid.addLiveCells(c_cell);

	//OUTPUT FIRST GRID
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 15 MOVES AND OUTPUT
    grid.simulateSteps(15);
    grid.output(file_2);
    file_2 << std::endl;  
	
	//SIMULATE 10 MOVES AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 10 MOVES AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//---------------
	// END OF TEST 1
	//---------------

	//---------------------
	// BEGINNING OF TEST 2
	//---------------------
 
    cout << "*** Life<FredkinCell> 20x20 ***" << endl;

	//RESET WIDTH AND HEIGHT . . . ETC
    width = 0; 
    height = 0;
    getWH(width, height, file_1);
    grid = Life <FredkinCell>(width,height,true);
    vector <FredkinCell> c_cell2(0);
    c_cell2.reserve(width*height);

      for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
			for(unsigned int j = 0; j < line.length(); j++){
	  			if(line[j] == '-')
	    			c_cell2.push_back(FredkinCell());
	  			else
	   				 c_cell2.push_back(FredkinCell(0));
			}
      }

	//OUTPUT FILE
      ofstream file_3("RunLifeFredkin2.out");
      grid.addLiveCells(c_cell2);
	
	//SIMULATE AND OUTPUT 30 GRIDS
	for(int i = 0; i < 30; i++){
	   grid.output(file_3);	   
	   file_3 << std::endl;
	   grid.step();
	}

	//----------------
	// END OF TEST 2
	//----------------
	
	//---------------------
	// BEGINNING OF TEST 3
	//---------------------

	cout << "*** Life<FredkinCell> 40x40 ***" << endl;

	//RESET HEIGHT AND WIDTH . . . ETC
    width = 0; 
    height = 0;
    getWH(width, height, file_1);
    grid = Life <FredkinCell>(width,height,true);
    vector <FredkinCell> c_cell3(0);
    c_cell3.reserve(width*height);

    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
	  		if(line[j] == '-')
	    		c_cell3.push_back(FredkinCell());
	  		else
	    		c_cell3.push_back(FredkinCell(0));
		}
    }


	//OUTPUT FILE 3
      ofstream file_4("RunLifeFredkin3.out");
      grid.addLiveCells(c_cell3);
	
	//OUTPUT AND SIMULATE 30 STEPS
	for(int i = 0; i < 30; i++){
	   grid.output(file_4);	   
	   file_4 << std::endl;
	   grid.step();
	}

	//---------------
	// END OF TEST 3
	//---------------
  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}

	//----------------------------------------------------------------------------------------------
	// CELL TESTS 1,2,3,4	ALL FREDKIN, CONWAY STYLES OMMITED BECAUSE THEY ARE BORING AND THE SAME 
	//						AS REGULAR CONWAY TESTS
	// THE FOLLOWING FOUR TESTS COME FROM A SINGLE INPUTE FILE
	//---------------------------------------------------------------------------------------------

    ifstream file_1;
    string line;
    int width = 0;
    int height = 0;
    file_1.open("RunLifeTest3.in");
	Life <Cell> grid(width,height,false);
  try {
    cout << "*** Life<Cell> 25x25 ***" << endl;
	//-----------------------
	// BEGINNING OF TEST ONE
	//-----------------------

	//GET WIDTH AND HEIGHT
    getWH(width, height, file_1);
	//INITIALIZE GRID AND VECTOR
	//Life <Cell> grid(width,height,false);
    vector <Cell> c_cell(0);
    c_cell.reserve(width*height);
  	Life <Cell> grid = Life <Cell>(width,height,false);
	//FILL UP CELL VECTOR
    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
		for(unsigned int j = 0; j < line.length(); j++){
			if(line[j] == '-')
	    		c_cell.push_back(Cell(new FredkinCell()));
	  		else
	    		c_cell.push_back(Cell(new FredkinCell(0)));
		}
    }

	//FIRST OUTPUT FILE
    ofstream file_2 ("RunLifeCell1.out");
    
    //INSERT CELLS
    grid.addLiveCells(c_cell);

	//OUTPUT FIRST GRID
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 15 MOVES AND OUTPUT
    grid.simulateSteps(15);
    grid.output(file_2);
    file_2 << std::endl;  
	
	//SIMULATE 10 MOVES AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//SIMULATE 10 MOVES AND OUTPUT
    grid.simulateSteps(10);
    grid.output(file_2);
    file_2 << std::endl;

	//---------------
	// END OF TEST 1
	//---------------

	//---------------------
	// BEGINNING OF TEST 2
	//---------------------
 
    cout << "*** Life<Cell> 50x50 ***" << endl;

	//RESET WIDTH AND HEIGHT . . . ETC
    width = 0; 
    height = 0;
    getWH(width, height, file_1);
    grid = Life <Cell>(width,height,false);
    vector <Cell> c_cell2(0);
    c_cell2.reserve(width*height);

      for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
			for(unsigned int j = 0; j < line.length(); j++){
	  			if(line[j] == '-')
	    			c_cell2.push_back(Cell (new FredkinCell()));
	  			else
	   				 c_cell2.push_back(Cell(new FredkinCell(0)));
			}
      }

	//OUTPUT FILE
      ofstream file_3("RunLifeCell2.out");
      grid.addLiveCells(c_cell2);
	
	//SIMULATE AND OUTPUT 30 GRIDS
	for(int i = 0; i < 30; i++){
	   grid.output(file_3);	   
	   file_3 << std::endl;
	   grid.step();
	}

	//----------------
	// END OF TEST 2
	//----------------

  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}
	//---------------------
	// BEGINNING OF TEST 3
	//---------------------
  try { 
    cout << "*** Life<Cell> 100x100 ***" << endl;

	//RESET WIDTH AND HEIGHT . . . ETC
    width = 0; 
    height = 0;
    getWH(width, height, file_1);
    grid = Life <Cell>(width,height,false);
    vector <Cell> c_cell3(0);
    c_cell3.reserve(width*height);


      for(int i = 0; i <= height; i++){
	getline (file_1, line);
	for(unsigned int j = 0; j < line.length(); j++){
	  if(line[j] == '-')
	    c_cell3.push_back(Cell (new FredkinCell()));
	  else
	    c_cell3.push_back(Cell(new FredkinCell(0)));
	}
      }

	//OUTPUT FILE
      ofstream file_4("RunLifeCell3.out");
      grid.addLiveCells(c_cell3);
	
	//SIMULATE AND OUTPUT 100 GRIDS
	for(int i = 0; i < 100; i++){
	   grid.output(file_4);	   
	   file_4 << std::endl;
	   grid.step();
	}

	grid.simulateSteps(1000);
	grid.output(file_4);

	//----------------
	// END OF TEST 3
	//----------------

	//---------------------
	// BEGINNING OF TEST 4
	//---------------------
 
    cout << "*** Life<Cell> 150x150 ***" << endl;

	//RESET WIDTH AND HEIGHT . . . ETC
    width = 0; 
    height = 0;
    getWH(width, height, file_1);
    grid = Life <Cell>(width,height,false);
    vector <Cell> c_cell4(0);
    c_cell4.reserve(width*height);

    for(int i = 0; i <= height; i++){
		getline (file_1, line);
	
			for(unsigned int j = 0; j < line.length(); j++){
	  			if(line[j] == '-')
	    			c_cell4.push_back(Cell (new FredkinCell()));
	  			else
	   				 c_cell4.push_back(Cell(new FredkinCell(0)));
			}
      }

	//OUTPUT FILE
      ofstream file_5("RunLifeCell4.out");
      grid.addLiveCells(c_cell4);
	
	//SIMULATE AND OUTPUT 100 GRIDS
	for(int i = 0; i < 100; i++){
	   grid.output(file_5);	   
	   file_5 << std::endl;
	   grid.step();
	}

	grid.simulateSteps(1000);
	grid.output(file_5);

	//----------------
	// END OF TEST 4
	//----------------

  }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}



  return 0;}


 void getWH(int& width, int& height, ifstream& file_1){
   string line;

  if(file_1.is_open()){
	//READ ONE LINE
    getline (file_1,line);
    for(unsigned int i = 0; i < line.length(); i++){	//FOR THE LENGTH OF THE LINE
      height += (line[i]-'0');	//READ NEXT NUMBER 
      if(i != line.length()-1)	//IF YOU AREN'T ON THE LAST NUMBER
		height *= 10;			//SHIFT NUMBERS ONE DIGIT TO THE LEFT
    }
	//READ SECOND LINE . . . SAME
    getline (file_1,line);
    for(unsigned int i = 0; i < line.length(); i++){
      width += (line[i]-'0');
      if(i != line.length()-1)
	width *= 10;
    }

  }
}
