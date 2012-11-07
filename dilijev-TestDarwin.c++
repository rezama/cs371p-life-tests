/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------
#include <stdexcept>
#include <cstdlib>                            // srand
#include <string>
#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TestRunner
#include "./Darwin.h"

using namespace std;

#define ASSERT(b) CPPUNIT_ASSERT(b)

Species makeFood() {
    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
     */
    Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");

    return food;
}

Species makeHopper() {
    // ------
    // hopper
    // ------
    /*
     0: hop
     1: go 0
     */
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    return hopper;
}

Species makeTrap() {
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
    Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    return trap;
}

Species makeRover() {
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
    Species rover("rover");
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop ");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

    return rover;
}

// --------------
// TestCoordinate
// --------------

struct TestCoordinate : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_ctor_1() {
        Coordinate c;
        ASSERT(c.row == 0);
        ASSERT(c.col == 0);
    }

    /**
     * One-argument ctor via default param for row.
     */
    void test_ctor_2() {
        Coordinate c(8);
        ASSERT(c.row == 8);
        ASSERT(c.col == 0);
    }

    /**
     * Two-argument ctor.
     */
    void test_ctor_3() {
        Coordinate c(2, 3);
        ASSERT(c.row == 2);
        ASSERT(c.col == 3);
    }

    /**
     * Test implicit type conversion.
     */
    void test_ctor_4() {
        Coordinate c = 4;
        ASSERT(c.row == 4);
        ASSERT(c.col == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCoordinate);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);
        CPPUNIT_TEST(test_ctor_4);
    CPPUNIT_TEST_SUITE_END();
};

// -----------
// TestSpecies
// -----------

struct TestSpecies : CppUnit::TestFixture {
    // ------------------------
    // test_constructor_name_id
    // ------------------------

    /**
     * Do some basic tests on the things that the constructor sets up.
     */
    void test_ctor_name_id_1() {
        Species::resetIdCounter();

        Species s("test");
        ASSERT(s.getId() == 1);
        ASSERT(s.getName() == "test");
        try {
            s.getInstruction(0);
            ASSERT(false);
        } catch (out_of_range &e) {
            ASSERT(true);
        }

        Creature c(s);
        ASSERT(c.getIdCharacter() == 't');
    }

    /**
     * Check for case-sensitive name to ID character.
     */
    void test_ctor_name_id_2() {
        Species::resetIdCounter();

        Species s("TEST");
        ASSERT(s.getId() == 1);
        ASSERT(s.getName() == "TEST");
        try {
            s.getInstruction(0);
            ASSERT(false);
        } catch (out_of_range &e) {
            ASSERT(true);
        }

        Creature c(s);
        ASSERT(c.getIdCharacter() == 'T');
    }

    /**
     * Check static ID increment in constructor.
     */
    void test_ctor_name_id_3() {
        Species::resetIdCounter();

        Species test("TEST");
        Species hello("Hello");
        ASSERT(test.getId() == 1);
        ASSERT(hello.getId() == 2);

        ASSERT(test.getName() == "TEST");
        ASSERT(hello.getName() == "Hello");
    }

    /**
     * Test that the destruction of a species doesn't change the sequential
     * selection of species unique ID.
     */
    void test_ctor_name_id_4() {
        Species::resetIdCounter();

        Species a("a");
        ASSERT(a.getId() == 1);

        {
            Species b("b");
            ASSERT(b.getId() == 2);
            Species c("c");
            ASSERT(c.getId() == 3);
        }

        Species b("b");
        ASSERT(b.getId() == 4);
        Species c("c");
        ASSERT(c.getId() == 5);
    }

    /**
     * Test implicit type conversion.
     */
    void test_ctor_name_id_5() {
        Species::resetIdCounter();

        Species a = string("a");
        ASSERT(a.getId() == 1);
        ASSERT(a.getName() == "a");
    }

    // ----------------------
    // test_addGetInstruction
    // ----------------------

    void test_addGetInstruction_1() {
        Species s("test");
        s.addInstruction("hop");
        ASSERT(s.getInstruction(0) == "hop");
    }

    /**
     * Check rejection of bad instruction.
     */
    void test_addGetInstruction_2() {
        Species s("test");

        try {
            s.addInstruction("stop");
            ASSERT(false);
        } catch (invalid_argument &e) {
            ASSERT(true);
        }
    }

