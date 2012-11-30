// -------------------------
// projects/life/vshan-RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall vshan-RunLife.c++ -o vshan-RunLife.c++.app
    % valgrind vshan-RunLife.c++.app > vshan-RunLife.out

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
#include <ctype.h>

#include "Cell.h"
#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // 1. Conway Cell 109x69
    // ------------------

    try {
		freopen ("vshan-RunLifeConway.out", "w", stdout);
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;
        ifstream myfile ("vshan-RunLifeConway.in");

        int row;
        int col;
        myfile >> row >> col;
		
        Life<ConwayCell> l(row, col, ConwayCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '*') //alive
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else
        		{
        			//Conway should only be in state dead . or alive *
        			assert(false);
        		}
        	}
        }

        /*
        read vshan-RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 283 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        Simulate 2500 moves.
        Print grid.
        */


        for(int i = 0; i < 283; i++)
        {
        	l.execute();
        }
        l.print();

        for(int i = 0; i < 40; i++)
        {
        	l.execute();
        }
        l.print();

        for(int i = 0; i < 2500; i++)
        {
        	l.execute();
        }
        l.print();

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // 2. Fredkin Cell 20x20
    // ------------------

    try {
		freopen ("vshan-RunLifeFredkin.out", "w", stdout);
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
		
		ifstream myfile ("vshan-RunLifeFredkin.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<FredkinCell> l(row, col, FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '-') //dead
        		{
        			l.add(FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c))
				{
					int cell_age = c - '0';
					l.add(FredkinCell(cell_age,c), i, j);
				}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }

				
        /*
        read vshan-RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */		
		
		l.print();
		for(int i = 0; i < 2; i++)
        {
        	l.execute();
			l.print();
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // 3. Cell 20x20
    // ----------

    try {
		freopen ("vshan-RunLife.out", "w", stdout);
        cout << "*** Life<Cell> 20x20 ***" << endl;
		
		ifstream myfile ("vshan-RunLife.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<Cell> l(row, col, new FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

				
        		if(c == '-') //dead Fredkin
        		{
        			l.add(new FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c)) //living Fredkin age below 10
				{
					int cell_age = c - '0';
					l.add(new FredkinCell(cell_age,c), i, j);
				}
				else if(c == '*') //alive Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }

		
        /*
        read vshan-RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		
		l.print();
		for(int i = 0; i < 5; i++)
        {
        	l.execute();
			l.print();
        }
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
		
	//----------------------------------------------------------------------
	// ------------------
    // 4. Conway Cell 8x8
    // ------------------

    try {
		freopen ("vshan-RunLifeConway8x8.out", "w", stdout);
        cout << "*** Life<ConwayCell> 8x8 ***" << endl;
        ifstream myfile ("vshan-RunLifeConway8x8.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<ConwayCell> l(row, col, ConwayCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '*') //alive
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else
        		{
        			//Conway should only be in state dead . or alive *
        			assert(false);
        		}
        	}
        }
        /*
        read vshan-RunLifeConway8x8.in // assume all Conway cells
        Print grid.
        Simulate 5 moves.
        Print grid.
        */

        l.print();

        for(int i = 0; i < 5; i++)
        {
        	l.execute();
			
		}
		l.print();

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ------------------
    // 5. Conway Cell 10x10
    // ------------------

    try {
		freopen ("vshan-RunLifeConway10x10.out", "w", stdout);
        cout << "*** Life<ConwayCell> 10x10 ***" << endl;
        ifstream myfile ("vshan-RunLifeConway10x10.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<ConwayCell> l(row, col, ConwayCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '*') //alive
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead
        		{
        			l.add(ConwayCell(c), i, j);
        		}
        		else
        		{
        			//Conway should only be in state dead . or alive *
        			assert(false);
        		}
        	}
        }
        /*
        read vshan-RunLifeConway10x10.in // assume all Conway cells
        Print grid.
        Simulate 10 moves.
        Print every grid.
        */

        l.print();

        for(int i = 0; i < 10; i++)
        {
        	l.execute();
			l.print();
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
	// ------------------
    // 6. Fredkin Cell 8x8
    // ------------------

    try {
		freopen ("vshan-RunLifeFredkin8x8.out", "w", stdout);
        cout << "*** Life<FredkinCell> 8x8 ***" << endl;
        ifstream myfile ("vshan-RunLifeFredkin8x8.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<FredkinCell> l(row, col, FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '-') //dead
        		{
        			l.add(FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c))
				{
					int cell_age = c - '0';
					l.add(FredkinCell(cell_age,c), i, j);
				}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }
        /*
        read vshan-RunLifeFredkin8x8.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print grid.
        */

        l.print();

        for(int i = 0; i < 5; i++)
        {
        	l.execute();
		}
		l.print();

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ------------------
    // 7. Fredkin Cell 18x18
    // ------------------

    try {
		freopen ("vshan-RunLifeFredkin18x18.out", "w", stdout);
        cout << "*** Life<FredkinCell> 18x18 ***" << endl;
        ifstream myfile ("vshan-RunLifeFredkin18x18.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<FredkinCell> l(row, col, FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;

        		if(c == '-') //dead
        		{
        			l.add(FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c))
				{
					int cell_age = c - '0';
					l.add(FredkinCell(cell_age,c), i, j);
				}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }
        /*
        read vshan-RunLifeFredkin18x18.in // assume all Fredkin cells
        Print grid.
        Simulate 10 moves.
        Print every grid.
        */

        l.print();

        for(int i = 0; i < 10; i++)
        {
        	l.execute();
			l.print();
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // 8. Cell 8x8
    // ----------

    try {
		freopen ("vshan-RunLife8x8.out", "w", stdout);
        cout << "*** Life<Cell> 8x8 ***" << endl;
		
		ifstream myfile ("vshan-RunLife8x8.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<Cell> l(row, col, new FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;
				
        		if(c == '-') //dead Fredkin
        		{
        			l.add(new FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c)) //living Fredkin age below 10
				{
					int cell_age = c - '0';
					l.add(new FredkinCell(cell_age,c), i, j);
				}
				else if(c == '*') //alive Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }
		
        /*
        read vshan-RunLife8x8.in
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		
		l.print();
		for(int i = 0; i < 5; i++)
        {
        	l.execute();
			l.print();
        }
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // 9. Cell 10x10
    // ----------

    try {
		freopen ("vshan-RunLife10x10.out", "w", stdout);
        cout << "*** Life<Cell> 10x10 ***" << endl;
		
		ifstream myfile ("vshan-RunLife10x10.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<Cell> l(row, col, new FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;
				
        		if(c == '-') //dead Fredkin
        		{
        			l.add(new FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c)) //living Fredkin age below 10
				{
					int cell_age = c - '0';
					l.add(new FredkinCell(cell_age,c), i, j);
				}
				else if(c == '*') //alive Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }
		
        /*
        read vshan-RunLife10x10.in
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		
		l.print();
		for(int i = 0; i < 5; i++)
        {
        	l.execute();
			l.print();
        }
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}	
		
	// ----------
    // 10. Cell 20x20
    // ----------

    try {
		freopen ("vshan-RunLife20x20.out", "w", stdout);
        cout << "*** Life<Cell> 20x20 ***" << endl;
		
		ifstream myfile ("vshan-RunLife20x20.in");
        int row;
        int col;
        myfile >> row >> col;
        Life<Cell> l(row, col, new FredkinCell());
        for(int i = 0; i < row; i++) {
        	for(int j = 0; j < col; j++) {
        		char c = '0';
        		myfile >> c;
				
        		if(c == '-') //dead Fredkin
        		{
        			l.add(new FredkinCell(0, c), i, j);
        		}
        		else if(isdigit(c)) //living Fredkin age below 10
				{
					int cell_age = c - '0';
					l.add(new FredkinCell(cell_age,c), i, j);
				}
				else if(c == '*') //alive Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
        		else if(c == '.') //dead Conway
        		{
        			l.add(new ConwayCell(c), i, j);
        		}
				else
        		{
        			//Fredkin should only be in state dead - or alive with some age 0-9
					//Vague ages of + are assumed not to be encountered in input
        			assert(false);
        		}
        	}
        }
		
        /*
        read vshan-RunLife20x20.in
        Print grid.
        Simulate 100 moves.
        Print every 10th grid.
        */
		
		l.print();
		for(int i = 1; i <= 100; i++)
        {
        	l.execute();
			
			if(i%10 == 0)
				l.print();
        }
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}	
		
    return 0;}
