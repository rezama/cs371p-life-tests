// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestAllocator.c++ -o TestAllocator.app
 *     valgrind TestAllocator.app >& TestAllocator.out
 */

//---------
// Defines
//---------

 
// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#define class struct
#include "Allocator.h"

 

// -------------
// TestAllocator
// -------------

template <typename A>
struct TestAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------
    
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;
    
    // --------
    // test_one
    // --------
    
    void test_one () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        x.deallocate(p, s);}
    
    // --------
    // test_ten
    // --------
    
    void test_ten () {
        A x;
        const difference_type s = 10;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
        pointer         e = b + s;
        pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}

    ///////////////////////
    // Store Int Tests//
    ///////////////////////
    void testStoreInt(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(15, charArray);


        CPPUNIT_ASSERT((int)charArray[0] == 15);
        CPPUNIT_ASSERT((int)charArray[1] == 0);
        CPPUNIT_ASSERT((int)charArray[2] == 0);
        CPPUNIT_ASSERT((int)charArray[3] == 0);

    }

    void testStoreIntMax(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(32767, charArray);
        CPPUNIT_ASSERT((int)charArray[0] == -1);
        CPPUNIT_ASSERT((int)charArray[1] == 127);
        CPPUNIT_ASSERT((int)charArray[2] == 0);
        CPPUNIT_ASSERT((int)charArray[3] == 0);
        
    }

    void testStoreIntMin(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(1, charArray);
        CPPUNIT_ASSERT((int)charArray[0] == 1);
        CPPUNIT_ASSERT((int)charArray[1] == 0);
        CPPUNIT_ASSERT((int)charArray[2] == 0);
        CPPUNIT_ASSERT((int)charArray[3] == 0);
        
    }

    void testStoreIntNegative(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(-142, charArray);
        CPPUNIT_ASSERT((int)charArray[0] == 114);
        CPPUNIT_ASSERT((int)charArray[1] == -1);
        CPPUNIT_ASSERT((int)charArray[2] == -1);
        CPPUNIT_ASSERT((int)charArray[3] == -1);
        
    }

    ///////////////////////
    // Retrieve Int Tests//
    ///////////////////////

    void testRetrieveInt(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(15, charArray);

        int answer = a.retrieveInt(charArray, charArray+4);
        std::cout<<answer<<std::endl;
        CPPUNIT_ASSERT(answer == 15);

    }

    void testRetrieveIntMax(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(32767, charArray);
        int answer = a.retrieveInt(charArray, charArray+4);

        CPPUNIT_ASSERT(answer == 32767);
        
    }

    void testRetrieveIntMin(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(1, charArray);
        int answer = a.retrieveInt(charArray, charArray+4);

        CPPUNIT_ASSERT(answer == 1);
        
    }

    void testRetrieveIntNegative(){
        Allocator<int, 100> a;
        char charArray[4];

        a.storeInt(-142, charArray);
        int answer = a.retrieveInt(charArray, charArray+4);

        CPPUNIT_ASSERT(answer == -142);
    }

    ////////////////////
    // Valid Tests//
    ///////////////////

    void testValid1 () {
        Allocator<int, 100> al;
        int* b = (int*) &al.a[0];
        *b = 92;
        b += 96;
        *b = 92;
        const bool result = al.valid();
        CPPUNIT_ASSERT(result == true);
    }

    void testValid2(){
        Allocator<int, 100> al;
        int* b = (int*) &al.a[0];
        *b = 40;
        b = (int*)&al.a[44];
        *b = 40;
        b = (int*)&al.a[48];
        *b = 10;
        b = (int*)&al.a[62];
        *b = 10;
        b = (int*)&al.a[66];
        *b = 26;
        b = (int*)&al.a[96];
        *b = 26;
        const bool result = al.valid();
        CPPUNIT_ASSERT(result == true);

    }
    void testValid3Negatives(){
        Allocator<int, 100> al;
        int* b = (int*) &al.a[0];
        *b = -40;
        b = (int*)&al.a[44];
        *b = -40;
        b = (int*)&al.a[48];
        *b = 10;
        b = (int*)&al.a[62];
        *b = 10;
        b = (int*)&al.a[66];
        *b = -26;
        b = (int*)&al.a[96];
        *b = -26;
        const bool result = al.valid();
        CPPUNIT_ASSERT(result == true);

    }

    ////////////////////
    // Allocate Tests//
    ///////////////////

    void testFiveAllocation () {
        A x;
        const difference_type s = 5;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
        pointer         e = b + s;
        pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);
    }

    void testZeroAllocation () {
        A x;
        const difference_type s = 0;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
        pointer         e = b + s;
        pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);
    }

    void testLotsAllocation () {
        A x;
        const difference_type s = 1000;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
        pointer         e = b + s;
        pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);
    }
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);

    //storeInt Tests
    CPPUNIT_TEST(testStoreInt);
    CPPUNIT_TEST(testStoreIntMax);
    CPPUNIT_TEST(testStoreIntMin);
    CPPUNIT_TEST(testStoreIntNegative);

    //retrieveInt Tests
    CPPUNIT_TEST(testStoreInt);
    CPPUNIT_TEST(testStoreIntMax);
    CPPUNIT_TEST(testStoreIntMin);
    CPPUNIT_TEST(testRetrieveIntNegative);

    //Valid Tests
    CPPUNIT_TEST(testValid1);
    CPPUNIT_TEST(testValid2);
    CPPUNIT_TEST(testValid3Negatives);

    //allocate tests
    CPPUNIT_TEST(testFiveAllocation);
    CPPUNIT_TEST(testZeroAllocation);
    CPPUNIT_TEST(testLotsAllocation);
    
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;
    
    CppUnit::TextTestRunner tr;
    
    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    //  tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!
    
    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    //  tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!
    
    tr.run();
    
    cout << "Done." << endl;
    return 0;}