    /**
     * Check recall in a sequence.
     */
    void test_addGetInstruction_3() {
        Species s("test");
        s.addInstruction("hop");
        s.addInstruction("right");
        s.addInstruction("left");
        s.addInstruction("go 0");

        ASSERT(s.getInstruction(0) == "hop");
        ASSERT(s.getInstruction(1) == "right");
        ASSERT(s.getInstruction(2) == "left");
        ASSERT(s.getInstruction(3) == "go 0");
    }

    /**
     * Check throwing exception when trying to access out of program range.
     */
    void test_addGetInstruction_4() {
        Species s("test");
        s.addInstruction("hop");
        s.addInstruction("right");
        s.addInstruction("left");
        s.addInstruction("go 0");

        ASSERT(s.getInstruction(0) == "hop");
        ASSERT(s.getInstruction(1) == "right");
        ASSERT(s.getInstruction(2) == "left");
        ASSERT(s.getInstruction(3) == "go 0");

        try {
            s.getInstruction(4);
            ASSERT(false);
        } catch (out_of_range &e) {
            ASSERT(true);
        }
    }

    // -------------------
    // test_resetIdCounter
    // -------------------

    /**
     * Test sequence post reset.
     */
    void test_resetIdCounter_1() {
        Species::resetIdCounter();

        Species a("a");
        ASSERT(a.getId() == 1);

        Species b("b");
        ASSERT(b.getId() == 2);
        Species c("c");
        ASSERT(c.getId() == 3);

        Species d("d");
        ASSERT(d.getId() == 4);
        Species e("e");
        ASSERT(e.getId() == 5);
    }

    /**
     * Test sequence post reset with destructed Species.
     */
    void test_resetIdCounter_2() {
        Species::resetIdCounter();

        Species a("a");
        ASSERT(a.getId() == 1);

        {
            Species b("b");
            ASSERT(b.getId() == 2);
            Species c("c");
            ASSERT(c.getId() == 3);
        }

        Species b("b");
        ASSERT(b.getId() == 4);
        Species c("c");
        ASSERT(c.getId() == 5);
    }

    /**
     * Test constructing species interleaved with reset.
     */
    void test_resetIdCounter_3() {
        Species::resetIdCounter();

        Species a("a");
        ASSERT(a.getId() == 1);

        Species b("b");
        ASSERT(b.getId() == 2);
        Species c("c");
        ASSERT(c.getId() == 3);

        Species::resetIdCounter();

        Species d("d");
        ASSERT(d.getId() == 1);
        Species e("e");
        ASSERT(e.getId() == 2);
    }

    /**
     * Serial calls to reset.
     */
    void test_resetIdCounter_4() {
        Species::resetIdCounter();
        Species::resetIdCounter();

        Species a("a");
        ASSERT(a.getId() == 1);

        Species::resetIdCounter();

        Species b("b");
        ASSERT(b.getId() == 1);
        Species c("c");
        ASSERT(c.getId() == 2);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSpecies);
        CPPUNIT_TEST(test_ctor_name_id_1);
        CPPUNIT_TEST(test_ctor_name_id_2);
        CPPUNIT_TEST(test_ctor_name_id_3);
        CPPUNIT_TEST(test_ctor_name_id_4);
        CPPUNIT_TEST(test_ctor_name_id_5);

        CPPUNIT_TEST(test_addGetInstruction_1);
        CPPUNIT_TEST(test_addGetInstruction_2);
        CPPUNIT_TEST(test_addGetInstruction_3);
        CPPUNIT_TEST(test_addGetInstruction_4);

        CPPUNIT_TEST(test_resetIdCounter_1);
        CPPUNIT_TEST(test_resetIdCounter_2);
        CPPUNIT_TEST(test_resetIdCounter_3);
        CPPUNIT_TEST(test_resetIdCounter_4);
    CPPUNIT_TEST_SUITE_END();
};

// ---------
// TestWorld
// ---------

