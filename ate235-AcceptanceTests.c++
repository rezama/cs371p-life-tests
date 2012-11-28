/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall ate235-AcceptanceTests.c++ -o ate235-AcceptanceTests.c++.app
    % valgrind ate235-AcceptanceTests.c++.app >& ate235-AcceptanceTests.out
*/
// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Acceptance Tests
    // ------------------

	
	
	//---------
	//Conway5x5
	//---------
	
    try {
        cout << "*** Life<ConwayCell> 5x5 ***" << endl;
		Life<ConwayCell> life("ate235-RunConway5x5.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//---------
	//Conway10x10
	//---------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<ConwayCell> 10x10 ***" << endl;
		Life<ConwayCell> life("ate235-RunConway10x10.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//-------------
	//Conway10x10_2
	//-------------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<ConwayCell> 10x10_2 ***" << endl;
		Life<ConwayCell> life("ate235-RunConway10x10_2.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	
	//-----------
	//Conway20x10
	//-----------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<ConwayCell> 20x10 ***" << endl;
		Life<ConwayCell> life("ate235-RunConway20x10.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//----------
	//Fredkin5x5
	//----------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<FredkinCell> 5x5 ***" << endl;
		Life<FredkinCell> life("ate235-RunFredkin5x5.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//------------
	//Fredkin25x25
	//------------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<FredkinCell> 25x25 ***" << endl;
		Life<FredkinCell> life("ate235-RunFredkin25x25.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//------------
	//Fredkin50x25
	//------------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<FredkinCell> 50x25 ***" << endl;
		Life<FredkinCell> life("ate235-RunFredkin50x25.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	
	//--------------
	//Fredkin100x100
	//--------------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<FredkinCell> 100x100 ***" << endl;
		Life<FredkinCell> life("ate235-RunFredkin100x100.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
	//--------
	//Cell 5X5
	//--------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<Cell> 5X5 ***" << endl;
		Life<Cell> life("ate235-RunLife5X5.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
			
	//----------
	//Cell 25x25
	//----------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<Cell> 25x25 ***" << endl;
		Life<Cell> life("ate235-RunLife25x25.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}
	
			
	//------------
	//Cell 100x100
	//------------
	
    try {
		cout << "\n" << endl;
        cout << "*** Life<Cell> 100x100 ***" << endl;
		Life<Cell> life("ate235-RunLife100x100.in");
		life.print();
		life.simulate(5, true);

    }
    catch (const invalid_argument&) {
        assert(false);
	}
    catch (const out_of_range&) {
        assert(false);
	}

    return 0;
}
