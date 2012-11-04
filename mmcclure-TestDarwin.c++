// -----------------------------
// Modeled after
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
//
// Modified for the purpose of CS371P Project #5
// Matthew McClure
// -----------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin
    % valgrind TestDarwin >& TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#undef private
#define private public

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {

    // -----
    // Species class constructor
    // -----

    void test_Species1 () {
        try {
            Grid::Species s = Grid::Species(NULL);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Species2 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            CPPUNIT_ASSERT(s._program.size() == 0);
            CPPUNIT_ASSERT(s._name.compare("NAME") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Species3 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            s.add(CONTROL_GOTO, 0);
            CPPUNIT_ASSERT(s._program.size() == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    // -----
    // Species add expression
    // -----
    
    void test_SpeciesAdd1 () {
        try {
            Grid::Species s = Grid::Species(".");
            s.add(ACTION_HOP, 0);
            s.add(MAX_INSTRUCTIONS, 0);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_SpeciesAdd2 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            s.add(ACTION_HOP, 0);
            s.add(ACTION_TURN_LEFT, 0);
            s.add(ACTION_TURN_RIGHT, 0);
            s.add(ACTION_INFECT, 0);
            s.add(CONTROL_IF_EMPTY, 0);
            s.add(CONTROL_IF_WALL, 0);
            s.add(CONTROL_IF_RANDOM, 0);
            s.add(CONTROL_IF_ENEMY, 0);
            s.add(CONTROL_GOTO, 0);
            CPPUNIT_ASSERT(s._program.size() == 9);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_SpeciesAdd3 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            s.add(CONTROL_GOTO, 0);
            CPPUNIT_ASSERT(s._program.size() == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    // -----
    // Species reset expression
    // -----
    
    void test_SpeciesReset1 () {
        try {
            Grid::Species s = Grid::Species(".");
            s.add(ACTION_HOP, 0);
            s.reset();
            CPPUNIT_ASSERT(s._program.size() == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_SpeciesReset2 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            s.add(ACTION_HOP, 0);
            s.add(ACTION_TURN_LEFT, 0);
            s.add(ACTION_TURN_RIGHT, 0);
            s.add(ACTION_INFECT, 0);
            s.add(CONTROL_IF_EMPTY, 0);
            s.add(CONTROL_IF_WALL, 0);
            s.add(CONTROL_IF_RANDOM, 0);
            s.add(CONTROL_IF_ENEMY, 0);
            s.reset();
            s.add(CONTROL_GOTO, 0);
            CPPUNIT_ASSERT(s._program.size() == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_SpeciesReset3 () {
        try {
            Grid::Species s = Grid::Species("NAME");
            s.add(CONTROL_GOTO, 0);
            s.reset();
            CPPUNIT_ASSERT(s._program.size() == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // Creature class constructor
    // -----
    
    void test_Creature1 () {
        try {
            Grid::Creature c = Grid::Creature(100);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Creature2 () {
        try {
            Grid::Creature c = Grid::Creature(NO_SPECIES);
            CPPUNIT_ASSERT(c._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Creature3 () {
        try {
            Grid::Creature c = Grid::Creature(NO_SPECIES, NORTH, 1);
            CPPUNIT_ASSERT(c._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(c._orientation == NORTH);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // World class constructor
    // -----
    
    void test_World1 () {
        try {
            Grid::World w = Grid::World(100, 100);
            CPPUNIT_ASSERT(true);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_World2 () {
        try {
            Grid::World w = Grid::World(10, 10, Grid::Creature(NO_SPECIES));
            CPPUNIT_ASSERT(w._m[0][0]._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_World3 () {
        try {
            Grid::World w = Grid::World(2, 2, Grid::Creature(FOOD));
            CPPUNIT_ASSERT(w._m[0][0]._speciesID == FOOD);
            CPPUNIT_ASSERT(w._m[0][1]._speciesID == FOOD);
            CPPUNIT_ASSERT(w._m[1][0]._speciesID == FOOD);
            CPPUNIT_ASSERT(w._m[1][1]._speciesID == FOOD);            
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // Grid
    // -----
    
    void test_Grid1 () {
        try {
            Grid s = Grid(0, 0);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Grid2 () {
        try {
            Grid s = Grid(2, 2);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][0]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][1]._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_Grid3 () {
        try {
            Grid s = Grid(1, 2);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // Grid Place
    // -----
    
    void test_GridPlace1 () {
        try {
            Grid s = Grid(1, 1);
            s.place(FOOD, 'n', 2, 2);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(true);
        }}
    
    void test_GridPlace2 () {
        try {
            Grid s = Grid(2, 2);
            s.place(FOOD, 'w', 0, 0);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == FOOD);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][0]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][1]._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_GridPlace3 () {
        try {
            Grid s = Grid(1, 2);
            s.place(FOOD,  'w', 0, 0);
            s.place(ROVER, 'n', 0, 0);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // Grid RandPlace
    // -----
    
    void test_GridRandPlace1 () {
        try {
            Grid s = Grid(1, 1);
            s.randPlace(FOOD, 2);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(true);
        }}
    
    void test_GridRandPlace2 () {
        try {
            Grid s = Grid(2, 2);
            s.randPlace(FOOD, 4);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == FOOD);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == FOOD);
            CPPUNIT_ASSERT(s._world._m[1][0]._speciesID == FOOD);
            CPPUNIT_ASSERT(s._world._m[1][1]._speciesID == FOOD);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_GridRandPlace3 () {
        try {
            Grid s = Grid(1, 2);
            s.randPlace(100, 2);
            CPPUNIT_ASSERT(false);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(true);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    // -----
    // Grid Simulate
    // -----
    
    void test_GridSimulate1 () {
        try {
            Grid s = Grid(1, 1);
            s.randPlace(FOOD, 1);
            s.simulate(3, 1);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == FOOD);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_GridSimulate2 () {
        try {
            Grid s = Grid(2, 2);
            s.place(FOOD,  'n', 0, 0);
            s.place(ROVER, 'w', 0, 1);
            s.simulate(1, 1);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == ROVER);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == ROVER);
            CPPUNIT_ASSERT(s._world._m[1][0]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][1]._speciesID == NO_SPECIES);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_GridSimulate3 () {
        try {
            Grid s = Grid(2, 2);
            s.place(HOPPER, 's', 0, 0);
            s.place(ROVER,  'w', 0, 1);
            s.simulate(1, 1);
            CPPUNIT_ASSERT(s._world._m[0][0]._speciesID == ROVER);
            CPPUNIT_ASSERT(s._world._m[0][1]._speciesID == NO_SPECIES);
            CPPUNIT_ASSERT(s._world._m[1][0]._speciesID == HOPPER);
            CPPUNIT_ASSERT(s._world._m[1][1]._speciesID == NO_SPECIES);            
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);

    CPPUNIT_TEST(test_Species1);
    CPPUNIT_TEST(test_Species2);
    CPPUNIT_TEST(test_Species3);
    
    CPPUNIT_TEST(test_SpeciesAdd1);
    CPPUNIT_TEST(test_SpeciesAdd2);
    CPPUNIT_TEST(test_SpeciesAdd3);

    CPPUNIT_TEST(test_SpeciesReset1);
    CPPUNIT_TEST(test_SpeciesReset2);
    CPPUNIT_TEST(test_SpeciesReset3);

    CPPUNIT_TEST(test_Creature1);
    CPPUNIT_TEST(test_Creature2);
    CPPUNIT_TEST(test_Creature3);
    
    CPPUNIT_TEST(test_World1);
    CPPUNIT_TEST(test_World2);
    CPPUNIT_TEST(test_World3);

    CPPUNIT_TEST(test_Grid1);
    CPPUNIT_TEST(test_Grid2);
    CPPUNIT_TEST(test_Grid3);
    
    CPPUNIT_TEST(test_GridPlace1);
    CPPUNIT_TEST(test_GridPlace2);
    CPPUNIT_TEST(test_GridPlace3);
    
    CPPUNIT_TEST(test_GridRandPlace1);
    CPPUNIT_TEST(test_GridRandPlace2);
    CPPUNIT_TEST(test_GridRandPlace3);
    
    CPPUNIT_TEST(test_GridSimulate1);
    CPPUNIT_TEST(test_GridSimulate2);
    CPPUNIT_TEST(test_GridSimulate3);
    
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