struct TestCreature : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    /** Default constructor. */
    void test_ctor_1() {
        Creature c;
        ASSERT(!c.hasValidSpecies());
        ASSERT(c.getIdCharacter() == '.');
        ASSERT(c.hasSameSpecies(Creature()));
    }

    /** One argument constructor. */
    void test_ctor_2() {
        Species s = makeFood();
        Creature c(s);  // should be NORTH

        ASSERT(c.hasValidSpecies());
        ASSERT(c.getIdCharacter() == 'f');
        ASSERT(c.hasSameSpecies(Creature(s)));

        Coordinate aa(1, 1);
        Coordinate bb(0, 1);

        Coordinate ahead = c.getLocationAhead(aa, 5, 5);
        ASSERT(ahead.row == bb.row);
        ASSERT(ahead.col == bb.col);
    }

    /** Two argument constructor. */
    void test_ctor_3() {
        Species s = makeFood();
        Creature c(s, EAST);

        ASSERT(c.hasValidSpecies());
        ASSERT(c.getIdCharacter() == 'f');
        ASSERT(c.hasSameSpecies(Creature(s)));

        Coordinate aa(1, 1);
        Coordinate bb(1, 2);

        Coordinate ahead = c.getLocationAhead(aa, 5, 5);
        ASSERT(ahead.row == bb.row);
        ASSERT(ahead.col == bb.col);
    }

    // ---------------------
    // test_getLocationAhead
    // ---------------------

    /** Test for when there is no bounding grid. */
    void test_getLocationAhead_1() {
        Species s = makeFood();
        Creature c(s, SOUTH);

        Coordinate aa(1, 1);
        Coordinate bb(2, 1);

        Coordinate ahead = c.getLocationAhead(aa);

        ASSERT(ahead.row == bb.row);
        ASSERT(ahead.col == bb.col);
    }

    /** Test for when there is no bounding grid. */
    void test_getLocationAhead_2() {
        Species s = makeFood();
        Creature c(s, NORTH);

        Coordinate aa(0, 0);
        Coordinate bb(-1, 0);

        Coordinate ahead = c.getLocationAhead(aa);

        ASSERT(ahead.row == bb.row);
        ASSERT(ahead.col == bb.col);
    }

    /** Test for when the given coordinate is within the grid. */
    void test_getLocationAhead_3() {
        Species s = makeFood();
        Creature c(s, WEST);

        Coordinate aa(2, 2);
        Coordinate bb(2, 1);

        Coordinate ahead = c.getLocationAhead(aa, 5, 5);

        ASSERT(ahead.row == bb.row);
        ASSERT(ahead.col == bb.col);
    }

    /** Test for when the given coordinate is outside the grid. */
    void test_getLocationAhead_4() {
        Species s = makeFood();
        Creature c(s, WEST);

        Coordinate aa(5, 5);
        Coordinate bb(5, 4);

        try {
            Coordinate ahead = c.getLocationAhead(aa, 3, 3);
            ASSERT(false);
        } catch(out_of_range& e) {
            ASSERT(true);
        }
    }

    // -------------------
    // test_getIdCharacter
    // -------------------

    void test_getIdCharacter_1() {
        Creature c;
        ASSERT(c.getIdCharacter() == '.');
    }

    void test_getIdCharacter_2() {
        Species s = makeFood();
        Creature c(s);
        ASSERT(c.getIdCharacter() == 'f');
    }

    void test_getIdCharacter_3() {
        Species s("HELLO");
        Creature c(s);
        ASSERT(c.getIdCharacter() == 'H');
    }

    // ----------------------
    // test_isFacingDirection
    // ----------------------

    void test_isFacingDirection_1() {
        Creature c;
        ASSERT(c.isFacingDirection(NORTH));
    }

    void test_isFacingDirection_2() {
        Species s = makeFood();
        Creature c(s);
        ASSERT(c.isFacingDirection(NORTH));
    }

    void test_isFacingDirection_3() {
        Species s = makeFood();
        Creature c(s, EAST);
        ASSERT(c.isFacingDirection(EAST));
    }

    // --------------------
    // test_hasValidSpecies
    // --------------------

    void test_hasValidSpecies_1() {
        Creature c;
        ASSERT(!c.hasValidSpecies());
    }

    void test_hasValidSpecies_2() {
        Species s = makeFood();
        Creature c(s);
        ASSERT(c.hasValidSpecies());
    }

    void test_hasValidSpecies_3() {
        Species s = makeFood();
        Creature c(s, EAST);
        ASSERT(c.hasValidSpecies());
    }

    // -------------------
    // test_hasSameSpecies
    // -------------------

    void test_hasSameSpecies_1() {
        Creature c;
        ASSERT(c.hasSameSpecies(Creature()));
    }

    void test_hasSameSpecies_2() {
        Species s = makeFood();
        Creature c(s);
        ASSERT(c.hasSameSpecies(Creature(s)));
    }

    void test_hasSameSpecies_3() {
        Species s = makeRover();
        Creature c(s, EAST);
        ASSERT(!c.hasSameSpecies(Creature(makeRover())));
    }

    void test_hasSameSpecies_4() {
        Species s = makeRover();
        Species r = makeFood();
        Creature c(s, EAST);
        Creature d(r, SOUTH);
        ASSERT(!c.hasSameSpecies(Creature(d)));
    }

    // -----------------
    // test_act_and_turn
    // -----------------

    void test_act_and_turn_1() {
        Species food = makeFood();
        Creature c(food);

        Coordinate aa(3, 3);

        ASSERT(c.turnMatches(0));

        Coordinate next = c.act(aa, false);
        ASSERT(next.row == aa.row);
        ASSERT(next.col == aa.col);

        ASSERT(c.turnMatches(1));
    }

    void test_act_and_turn_2() {
        Species food = makeFood();
        Creature c(food);

        Coordinate aa(3, 3);

        ASSERT(c.turnMatches(0));

        Coordinate next = c.act(aa, true);
        ASSERT(next.row == aa.row);
        ASSERT(next.col == aa.col);

        ASSERT(c.turnMatches(1));
    }

    void test_act_and_turn_3() {
        Species s = makeHopper();
        Creature c(s);

        Coordinate aa(3, 3);
        Coordinate bb(2, 3);

        ASSERT(c.turnMatches(0));

        Coordinate next = c.act(aa, false);
        ASSERT(next.row == bb.row);
        ASSERT(next.col == bb.col);

        ASSERT(c.turnMatches(1));
    }

    void test_act_and_turn_4() {
        Species s = makeHopper();
        Creature c(s);

        Coordinate aa(3, 3);

        ASSERT(c.turnMatches(0));

        Coordinate next = c.act(aa, true);
        ASSERT(next.row == aa.row);
        ASSERT(next.col == aa.col);

        ASSERT(c.turnMatches(1));
    }

    void test_act_and_turn_5() {
        Species s = makeHopper();
        Species r = makeTrap();
        Creature c(s);
        Creature d(s);

        Coordinate aa(3, 3);

        ASSERT(c.turnMatches(0));
        ASSERT(d.turnMatches(0));

        c.act(aa, true);

        ASSERT(c.turnMatches(1));
        ASSERT(d.turnMatches(0));
    }

    void test_act_and_turn_6() {
        Species s = makeHopper();
        Creature c(s);
        Creature d(s);

        Coordinate aa(3, 3);

        ASSERT(c.turnMatches(0));

        Coordinate next = c.act(aa, d, false);
        ASSERT(next.row == aa.row);
        ASSERT(next.col == aa.col);

        ASSERT(c.turnMatches(1));
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCreature);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);
        CPPUNIT_TEST(test_getLocationAhead_1);
        CPPUNIT_TEST(test_getLocationAhead_2);
        CPPUNIT_TEST(test_getLocationAhead_3);
        CPPUNIT_TEST(test_getLocationAhead_4);
        CPPUNIT_TEST(test_getIdCharacter_1);
        CPPUNIT_TEST(test_getIdCharacter_2);
        CPPUNIT_TEST(test_getIdCharacter_3);
        CPPUNIT_TEST(test_isFacingDirection_1);
        CPPUNIT_TEST(test_isFacingDirection_2);
        CPPUNIT_TEST(test_isFacingDirection_3);
        CPPUNIT_TEST(test_hasValidSpecies_1);
        CPPUNIT_TEST(test_hasValidSpecies_2);
        CPPUNIT_TEST(test_hasValidSpecies_3);
        CPPUNIT_TEST(test_hasSameSpecies_1);
        CPPUNIT_TEST(test_hasSameSpecies_2);
        CPPUNIT_TEST(test_hasSameSpecies_3);
        CPPUNIT_TEST(test_hasSameSpecies_4);
        CPPUNIT_TEST(test_act_and_turn_1);
        CPPUNIT_TEST(test_act_and_turn_2);
        CPPUNIT_TEST(test_act_and_turn_3);
        CPPUNIT_TEST(test_act_and_turn_4);
        CPPUNIT_TEST(test_act_and_turn_5);
        CPPUNIT_TEST(test_act_and_turn_6);
    CPPUNIT_TEST_SUITE_END();
};

