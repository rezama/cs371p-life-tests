// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

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
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <fstream>
#include <sstream> //istringstream
#include <stdexcept> // invalid_argument, out_of_range
#include <string>

#include "Darwin.h"
// ----
// main
// ----

void aux_program();

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ---------------
    // best proposals:
    // ---------------

    /* Copy of Rover
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    /* slight change of Rover
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: right
     4: go 0
     5: left
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    /* Messes up RNG a bit but doesn't depend on randomization
     0: if_enemy 8
     1: if_empty 5
     2: if_random 2
     3: right
     4: go 0
     5: if_random 5
     6: hop
     7: go 0
     8: if_random 8
     9: infect
     10: go 0
    */


    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        string setup = "5 1\n8 8\n";
        setup += "f 2 0 0\n";
        setup += "h 1 3 3\n";
        setup += "h 2 3 4\n";
        setup += "h 3 4 4\n";
        setup += "h 0 4 3\n";
        setup += "f 1 7 7\n";
	setup += "END\n";
        
        istringstream file(setup);
        Darwin darwin(file);
	darwin.simulate(cout);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */ 
	srand(0);
	string setup = "5 1\n7 9\n";
	setup += "t 3 0 0\n";
	setup += "h 2 3 2\n";
	setup += "r 1 5 4\n";
	setup += "t 0 6 8\n";
	setup += "END\n";
        
        istringstream file(setup);
        Darwin darwin(file);
	darwin.simulate(cout);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */

	string setup = "1000 100\n72 72\n";
        setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n";
	setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n";
	setup += "f -1\n"; setup += "f -1\n";
        setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n";
        setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n";
        setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n";
	setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n";
	setup += "t -1\n"; setup += "t -1\n";
	setup += "END\n";

        istringstream file(setup);
        Darwin darwin(file);
	darwin.simulate(cout);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */

	string setup = "1000 100\n72 72\n";
        setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n";
	setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n"; setup += "f -1\n";
	setup += "f -1\n"; setup += "f -1\n";
        setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n"; setup += "h -1\n"; setup += "h -1\n";
	setup += "h -1\n";
        setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n"; setup += "r -1\n"; setup += "r -1\n";
	setup += "r -1\n";
        setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n";
	setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n"; setup += "t -1\n";
	setup += "t -1\n"; setup += "t -1\n";
	setup += "b -1\n"; setup += "b -1\n"; setup += "b -1\n"; setup += "b -1\n";
	setup += "b -1\n"; setup += "b -1\n"; setup += "b -1\n"; setup += "b -1\n";
	setup += "b -1\n"; setup += "b -1\n";
	setup += "END\n";
        
        istringstream file(setup);
        Darwin darwin(file);
	darwin.simulate(cout);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	aux_program();
    return 0;}


void aux_program() {
	ifstream file;
	ofstream out;
	try {
		cout << "*** Darwin 72x72 with Best ***" << endl;
		srand(0);     
		file.open ("RunDarwin.in");
		Darwin darwin(file, true);
		out.open("RunDarwinComp.out");
		darwin.simulate(cout);
		out.close();
		file.close(); 
  } catch (const invalid_argument&) {
  		out.close();
			file.close();
      assert(false);
  } catch (const out_of_range&) {
  		out.close();
			file.close();
      assert(false);
  }
  
}
