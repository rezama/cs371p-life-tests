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

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Allocator.h"
#define HEAP_SIZE 100   // can be any reasonable number. tests should automatically adjust


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

    // -------
    // helpers
    // -------

    // used as a checker function for allocate unit tests
    int getNumElements (pointer p, pointer e) {
        int    c = 0;
        while (p != e) {
            ++*p;
            ++c;
            ++p;}
        return c;
    }

    /*
    returns the maximum number of allocates possible with current HEAP_SIZE 
    and Allocator type. assumes sentinel size == sizeof(int)
     */
    size_t getMaxAllocs () {
        size_t valsize = sizeof(value_type);
        valsize += 2 * sizeof(int);
        return HEAP_SIZE / valsize;
    }

    // -------------
    // test_allocate
    // -------------
    void test_allocate_one () {
        A x;
        int size;
        const difference_type s = 1;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
        try {
            size = getNumElements(b, e);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
        CPPUNIT_ASSERT(size == (int) s);}

    void test_allocate_ten () {
        A x;
        int size;
        const difference_type s = 10;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
        try {
            size = getNumElements(b, e);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
        CPPUNIT_ASSERT(size == (int) s);}


    void test_allocate_capacity () {
        A x;
        int size;
        size_t valsize = sizeof(value_type);
        const difference_type s = ((HEAP_SIZE - (sizeof(int) * 2)) / valsize);
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
        try {
            size = getNumElements(b, e);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
        CPPUNIT_ASSERT(size == (int) s);}

    // --------------
    // test_bad_alloc
    // --------------
    /*
     All tests below this rely on an implementation that throws an exception 
     on bad allocations. Since the default allocator class won't throw an 
     exception on _heapsize or _one_over_capacity, those tests are disabled.
     */
    void test_bad_alloc_negone () {
        A x;
        const difference_type s = -1;
        try {
            x.allocate(s);
            CPPUNIT_ASSERT(false);
        } catch (std::bad_alloc& ba) { /*nothing to be done*/ }}

    void test_bad_alloc_heapsize () {
        A x;
        std::allocator<int> ialloc;
        std::allocator<double> dalloc; 
        const difference_type s = HEAP_SIZE;        
        try {
            x.allocate(s);
            CPPUNIT_ASSERT(typeid(A) == typeid(ialloc) || typeid(A) == typeid(dalloc));
        } catch (std::bad_alloc& ba) { /*nothing to be done*/ }}

    void test_bad_alloc_one_over_capacity () {
        A x;
        std::allocator<int> ialloc;
        std::allocator<double> dalloc; 
        size_t valsize = sizeof(value_type);
        const difference_type s = ((HEAP_SIZE - (sizeof(int) * 2)) / valsize) + 1;
        // std::cout << "s: " << s << std::endl;      
        try {
            x.allocate(s);
            CPPUNIT_ASSERT(typeid(A) == typeid(ialloc) || typeid(A) == typeid(dalloc));
        } catch (std::bad_alloc& ba) { /*nothing to be done*/ }}

    // -------------------
    // test_multi_allocate
    // -------------------
    
    void test_multi_allocate_one_twice () {
        A x;
        const difference_type s = 1;
        pointer b;
        try {
            b = x.allocate(s);
            b = x.allocate(s);
        } catch (...) {
            CPPUNIT_ASSERT(false);}}

    void test_multi_allocate_twice () {
        A x;
        const size_t numAllocs = 2;
        size_t valsize = sizeof(value_type);
        difference_type maxBytes = HEAP_SIZE - (sizeof(int) * 2);
        maxBytes -= (sizeof(int) * 2) * (numAllocs - 1);
        const difference_type s = maxBytes / valsize / numAllocs;   // should always fit since it returns the floor
        // std::cout << "\nmaxBytes: " << maxBytes << ", maxElements: " << maxBytes / valsize 
                  // << ", numAllocs: " << numAllocs << ", s: " << s << std::endl;     
        pointer b;
        try {
            for (size_t i = 0; i < numAllocs; i++) {
                b = x.allocate(s);}
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            CPPUNIT_ASSERT(false);}}

    void test_multi_allocate_four () {
        A x;
        const size_t numAllocs = 4;
        size_t valsize = sizeof(value_type);
        difference_type maxBytes = HEAP_SIZE - (sizeof(int) * 2);
        maxBytes -= (sizeof(int) * 2) * (numAllocs - 1);
        const difference_type s = maxBytes / valsize / numAllocs;   // should always fit since it returns the floor
        // std::cout << "\nmaxBytes: " << maxBytes << ", maxElements: " << maxBytes / valsize 
                  // << ", numAllocs: " << numAllocs << ", s: " << s << std::endl;     
        pointer b;
        try {
            for (size_t i = 0; i < numAllocs; i++) {
                b = x.allocate(s);}
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            CPPUNIT_ASSERT(false);}}

    void test_multi_allocate_max () {
        A x;
        size_t numAllocs = getMaxAllocs();
        const difference_type s = 1;
        // std::cout << "\nnumAllocs: " << numAllocs << ", s: " << s << std::endl;    
        pointer b;
        try {
            for (size_t i = 0; i < numAllocs; i++) {
                b = x.allocate(s);}
        } catch (...) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);

    /* 
    NOTE: allocate unit tests WILL cause a memory leak when used with default 
          Allocator. This is intentional, since these tests are only for the
          purpose of testing the functionality of the allocate function.
          Disable the TestRunner for the STL allocators to isolate your own
          memory leaks.
    */
    // allocate
    CPPUNIT_TEST(test_allocate_one);
    CPPUNIT_TEST(test_allocate_ten);
    CPPUNIT_TEST(test_allocate_capacity);

    // bad_alloc
    CPPUNIT_TEST(test_bad_alloc_negone);
    CPPUNIT_TEST(test_bad_alloc_heapsize);
    CPPUNIT_TEST(test_bad_alloc_one_over_capacity);

    // multi_allocate
    CPPUNIT_TEST(test_multi_allocate_one_twice);
    CPPUNIT_TEST(test_multi_allocate_twice);
    CPPUNIT_TEST(test_multi_allocate_four);
    CPPUNIT_TEST(test_multi_allocate_max);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    // tr.addTest(TestAllocator< std::allocator<int> >::suite());
 tr.addTest(TestAllocator< Allocator<int, HEAP_SIZE> >::suite()); // uncomment!

    // tr.addTest(TestAllocator< std::allocator<double> >::suite());
 tr.addTest(TestAllocator< Allocator<double, HEAP_SIZE> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}