// ---------
// TestWorld
// ---------

struct TestWorld : CppUnit::TestFixture {
    // ------------------------
    // test_constructor_display
    // ------------------------

    /**
     * Default constructor.
     */
    void test_ctor_display_1() {
        World w;
        ostringstream str(ostringstream::out);

        ASSERT(w.getNumRows() == 1);
        ASSERT(w.getNumCols() == 1);

        w.display(str);

        string expected = "Turn = 0.\n"
                "  0\n"
                "0 .\n\n";
        ASSERT(str.str() == expected);
    }

    /**
     * One-argument ctor via default param for row.
     */
    void test_ctor_display_2() {
        World w(3);
        ostringstream str(ostringstream::out);

        ASSERT(w.getNumRows() == 3);
        ASSERT(w.getNumCols() == 1);

        w.display(str);

        string expected = "Turn = 0.\n"
                "  0\n"
                "0 .\n"
                "1 .\n"
                "2 .\n\n";
        ASSERT(str.str() == expected);
    }

    /**
     * Implicit type conversion.
     */
    void test_ctor_display_3() {
        World w = 3;
        ostringstream str(ostringstream::out);

        ASSERT(w.getNumRows() == 3);
        ASSERT(w.getNumCols() == 1);

        w.display(str);

        string expected = "Turn = 0.\n"
                "  0\n"
                "0 .\n"
                "1 .\n"
                "2 .\n\n";
        ASSERT(str.str() == expected);
    }

