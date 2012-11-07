// ------------------------------
// projects/Darwin/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#define private public
#define protected public
#define class struct
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {

    void test_instruction1 () {

        Instruction inst = Instruction(InstructionType::GO, 0);

        try {
            CPPUNIT_ASSERT(inst.line == 0);
            CPPUNIT_ASSERT(inst.type == InstructionType::GO);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_instruction2 () {

        Instruction inst = Instruction(InstructionType::INFECT);

        try {
            CPPUNIT_ASSERT(inst.line == -1);
            CPPUNIT_ASSERT(inst.type == InstructionType::INFECT);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }


    void test_instruction3 () {

        Instruction inst = Instruction(InstructionType::IF_ENEMY, 9);

        try {
            CPPUNIT_ASSERT(inst.line == 9);
            CPPUNIT_ASSERT(inst.type == InstructionType::IF_ENEMY);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_instruction4 () {

        Instruction inst = Instruction(InstructionType::LEFT);

        try {
            CPPUNIT_ASSERT(inst.line == -1);
            CPPUNIT_ASSERT(inst.type == InstructionType::LEFT);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_instruction5 () {

        Instruction inst = Instruction(InstructionType::RIGHT);

        try {
            CPPUNIT_ASSERT(inst.line == -1);
            CPPUNIT_ASSERT(inst.type == InstructionType::RIGHT);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_species1 () {

        Species specie = Species();

        try {
            CPPUNIT_ASSERT(specie.program.empty());
            CPPUNIT_ASSERT(specie.type == SpeciesType::INVALID);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_species2 () {
        Species specie = Species(SpeciesType::FOOD);

        try {
            CPPUNIT_ASSERT(specie.program.size() == 2);
            CPPUNIT_ASSERT(specie.type == SpeciesType::FOOD);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_species3 () {
        Species specie = Species(SpeciesType::ROVER);

        try {
            CPPUNIT_ASSERT(specie.program.size() == 11);
            CPPUNIT_ASSERT(specie.type == SpeciesType::ROVER);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_generateProgram1 () {
        std::vector<Instruction> program = Species::generateProgram(SpeciesType::ROVER);

        try {
            CPPUNIT_ASSERT(program.size() == 11);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_generateProgram2 () {
        std::vector<Instruction> program = Species::generateProgram(SpeciesType::FOOD);

        try {
            CPPUNIT_ASSERT(program.size() == 2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_generateProgram3 () {
        std::vector<Instruction> program = Species::generateProgram(SpeciesType::INVALID);

        try {
            CPPUNIT_ASSERT(program.empty());
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }


    void test_creature1 () {

        Creature v = Creature();

        try {
            CPPUNIT_ASSERT(v.specie.program.empty());
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == -1);
            CPPUNIT_ASSERT(v.pc == -1);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::INVALID);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_creature2 () {
        Creature v = Creature(0, SpeciesType::FOOD);

        try {
            CPPUNIT_ASSERT(v.specie.program.size() == 2);
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == 0);
            CPPUNIT_ASSERT(v.pc == 0);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::FOOD);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_creature3 () {
        Creature v = Creature(2, SpeciesType::ROVER);

        try {
            CPPUNIT_ASSERT(v.specie.program.size() == 11);
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == 2);
            CPPUNIT_ASSERT(v.pc == 0);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::ROVER);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_invalidate1 () {

        Creature v = Creature(2, SpeciesType::ROVER);

        try {
            CPPUNIT_ASSERT(v.specie.program.size() == 11);
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == 2);
            CPPUNIT_ASSERT(v.pc == 0);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::ROVER);
            v.invalidate();
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::INVALID);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_invalidate2 () {

        Creature v = Creature(2, SpeciesType::FOOD);

        try {
            CPPUNIT_ASSERT(v.specie.program.size() == 2);
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == 2);
            CPPUNIT_ASSERT(v.pc == 0);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::FOOD);
            v.round++;
            v.invalidate();
            v.round++;
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::INVALID);
            CPPUNIT_ASSERT(v.round == 2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_invalidate3 () {

        Creature v = Creature(3, SpeciesType::TRAP);

        try {
            CPPUNIT_ASSERT(v.specie.program.size() == 5);
            CPPUNIT_ASSERT(v.round == 0);
            CPPUNIT_ASSERT(v.dir == 3);
            CPPUNIT_ASSERT(v.pc == 0);
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::TRAP);
            v.round++;
            v.invalidate();
            CPPUNIT_ASSERT(v.specie.type == SpeciesType::INVALID);
            CPPUNIT_ASSERT(v.round == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }


    void test_valid1 () {

        Creature v = Creature();

        try {
            CPPUNIT_ASSERT(!v.valid());
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_valid2 () {
        Creature v = Creature(3, SpeciesType::FOOD);

        try {
            CPPUNIT_ASSERT(v.valid());
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_valid3 () {
        Creature v = Creature(2, SpeciesType::ROVER);

        try {
            CPPUNIT_ASSERT(v.valid());
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_board1 () {

        Controller c = Controller(72, 72);

        try {
            CPPUNIT_ASSERT(c.board.size() == 72);
            CPPUNIT_ASSERT((c.board[0]).size() == 72);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_board2 () {
        Controller c = Controller(7, 9);

        try {
            CPPUNIT_ASSERT(c.board.size() == 7);
            CPPUNIT_ASSERT((c.board[0]).size() == 9);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_board3 () {
        Controller c = Controller(9, 7);

        try {
            CPPUNIT_ASSERT(c.board.size() == 9);
            CPPUNIT_ASSERT((c.board[0]).size() == 7);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_hop1 () {
        Controller c(8, 8);
        c.place(SpeciesType::HOPPER , 0, 0, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            c.start(0);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_hop2 () {
        Controller c(8, 8);
        c.place(SpeciesType::HOPPER , 2, 0, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            c.start(0);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::INVALID);
            CPPUNIT_ASSERT((c.board[0][1]).specie.type == SpeciesType::HOPPER);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_hop3 () {
        Controller c(8, 8);
        c.place(SpeciesType::HOPPER , 3, 0, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            c.start(0);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::INVALID);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::HOPPER);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_infect1 () {
        Controller c(8, 8);
        c.place(SpeciesType::TRAP , 3, 0, 0);
        c.place(SpeciesType::FOOD , 0, 1, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);
            c.start(4);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::TRAP);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_infect2 () {
        Controller c(8, 8);
        c.place(SpeciesType::ROVER , 3, 0, 0);
        c.place(SpeciesType::FOOD , 0, 1, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::ROVER);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);
            c.start(4);
            unsigned count = 0;
            for(unsigned int i = 0; i < c.board.size(); i++)
                for(unsigned int j = 0; j < (c.board[i]).size(); j++)
                    if((c.board[i][j]).specie.type == SpeciesType::ROVER)
                        count++;
            CPPUNIT_ASSERT(count == 2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_infect3 () {
        Controller c(8, 8);
        c.place(SpeciesType::TRAP , 3, 0, 0);
        c.place(SpeciesType::FOOD , 0, 1, 0);
        c.place(SpeciesType::FOOD , 0, 2, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);
            c.start(4);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[2][0]).specie.type == SpeciesType::TRAP);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_execute1 () {
        Controller c = Controller(9, 7);
        c.place(SpeciesType::TRAP , 3, 0, 0);
        c.place(SpeciesType::FOOD , 0, 1, 0);
        const Instruction infect = Instruction(InstructionType::INFECT);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[0][0]).round == 0);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);
            c.execute(infect, c.board[0][0], 0, 0);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[0][0]).round == 1);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::TRAP);

        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_execute2 () {
        Controller c = Controller(9, 7);
        c.place(SpeciesType::HOPPER , 3, 0, 0);
        c.place(SpeciesType::FOOD , 0, 1, 0);
        const Instruction hop = Instruction(InstructionType::HOP);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            CPPUNIT_ASSERT((c.board[0][0]).round == 0);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);
            c.execute(hop, c.board[0][0], 0, 0);
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            CPPUNIT_ASSERT((c.board[0][0]).round == 1);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::FOOD);

        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_execute3 () {
        Controller c = Controller(9, 7);
        c.place(SpeciesType::HOPPER , 3, 0, 0);
        const Instruction hop = Instruction(InstructionType::HOP);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::HOPPER);
            CPPUNIT_ASSERT((c.board[0][0]).round == 0);
            c.execute(hop, c.board[0][0], 0, 0);
            CPPUNIT_ASSERT((c.board[1][0]).specie.type == SpeciesType::HOPPER);
            CPPUNIT_ASSERT((c.board[1][0]).round == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_getFacing1 () {
        Controller c(8, 8);
        std::vector<int> coords = c.getFacing(0, 0, 0);

        try {
            CPPUNIT_ASSERT(coords[0] == -1);
            CPPUNIT_ASSERT(coords[1] == -1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_getFacing2 () {
        Controller c(8, 8);
        std::vector<int> coords = c.getFacing(1, 0, 0);

        try {
            CPPUNIT_ASSERT(coords[0] == -1);
            CPPUNIT_ASSERT(coords[1] == -1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_getFacing3 () {
        Controller c(8, 8);
        std::vector<int> coords = c.getFacing(2, 0, 0);

        try {
            CPPUNIT_ASSERT(coords[0] == 0);
            CPPUNIT_ASSERT(coords[1] == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_getFacing4 () {
        Controller c(8, 8);
        std::vector<int> coords = c.getFacing(3, 0, 0);

        try {
            CPPUNIT_ASSERT(coords[0] == 1);
            CPPUNIT_ASSERT(coords[1] == 0);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToRow1 () {
        Controller c = Controller(9, 7);
        unsigned int loc = (c.board.size() * (c.board[0]).size()) - 1;
        unsigned int row = c.absToRow(loc);
        try {
            CPPUNIT_ASSERT(row == (c.board.size() - 1));
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToRow2 () {
        Controller c = Controller(3, 7);
        unsigned int loc = 6;
        unsigned int row = c.absToRow(loc);
        try {
            CPPUNIT_ASSERT(row == 0);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToRow3 () {
        Controller c = Controller(14, 7);
        unsigned int loc = 13;
        unsigned int row = c.absToRow(loc);
        try {
            CPPUNIT_ASSERT(row == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToCol1 () {
        Controller c = Controller(9, 7);
        unsigned int loc = (c.board.size() * (c.board[0]).size()) - 1;
        unsigned int col = c.absToCol(loc);
        try {
            CPPUNIT_ASSERT(col == (c.board[0]).size() - 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToCol2 () {
        Controller c = Controller(9, 7);
        unsigned int loc = 6;
        unsigned int col = c.absToCol(loc);
        try {
            CPPUNIT_ASSERT(col == 6);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_absToCol3 () {
        Controller c = Controller(9, 7);
        unsigned int loc = 13;
        unsigned int col = c.absToCol(loc);
        try {
            CPPUNIT_ASSERT(col == 6);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_place1 () {
        Controller c(8, 8);
        c.place(SpeciesType::FOOD  , 1, 0, 0);
        try {
            CPPUNIT_ASSERT((c.board[0][0]).specie.type == SpeciesType::FOOD);
            CPPUNIT_ASSERT((c.board[0][0]).dir == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }


    void test_place2 () {
        Controller c(8, 8);
        c.place(SpeciesType::ROVER , 2, 4, 5);
        try {
            CPPUNIT_ASSERT((c.board[4][5]).specie.type == SpeciesType::ROVER);
            CPPUNIT_ASSERT((c.board[4][5]).dir == 2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_place3 () {
        Controller c(8, 8);
        c.place(SpeciesType::TRAP , 0, 5, 2);
        try {
            CPPUNIT_ASSERT((c.board[5][2]).specie.type == SpeciesType::TRAP);
            CPPUNIT_ASSERT((c.board[5][2]).dir == 0);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_place4 () {
        srand(0);
        Controller c(8, 8);
        c.place(SpeciesType::FOOD , 1);
        int count = 0;
        try {
            for(unsigned int i = 0; i < c.board.size(); i++)
                for(unsigned int j = 0; j < (c.board[i]).size(); j++)
                    if((c.board[i][j]).specie.type == SpeciesType::FOOD)
                        ++count;
                    else if((c.board[i][j]).specie.type != SpeciesType::INVALID)
                        CPPUNIT_ASSERT(false);

            CPPUNIT_ASSERT(count == 1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_place5 () {
        srand(0);
        Controller c(8, 8);
        c.place(SpeciesType::ROVER , 2);
        int count = 0;
        try {
            for(unsigned int i = 0; i < c.board.size(); i++)
                for(unsigned int j = 0; j < (c.board[i]).size(); j++)
                    if((c.board[i][j]).specie.type == SpeciesType::ROVER)
                        ++count;
                    else if((c.board[i][j]).specie.type != SpeciesType::INVALID)
                        CPPUNIT_ASSERT(false);

            CPPUNIT_ASSERT(count == 2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_place6 () {
        srand(0);
        Controller c(72, 72);
        c.place(SpeciesType::FOOD, 10);
        c.place(SpeciesType::HOPPER, 10);
        c.place(SpeciesType::ROVER, 10);
        c.place(SpeciesType::TRAP, 10);
        int count = 0;
        try {
            for(unsigned int i = 0; i < c.board.size(); i++)
                for(unsigned int j = 0; j < (c.board[i]).size(); j++)
                    if((c.board[i][j]).specie.type != SpeciesType::INVALID)
                        ++count;

            CPPUNIT_ASSERT(count == 40);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_instruction1);
    CPPUNIT_TEST(test_instruction2);
    CPPUNIT_TEST(test_instruction3);
    CPPUNIT_TEST(test_instruction4);
    CPPUNIT_TEST(test_instruction5);
    CPPUNIT_TEST(test_species1);
    CPPUNIT_TEST(test_species2);
    CPPUNIT_TEST(test_species3);
    CPPUNIT_TEST(test_generateProgram1);
    CPPUNIT_TEST(test_generateProgram2);
    CPPUNIT_TEST(test_generateProgram3);
    CPPUNIT_TEST(test_creature1);
    CPPUNIT_TEST(test_creature2);
    CPPUNIT_TEST(test_creature3);
    CPPUNIT_TEST(test_invalidate1);
    CPPUNIT_TEST(test_invalidate2);
    CPPUNIT_TEST(test_invalidate3);
    CPPUNIT_TEST(test_valid1);
    CPPUNIT_TEST(test_valid2);
    CPPUNIT_TEST(test_valid3);
    CPPUNIT_TEST(test_board1);
    CPPUNIT_TEST(test_board2);
    CPPUNIT_TEST(test_board3);
    CPPUNIT_TEST(test_getFacing1);
    CPPUNIT_TEST(test_getFacing2);
    CPPUNIT_TEST(test_getFacing3);
    CPPUNIT_TEST(test_infect1);
    CPPUNIT_TEST(test_infect2);
    CPPUNIT_TEST(test_infect3);
    CPPUNIT_TEST(test_hop1);
    CPPUNIT_TEST(test_hop2);
    CPPUNIT_TEST(test_hop3);
    CPPUNIT_TEST(test_execute1);
    CPPUNIT_TEST(test_execute2);
    CPPUNIT_TEST(test_execute3);
    CPPUNIT_TEST(test_place1);
    CPPUNIT_TEST(test_place2);
    CPPUNIT_TEST(test_place3);
    CPPUNIT_TEST(test_place4);
    CPPUNIT_TEST(test_place5);
    CPPUNIT_TEST(test_place6);
    CPPUNIT_TEST(test_absToRow1);
    CPPUNIT_TEST(test_absToRow2);
    CPPUNIT_TEST(test_absToRow3);
    CPPUNIT_TEST(test_absToCol1);
    CPPUNIT_TEST(test_absToCol2);
    CPPUNIT_TEST(test_absToCol3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}