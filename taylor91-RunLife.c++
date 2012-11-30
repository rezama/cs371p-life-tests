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
#include <stdlib.h>


#ifndef CC_DEF
#define CC_DEF
#include "ConwayCell.h"
#endif

#ifndef FC_DEF
#define FC_DEF
#include "FredkinCell.h"
#endif


#ifndef CELL_DEF
#define CELL_DEF
#include "Cell.h"
#endif


#ifndef LIFE_DEF
#define LIFE_DEF
#include "Life.h"
#endif

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

	ifstream ConwayIn("RunLifeConway.in", ifstream::in);
	ofstream ConwayOut("RunLifeConway.out");


    // ------------------
    // Conway Cell 109x69
    // ------------------
    try {
        
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
        ConwayOut << "*** Life<ConwayCell> 109x69 ***" << endl;
        ConwayOut << endl;
        
		char inputLine[10];
		ConwayIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		ConwayIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<ConwayCell> grid(rows, cols, ConwayIn);
		grid.print_grid(ConwayOut);
		
		for(int i = 0; i < 283; i++)
		{
			grid.take_turn();	
		}
		ConwayOut << endl;
		grid.print_grid(ConwayOut);
		
		for(int i = 0; i < 40; i++)
		{
			grid.take_turn();
		}
		ConwayOut << endl;
		grid.print_grid(ConwayOut);
		
		for(int i = 0; i < 2500; i++)
		{
			grid.take_turn();
		}
		ConwayOut << endl;
		grid.print_grid(ConwayOut);
		
		
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        
	 //------------
	 // Conway 10x10
	 //------------


	try {
		while(ConwayIn.peek() == '\n'){
			ConwayIn.get();
		}
    	ConwayOut << "\n*** Life<ConwayCell> 10x10 ***" << endl;
    
		char inputLine[10];
		ConwayIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		ConwayIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
    	
		Life<ConwayCell> life(rows, cols, ConwayIn);
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		life.take_turn();
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		life.take_turn();
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		life.take_turn();
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		life.take_turn();
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		
		for(int i = 0; i < 100; i++)
		{
			life.take_turn();
		}
		ConwayOut << endl;
		life.print_grid(ConwayOut);
	}
	catch (const invalid_argument&) {
	assert(false);}
	catch (const out_of_range&) {
	assert(false);}
	
	
	 //------------
	 // Conway 30x25
	 //------------


	try {
		while(ConwayIn.peek() == '\n'){
			ConwayIn.get();
		}
    	ConwayOut << "\n*** Life<ConwayCell> 30x25 ***" << endl;
    
		char inputLine[10];
		ConwayIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		ConwayIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
    	
		Life<ConwayCell> life(rows, cols, ConwayIn);
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		life.take_turn();
		ConwayOut << endl;
		for(int i = 0; i < 5; i++)
		{
			life.take_turn();
		}
		ConwayOut << endl;
		life.print_grid(ConwayOut);
		
		for(int i = 0; i < 5; i++)
		{
			life.take_turn();
		}
		ConwayOut << endl;
		life.print_grid(ConwayOut);
	}
	catch (const invalid_argument&) {
	assert(false);}
	catch (const out_of_range&) {
	assert(false);}



	ConwayIn.close();
	ConwayOut.close();


	ifstream FredkinIn("RunLifeFredkin.in", ifstream::in);
	ofstream FredkinOut("RunLifeFredkin.out");
	
	
	
	
	// ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        FredkinOut << "*** Life<FredkinCell> 20x20 ***" << endl;
        FredkinOut << endl;
        
		char inputLine[10];
		FredkinIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		FredkinIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<FredkinCell> grid(rows, cols, FredkinIn);
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 2; i++)
		{
			grid.take_turn();
			FredkinOut << endl;
			grid.print_grid(FredkinOut);	
		}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	

	// ------------------
    // Fredkin Cell 44x102
    // ------------------

    try {
        while(FredkinIn.peek() == '\n'){
				FredkinIn.get();
		}
			
        FredkinOut << "\n*** Life<FredkinCell> 44x102 ***" << endl;
        FredkinOut << endl;
        
		char inputLine[10];
		FredkinIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		FredkinIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		
		Life<FredkinCell> grid(rows, cols, FredkinIn);
		grid.print_grid(FredkinOut);
			
	
		grid.take_turn();
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 5; i++)
		{
			grid.take_turn();	
		}
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 5; i++)
		{
			grid.take_turn();	
		}
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 15; i++)
		{
			grid.take_turn();	
		}
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 20; i++)
		{
			grid.take_turn();	
		}
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
       
        
    // ------------------
    // Fredkin Cell 35x25
    // ------------------

    try {
        while(FredkinIn.peek() == '\n'){
				FredkinIn.get();
		}
			
        FredkinOut << "\n*** Life<FredkinCell> 35x25 ***" << endl;
        FredkinOut << endl;
        
		char inputLine[10];
		FredkinIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		FredkinIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		
		Life<FredkinCell> grid(rows, cols, FredkinIn);
		grid.print_grid(FredkinOut);
			
	
		grid.take_turn();
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
		
		for(int i = 0; i < 49; i++)
		{
			grid.take_turn();	
		}
		FredkinOut << endl;
		grid.print_grid(FredkinOut);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
     
    FredkinIn.close();   
    FredkinOut.close();   
         
       
    ifstream CellIn("RunLife.in", ifstream::in);   
    ofstream CellOut("RunLife.out");    
        
    // ----------
    // Cell 20x20
    // ----------

    try {
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        CellOut << "*** Life<Cell> 20x20 ***" << endl;
        CellOut << endl;
        
		char inputLine[10];
		CellIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		CellIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<Cell> grid(rows, cols, CellIn);
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 5; i++)
		{
			grid.take_turn();
			CellOut << endl;
			grid.print_grid(CellOut);	
		}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // Cell 54x99
    // ----------
       
     try {
		while(CellIn.peek() == '\n'){
				CellIn.get();
		}
        CellOut << "\n*** Life<Cell> 54x99 ***" << endl;
        CellOut << endl;
        
		char inputLine[10];
		CellIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		CellIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<Cell> grid(rows, cols, CellIn);
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 10; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 10; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 10; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	// ----------
    // Cell 16x16
    // ----------
       
     try {
		while(CellIn.peek() == '\n'){
				CellIn.get();
		}
        CellOut << "\n*** Life<Cell> 16x16 ***" << endl;
        CellOut << endl;
        
		char inputLine[10];
		CellIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		CellIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<Cell> grid(rows, cols, CellIn);
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 5; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 10; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 15; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
        
    // ----------
    // Cell 16x16
    // ----------
       
     try {
		while(CellIn.peek() == '\n'){
				CellIn.get();
		}
        CellOut << "\n*** Life<Cell> 16x16 ***" << endl;
        CellOut << endl;
        
		char inputLine[10];
		CellIn.getline(inputLine, 10);
		int rows = atoi(inputLine);
		CellIn.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<Cell> grid(rows, cols, CellIn);
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 5; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 10; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
		
		for(int i = 0; i < 15; i++)
		{
			grid.take_turn();	
		}
		CellOut << endl;
		grid.print_grid(CellOut);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	CellIn.close();
	CellOut.close();

    return 0;}