    /**
     * Two-argument constructor.
     */
    void test_ctor_display_4() {
        World w(2, 2);
        ostringstream str(ostringstream::out);

        ASSERT(w.getNumRows() == 2);
        ASSERT(w.getNumCols() == 2);

        w.display(str);

        string expected = "Turn = 0.\n"
                "  01\n"
                "0 ..\n"
                "1 ..\n\n";
        ASSERT(str.str() == expected);
    }

    // -------------------
    // test_ctor_rows_cols
    // -------------------

    void test_ctor_rows_cols_1() {
        World w;
        ASSERT(w.getNumRows() == 1);
        ASSERT(w.getNumCols() == 1);
    }

    void test_ctor_rows_cols_2() {
        World w(5);
        ASSERT(w.getNumRows() == 5);
        ASSERT(w.getNumCols() == 1);
    }

    void test_ctor_rows_cols_3() {
        World w(2, 5);
        ASSERT(w.getNumRows() == 2);
        ASSERT(w.getNumCols() == 5);
    }

    // ----------------
    // test_addCreature
    // ----------------

    void test_addCreature_1() {
        World w;
        Species food = makeFood();
        Creature c(food);
        Coordinate loc(0, 0);

        w.addCreature(loc, c);

        ostringstream str(ostringstream::out);
        w.display(str);

        string expected = "Turn = 0.\n"
                "  0\n"
                "0 f\n\n";
        ASSERT(str.str() == expected);

        ASSERT(w.getGrid(loc).hasSameSpecies(Creature(food)));
    }

