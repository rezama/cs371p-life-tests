// -----------------------------
// Modeled after
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
//
// Modified for the purpose of CS371P Project #6
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
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestLife.c++ -o TestLife.c++.app
    % valgrind TestLife.c++.app >& TestLife.out
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

#include "Life.h"

// -----------
// TestLife
// -----------

struct TestLife : CppUnit::TestFixture {

    // -----
    // Cell
    // -----
    void test_CellCopyConstructor1 () {
        try {
            Cell c;
            AbstractCell<Cell> *cprime = NULL;
            
            cprime = c.clone();
            assert(cprime == NULL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCopyConstructor2 () {
        try {
            ConwayCell cw;
            Cell       cprime;
            Cell       cdblprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            cdblprime = cprime;

            assert(cdblprime._p != NULL);
            assert(cdblprime._p->_type == CONWAY_CELL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCopyConstructor3 () {
        try {
            FredkinCell fk;
            Cell        cprime;
            Cell        cdblprime;
            
            cprime._p = (AbstractCell<Cell> *)fk.clone();
            cdblprime = cprime;

            assert(cdblprime._p != NULL);
            assert(cdblprime._p->_type == FREDKIN_CELL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellCopyConstructorPtr1 () {
        try {
            ConwayCell  cw;
            Cell        c((AbstractCell<Cell> *)cw.clone());

            assert(c.get() != NULL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCopyConstructorPtr2 () {
        try {
            FredkinCell fk;
            Cell        c((AbstractCell<Cell> *)fk.clone());
            
            assert(c.get() != NULL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCopyConstructorPtr3 () {
        try {
            FredkinCell fk;
            Cell        c((AbstractCell<Cell> *)fk.clone());
            Cell        cdblprime(c);
            
            assert(cdblprime.get() != NULL);
            assert(cdblprime.get()->_type == FREDKIN_CELL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellClone1 () {
        try {
            Cell c;
            AbstractCell<Cell> *cprime = NULL;
            
            cprime = c.clone();
            assert(cprime == NULL);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellClone2 () {
        try {
            ConwayCell cw;
            AbstractCell<Cell> *cprime = NULL;
            
            cprime = (AbstractCell<Cell> *)cw.clone();
            assert(cprime != NULL);
            assert(cprime->_type == CONWAY_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellClone3 () {
        try {
            FredkinCell fk;
            AbstractCell<Cell> *cprime = NULL;
            
            cprime = (AbstractCell<Cell> *)fk.clone();
            assert(cprime != NULL);
            assert(cprime->_type == FREDKIN_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellCalcNumNeighborsAlive1 () {
        try {
            size_type m[9];
            ConwayCell cw;
            Cell       cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 0;
            m[6] = m[7] = m[8] = 0;
            
            assert(cprime.calcNumNeighborsAlive(&m[0]) == 3);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCalcNumNeighborsAlive2 () {
        try {
            size_type m[9];
            ConwayCell cw;
            Cell       cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 1;
            m[6] = m[7] = m[8] = 0;

            assert(cprime.calcNumNeighborsAlive(&m[0]) == 5);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellCalcNumNeighborsAlive3 () {
        try {
            size_type m[9];
            FredkinCell fk;
            Cell        cprime;
            
            cprime._p = (AbstractCell<Cell> *)fk.clone();
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 1;
            m[6] = m[7] = m[8] = 0;

            assert(cprime.calcNumNeighborsAlive(&m[0]) == 3);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellGeneration1 () {
        try {
            ConwayCell cw;
            Cell       cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            cprime.generation(2);
            assert(cprime._p->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellGeneration2 () {
        try {
            ConwayCell cw;
            Cell       cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            cprime.generation(3);
            assert(cprime._p->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellGeneration3 () {
        try {
            FredkinCell fk;
            Cell        cprime;
            
            cprime._p = (AbstractCell<Cell> *)fk.clone();
            cprime.generation(3);
            assert(cprime._p->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellRead1 () {
        try {
            string          s("*");
            istringstream   iss;
            ConwayCell      cw;
            Cell            cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            iss.str(s);
            iss >> cprime;
            assert(cprime._p->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellRead2 () {
        try {
            string          s(".");
            istringstream   iss;
            ConwayCell      cw;
            Cell            cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            iss.str(s);
            iss >> cprime;
            assert(cprime._p->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellRead3 () {
        try {
            string          s("-");  
            istringstream   iss;
            FredkinCell     fk;
            Cell            cprime;
            
            cprime._p = (AbstractCell<Cell> *)fk.clone();
            iss.str(s);
            iss >> cprime;
            assert(cprime._p->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    void test_CellWrite1 () {
        try {
            ostringstream   oss;
            ConwayCell      cw;
            Cell            cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            oss << cprime;
            assert(oss.str().compare(".") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellWrite2 () {
        try {
            string          sin("*");
            ostringstream   oss;
            istringstream   iss;
            ConwayCell      cw;
            Cell            cprime;
            
            cprime._p = (AbstractCell<Cell> *)cw.clone();
            iss.str(sin);
            iss >> cprime;
            oss << cprime;
            assert(oss.str().compare("*") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_CellWrite3 () {
        try {
            string          sin("-");
            istringstream   iss;
            ostringstream   oss;
            FredkinCell     fk;
            Cell            cprime;
           
            cprime._p = (AbstractCell<Cell> *)fk.clone(); 
            iss.str(sin);
            iss >> cprime;
            oss << cprime;
            assert(oss.str().compare("-") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    // -----
    // ConwayCell
    // -----
    void test_ConwayCellCopyConstructor1 () {
        try {
            ConwayCell cw;
            
            cw.get()->_alive = 1;
            
            ConwayCell cwprime(cw);
            
            assert(cwprime.get()->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellCopyConstructor2 () {
        try {
            string          s("*");
            istringstream   iss;
            ostringstream   oss;            
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            
            ConwayCell      cwprime(cw);
            
            oss << cwprime;
            assert(oss.str().compare("*") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellCopyConstructor3 () {
        try {
            string          s(".");
            istringstream   iss;
            ostringstream   oss;            
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            
            ConwayCell      cwprime(cw);
            
            oss << cwprime;
            assert(oss.str().compare(".") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellClone1 () {
        try {
            ConwayCell cw;
            AbstractCell<ConwayCell> *cprime;
            
            cprime = (AbstractCell<ConwayCell> *)cw.clone();
            assert(cprime != NULL);
            assert(cprime->_type == CONWAY_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellClone2 () {
        try {
            string          s("*");
            istringstream   iss;            
            ConwayCell      cw;
            AbstractCell<ConwayCell> *cprime;
            
            iss.str(s);
            iss >> cw;
            
            cprime = (AbstractCell<ConwayCell> *)cw.clone();
            assert(cprime != NULL);
            assert(cprime->_type == CONWAY_CELL);
            assert(cprime->_alive == 1);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellClone3 () {
        try {
            string          s("*");
            istringstream   iss;            
            ostringstream   oss;             
            ConwayCell      cw;
            AbstractCell<ConwayCell> *cprime;
            
            iss.str(s);
            iss >> cw;
            
            cprime = (AbstractCell<ConwayCell> *)cw.clone();
            
            oss << cprime;
            
            assert(cprime != NULL);
            assert(cprime->_type == CONWAY_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellCalcNumNeighborsAlive1 () {
        try {
            size_type m[9];
            ConwayCell cw;
            
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 0;
            m[6] = m[7] = m[8] = 0;
            
            assert(cw.calcNumNeighborsAlive(&m[0]) == 3);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellCalcNumNeighborsAlive2 () {
        try {
            size_type m[9];
            ConwayCell cw;
            
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 0;
            m[6] = m[7] = m[8] = 1;
            
            assert(cw.calcNumNeighborsAlive(&m[0]) == 6);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellCalcNumNeighborsAlive3 () {
        try {
            size_type m[9];
            ConwayCell cw;
            
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 1;
            m[6] = m[7] = m[8] = 0;
            
            assert(cw.calcNumNeighborsAlive(&m[0]) == 5);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellGeneration1 () {
        try {
            string          s("*");
            istringstream   iss;            
            ostringstream   oss;             
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            cw.generation(1);
            oss << cw;
            assert(cw.get()->_alive == 0);
            assert(oss.str().compare(".") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellGeneration2 () {
        try {
            string          s("*");
            istringstream   iss;            
            ostringstream   oss;             
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            cw.generation(3);
            oss << cw;
            assert(cw.get()->_alive == 1);
            assert(oss.str().compare("*") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellGeneration3 () {
        try {
            ostringstream   oss;            
            ConwayCell      cw;
            
            cw.generation(3);
            oss << cw;
            assert(cw.get()->_alive == 1);
            assert(oss.str().compare("*") == 0);            
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellRead1 () {
        try {
            string          s("*");
            istringstream   iss;
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            assert(cw.get()->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellRead2 () {
        try {
            string          s("*");
            istringstream   iss;
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            
            ConwayCell      cwprime(cw);
            iss.str(".");
            iss >> cwprime;
            assert(cw.get()->_alive == 1);
            assert(cwprime.get()->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellRead3 () {
        try {
            string          s(".");  
            istringstream   iss;
            ConwayCell      cw;
            
            iss.str(s);
            iss >> cw;
            assert(cw.get()->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellWrite1 () {
        try {
            ostringstream   oss;
            ConwayCell      cw;
            
            oss << cw;
            assert(oss.str().compare(".") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellWrite2 () {
        try {
            string          sin("*");
            ostringstream   oss;
            istringstream   iss;
            ConwayCell      cw;
            
            iss.str(sin);
            iss >> cw;
            oss << cw;
            assert(oss.str().compare("*") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_ConwayCellWrite3 () {
        try {
            string          sin("*");
            istringstream   iss;
            ostringstream   oss;
            ConwayCell      cw;
            ConwayCell      cwprime(cw);
            
            iss.str(sin);
            iss >> cw;
            oss << cwprime;
            assert(oss.str().compare(".") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}

    // -----
    // FredkinCell
    // -----
    void test_FredkinCellCopyConstructor1 () {
        try {
            FredkinCell fk;
            
            fk.get()->_alive = 1;
            
            FredkinCell fkprime(fk);
            
            assert(fkprime.get()->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellCopyConstructor2 () {
        try {
            string          s("9");
            istringstream   iss;
            ostringstream   oss;            
            FredkinCell     fk;
            
            iss.str(s);
            iss >> fk;

            FredkinCell     fkprime(fk);
            
            oss << fkprime;
            assert(oss.str().compare("9") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellCopyConstructor3 () {
        try {
            string          s("-");
            istringstream   iss;
            ostringstream   oss;            
            FredkinCell     fk;
            
            iss.str(s);
            iss >> fk;
            
            FredkinCell     fkprime(fk);
            
            oss << fkprime;
            assert(oss.str().compare("-") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
        
    void test_FredkinCellClone1 () {
        try {
            FredkinCell fk;
            AbstractCell<FredkinCell> *cprime;
            
            cprime = (AbstractCell<FredkinCell> *)fk.clone();
            assert(cprime != NULL);
            assert(cprime->_type == FREDKIN_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellClone2 () {
        try {
            string          s("9");
            istringstream   iss;            
            FredkinCell     fk;
            AbstractCell<FredkinCell> *cprime;
            
            iss.str(s);
            iss >> fk;

            cprime = (AbstractCell<FredkinCell> *)fk.clone();
            assert(cprime != NULL);
            assert(cprime->_type == FREDKIN_CELL);
            assert(cprime->_alive == 1);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellClone3 () {
        try {
            string          s("9");
            istringstream   iss;            
            ostringstream   oss;             
            FredkinCell     fk;
            AbstractCell<FredkinCell> *cprime;

            iss.str(s);
            iss >> fk;
            
            cprime = (AbstractCell<FredkinCell> *)fk.clone();
            
            oss << cprime;
            
            assert(cprime != NULL);
            assert(cprime->_type == FREDKIN_CELL);
            delete cprime;
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellCalcNumNeighborsAlive1 () {
        try {
            size_type m[9];
            FredkinCell fk;

            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 0;
            m[6] = m[7] = m[8] = 0;
            
            assert(fk.calcNumNeighborsAlive(&m[0]) == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellCalcNumNeighborsAlive2 () {
        try {
            size_type m[9];
            FredkinCell fk;
            
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 0;
            m[6] = m[7] = m[8] = 1;
            
            assert(fk.calcNumNeighborsAlive(&m[0]) == 2);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellCalcNumNeighborsAlive3 () {
        try {
            size_type m[9];
            FredkinCell fk;
            
            m[0] = m[1] = m[2] = 1;
            m[3] = m[4] = m[5] = 1;
            m[6] = m[7] = m[8] = 0;
            
            assert(fk.calcNumNeighborsAlive(&m[0]) == 3);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellGeneration1 () {
        try {
            string          s("9");
            istringstream   iss;            
            ostringstream   oss;             
            FredkinCell     fk;
            
            iss.str(s);
            iss >> fk;
            fk.generation(1);
            oss << fk;
            assert(fk.get()->_alive == 1);
            assert(oss.str().compare("+") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellGeneration2 () {
        try {
            string          s("+");
            istringstream   iss;            
            ostringstream   oss;             
            FredkinCell     fk;

            iss.str(s);
            iss >> fk;
            fk.generation(3);
            oss << fk;
            assert(fk.get()->_alive == 1);
            assert(oss.str().compare("+") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellGeneration3 () {
        try {
            ostringstream   oss;            
            FredkinCell     fk;
            
            fk.generation(3);
            oss << fk;
            assert(fk.get()->_alive == 1);
            assert(oss.str().compare("0") == 0);            
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellRead1 () {
        try {
            string          s("0");
            istringstream   iss;
            FredkinCell     fk;
            
            iss.str(s);
            iss >> fk;
            assert(fk.get()->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellRead2 () {
        try {
            string          s("+");
            istringstream   iss;
            FredkinCell     fk;

            iss.str(s);
            iss >> fk;
            assert(fk.get()->_alive == 1);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellRead3 () {
        try {
            string          s("-");  
            istringstream   iss;
            FredkinCell     fk;
            
            iss.str(s);
            iss >> fk;
            assert(fk.get()->_alive == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellWrite1 () {
        try {
            ostringstream   oss;
            FredkinCell     fk;
            
            oss << fk;
            assert(oss.str().compare("-") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellWrite2 () {
        try {
            string          sin("0");
            ostringstream   oss;
            istringstream   iss;
            FredkinCell     fk;
            
            iss.str(sin);
            iss >> fk;
            oss << fk;
            assert(oss.str().compare("0") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    void test_FredkinCellWrite3 () {
        try {
            string          sin("+");
            istringstream   iss;
            ostringstream   oss;
            FredkinCell     fk;
            
            iss.str(sin);
            iss >> fk;
            oss << fk;
            assert(oss.str().compare("+") == 0);
        } catch (const invalid_argument&) {
            CPPUNIT_ASSERT(false);
        } catch (const out_of_range&) {
            CPPUNIT_ASSERT(false);
        }}
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);

    CPPUNIT_TEST(test_CellCopyConstructor1);
    CPPUNIT_TEST(test_CellCopyConstructor2);
    CPPUNIT_TEST(test_CellCopyConstructor3);

    CPPUNIT_TEST(test_CellCopyConstructorPtr1);
    CPPUNIT_TEST(test_CellCopyConstructorPtr2);
    CPPUNIT_TEST(test_CellCopyConstructorPtr3);

    CPPUNIT_TEST(test_CellClone1);
    CPPUNIT_TEST(test_CellClone2);
    CPPUNIT_TEST(test_CellClone3);

    CPPUNIT_TEST(test_CellCalcNumNeighborsAlive1);
    CPPUNIT_TEST(test_CellCalcNumNeighborsAlive2);
    CPPUNIT_TEST(test_CellCalcNumNeighborsAlive3);
    
    CPPUNIT_TEST(test_CellGeneration1);
    CPPUNIT_TEST(test_CellGeneration2);
    CPPUNIT_TEST(test_CellGeneration3);

    CPPUNIT_TEST(test_CellRead1);
    CPPUNIT_TEST(test_CellRead2);
    CPPUNIT_TEST(test_CellRead3);
    
    CPPUNIT_TEST(test_CellWrite1);
    CPPUNIT_TEST(test_CellWrite2);
    CPPUNIT_TEST(test_CellWrite3);

    CPPUNIT_TEST(test_ConwayCellCopyConstructor1);
    CPPUNIT_TEST(test_ConwayCellCopyConstructor2);
    CPPUNIT_TEST(test_ConwayCellCopyConstructor3);
    
    CPPUNIT_TEST(test_ConwayCellClone1);
    CPPUNIT_TEST(test_ConwayCellClone2);
    CPPUNIT_TEST(test_ConwayCellClone3);
    
    CPPUNIT_TEST(test_ConwayCellCalcNumNeighborsAlive1);
    CPPUNIT_TEST(test_ConwayCellCalcNumNeighborsAlive2);
    CPPUNIT_TEST(test_ConwayCellCalcNumNeighborsAlive3);
    
    CPPUNIT_TEST(test_ConwayCellGeneration1);
    CPPUNIT_TEST(test_ConwayCellGeneration2);
    CPPUNIT_TEST(test_ConwayCellGeneration3);
    
    CPPUNIT_TEST(test_ConwayCellRead1);
    CPPUNIT_TEST(test_ConwayCellRead2);
    CPPUNIT_TEST(test_ConwayCellRead3);
    
    CPPUNIT_TEST(test_ConwayCellWrite1);
    CPPUNIT_TEST(test_ConwayCellWrite2);
    CPPUNIT_TEST(test_ConwayCellWrite3);

    CPPUNIT_TEST(test_FredkinCellCopyConstructor1);
    CPPUNIT_TEST(test_FredkinCellCopyConstructor2);
    CPPUNIT_TEST(test_FredkinCellCopyConstructor3);
        
    CPPUNIT_TEST(test_FredkinCellClone1);
    CPPUNIT_TEST(test_FredkinCellClone2);
    CPPUNIT_TEST(test_FredkinCellClone3);
    
    CPPUNIT_TEST(test_FredkinCellCalcNumNeighborsAlive1);
    CPPUNIT_TEST(test_FredkinCellCalcNumNeighborsAlive2);
    CPPUNIT_TEST(test_FredkinCellCalcNumNeighborsAlive3);
    
    CPPUNIT_TEST(test_FredkinCellGeneration1);
    CPPUNIT_TEST(test_FredkinCellGeneration2);
    CPPUNIT_TEST(test_FredkinCellGeneration3);
    
    CPPUNIT_TEST(test_FredkinCellRead1);
    CPPUNIT_TEST(test_FredkinCellRead2);
    CPPUNIT_TEST(test_FredkinCellRead3);
    
    CPPUNIT_TEST(test_FredkinCellWrite1);
    CPPUNIT_TEST(test_FredkinCellWrite2);
    CPPUNIT_TEST(test_FredkinCellWrite3);
    
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