    void test_addCreature_2() {
        World w(2, 2);
        Species food = makeFood();
        Species trap = makeTrap();
        Creature a(food);
        Coordinate aa(0, 1);
        Creature b(trap);
        Coordinate bb(1, 1);

        w.addCreature(aa, a);
        w.addCreature(bb, b);

        ostringstream str(ostringstream::out);
        w.display(str);

        string expected = "Turn = 0.\n"
                "  01\n"
                "0 .f\n"
                "1 .t\n\n";
        ASSERT(str.str() == expected);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature(trap)));
    }

    /**
     * Check for error if trying to add outside the grid range.
     */
    void test_addCreature_3() {
        World w;
        Species food = makeFood();
        Creature c(food);
        Coordinate loc(3, 3);

        try {
            w.addCreature(loc, c);
            ASSERT(false);
        } catch (out_of_range &e) {
            ASSERT(true);
        }
    }

    // ------------
    // test_getGrid
    // ------------

    void test_getGrid_1() {
        World w;
        ASSERT(w.getGrid(Coordinate(0, 0)).hasSameSpecies(Creature()));
    }

    void test_getGrid_2() {
        World w(2, 2);
        Species food = makeFood();
        Species trap = makeTrap();
        Creature a(food);
        Coordinate aa(0, 1);
        Creature b(trap);
        Coordinate bb(1, 1);

        w.addCreature(aa, a);
        w.addCreature(bb, b);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(Coordinate(0, 0)).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(Coordinate(1, 0)).hasSameSpecies(Creature()));
    }

    void test_getGrid_3() {
        World w;

        try {
            w.getGrid(Coordinate(1, 1));
            ASSERT(false);
        } catch (out_of_range &e) {
            ASSERT(true);
        }
    }

    // ------------
    // test_execute
    // ------------

    void test_execute_1() {
        World w(2, 1);
        Species hopper = makeHopper();
        Creature c(hopper);
        Coordinate aa(0, 0);
        Coordinate bb(1, 0);

        w.addCreature(bb, c);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature(hopper)));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(hopper)));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature()));
    }

    void test_execute_2() {
        World w(1, 1);
        Species trap = makeTrap();
        Creature c(trap);
        Coordinate aa(0, 0);

        w.addCreature(aa, c);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(aa).isFacingDirection(NORTH));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(aa).isFacingDirection(WEST));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(aa).isFacingDirection(SOUTH));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(aa).isFacingDirection(EAST));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(trap)));
        ASSERT(w.getGrid(aa).isFacingDirection(NORTH));
    }

    void test_execute_3() {
        World w(2, 1);
        Species rover = makeRover();
        Creature c(rover);
        Coordinate aa(0, 0);
        Coordinate bb(1, 0);

        srand(0);

        w.addCreature(bb, c);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature(rover)));
        ASSERT(w.getGrid(bb).isFacingDirection(NORTH));
        ASSERT(w.getGrid(bb).turnMatches(0));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(rover)));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).isFacingDirection(NORTH));
        ASSERT(w.getGrid(aa).turnMatches(1));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(rover)));
        ASSERT(w.getGrid(bb).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).isFacingDirection(EAST));
        ASSERT(w.getGrid(aa).turnMatches(2));
    }

    /**
     * Empty grids' turns never advance.
     */
    void test_execute_4() {
        World w(2, 1);
        Coordinate aa(0, 0);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).turnMatches(0));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).turnMatches(0));

        w.execute(1);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).turnMatches(0));

        w.execute(2);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).turnMatches(0));

        w.execute(10);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature()));
        ASSERT(w.getGrid(aa).turnMatches(0));
    }

    /**
     * Empty grids' turns never advance.
     */
    void test_execute_5() {
        World w(2, 1);
        Species food = makeFood();
        Creature c(food);
        Coordinate aa(0, 0);

        w.addCreature(aa, c);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(aa).turnMatches(0));

        w.execute();

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(aa).turnMatches(1));

        w.execute(1);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(aa).turnMatches(2));

        w.execute(2);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(aa).turnMatches(4));

        w.execute(10);

        ASSERT(w.getGrid(aa).hasSameSpecies(Creature(food)));
        ASSERT(w.getGrid(aa).turnMatches(14));
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestWorld);
        CPPUNIT_TEST(test_ctor_display_1);
        CPPUNIT_TEST(test_ctor_display_2);
        CPPUNIT_TEST(test_ctor_display_3);
        CPPUNIT_TEST(test_ctor_display_4);

        CPPUNIT_TEST(test_ctor_rows_cols_1);
        CPPUNIT_TEST(test_ctor_rows_cols_2);
        CPPUNIT_TEST(test_ctor_rows_cols_3);

        CPPUNIT_TEST(test_addCreature_1);
        CPPUNIT_TEST(test_addCreature_2);
        CPPUNIT_TEST(test_addCreature_3);

        CPPUNIT_TEST(test_getGrid_1);
        CPPUNIT_TEST(test_getGrid_2);
        CPPUNIT_TEST(test_getGrid_3);

        CPPUNIT_TEST(test_execute_1);
        CPPUNIT_TEST(test_execute_2);
        CPPUNIT_TEST(test_execute_3);
        CPPUNIT_TEST(test_execute_4);
        CPPUNIT_TEST(test_execute_5);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;

    try {
        ios_base::sync_with_stdio(false);  // turn off sync with C I/O
        cout << "TestDarwin.c++" << endl;

        CppUnit::TextTestRunner tr;
        tr.addTest(TestCoordinate::suite());
        tr.addTest(TestSpecies::suite());
        tr.addTest(TestCreature::suite());
        tr.addTest(TestWorld::suite());
        tr.run();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    cout << "Done." << endl;
    return 0;
}
