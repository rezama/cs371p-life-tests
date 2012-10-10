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
#include <algorithm>                            // count
#include <memory>                               // allocator
#include "cppunit/extensions/HelperMacros.h"    // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"                // TestFixture
#include "cppunit/TextTestRunner.h"             // TestRunner

#define class       struct
#define private     public
#define protected   public

#include "./Allocator.h"

// -----------------------
// Test our implementation
// -----------------------

template<typename T, std::size_t N>
struct TestPrivate : CppUnit::TestFixture {
    // -------
    // defines
    // -------
#define INT_P(expr) (reinterpret_cast<int*>(expr))
#define T_P(expr)   (reinterpret_cast<T*>(expr))
#define SENT_BYTES  (sizeof(int))

    void test_allocAndSplit() {
        Allocator<T, N> x;
        address_t startAddr = &x.a[0];
        sentinel_t spaceNeeded = sizeof(T);
        address_t p = x.allocAndSplit(startAddr, spaceNeeded);
        CPPUNIT_ASSERT(x.valid());

        CPPUNIT_ASSERT(reinterpret_cast<address_t>(&x.a[SENT_BYTES]) == p);

        int expected = -1 * static_cast<int>(sizeof(T));
        int header = *(reinterpret_cast<int*>(&x.a[0]));
        int footer = *(reinterpret_cast<int*>(&x.a[sizeof(T) + SENT_BYTES]));
        int next_header = *(reinterpret_cast<int*>(&x.a[sizeof(T)
                + SENT_BYTES * 2]));

        int freeBlockSize = N - 4 * SENT_BYTES - sizeof(T);

        CPPUNIT_ASSERT(expected == header);
        CPPUNIT_ASSERT(expected == footer);
        CPPUNIT_ASSERT(next_header == freeBlockSize);
        CPPUNIT_ASSERT(*(INT_P(&x.a[N-SENT_BYTES])) == freeBlockSize);

        x.deallocate(reinterpret_cast<T*>(p), 1);
        CPPUNIT_ASSERT(x.valid());
    }

    void test_allocBlock() {
        Allocator<T, N> x;
        address_t startAddr = &x.a[0];
        address_t p = x.allocBlock(startAddr);
        CPPUNIT_ASSERT(x.valid());

        CPPUNIT_ASSERT(reinterpret_cast<address_t>(&x.a[SENT_BYTES]) == p);

        int expected = -1 * static_cast<int>(N - 2 * SENT_BYTES);
        int header = *(reinterpret_cast<int*>(&x.a[0]));
        int footer = *(reinterpret_cast<int*>(&x.a[N - SENT_BYTES]));

        CPPUNIT_ASSERT(expected == header);
        CPPUNIT_ASSERT(expected == footer);

        x.deallocate(reinterpret_cast<T*>(p), 1);
        CPPUNIT_ASSERT(x.valid());
    }

CPPUNIT_TEST_SUITE(TestPrivate);
        CPPUNIT_TEST(test_allocAndSplit);
        CPPUNIT_TEST(test_allocBlock);
    CPPUNIT_TEST_SUITE_END();
};

// -------------
// TestAllocator
// -------------

template<typename A>
struct TestAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer pointer;

    // ----------------------
    // Allocator::Allocator()
    // ----------------------

    /**
     * Check that valid works with a simple test on the constructor.
     */
    void test_constructor() {
        A x;
    }

    // --------
    // allocate
    // --------

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     */
    void test_allocate_1() {
        A x;
        pointer p1 = x.allocate(1);
        pointer p2 = x.allocate(2);
        pointer p3 = x.allocate(3);
        x.deallocate(p1, 1);
        x.deallocate(p2, 2);
        x.deallocate(p3, 3);
    }

    /**
     * Check to see if we can allocate 0 space
     */
    void test_allocate_2() {
        A x;
        pointer p0 = x.allocate(0);
        x.deallocate(p0, 0);
    }

    /**
     * Check to see that we can allocate the entire heap at once
     */
    void test_allocate_3() {
        A x;
        pointer p = x.allocate(11);
        x.deallocate(p, 0);
    }

    /**
     * Ensure that allocate(-n) for some n, throws an exception.
     */
    void test_allocate_4() {
        A x;
        try {
            x.allocate(-1);
            CPPUNIT_ASSERT(false);
        } catch (std::bad_alloc& e) {
            CPPUNIT_ASSERT(true);
        }
    }

    /**
     * Ensure that allocate(-n) for some n, throws an exception.
     */
    void test_allocate_5() {
        A x;
        try {
            x.allocate(-12345);
            CPPUNIT_ASSERT(false);
        } catch (std::bad_alloc& e) {
            CPPUNIT_ASSERT(true);
        }
    }

    // ----------
    // deallocate
    // ----------

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This does not require a coalesce.
     */
    void test_deallocate_1() {
        A x;
        pointer p1 = x.allocate(1);
        pointer p2 = x.allocate(1);
        *p1 = 42;
        pointer p3 = x.allocate(2);

        x.deallocate(p1, 1);  // special case: deallocating the first block

        // free the rest of the memory
        x.deallocate(p2, 1);
        x.deallocate(p3, 2);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires coalescing with the previous free block.
     */
    void test_deallocate_2() {
        A x;
        pointer p1 = x.allocate(1);  // leave this one busy
        pointer p2 = x.allocate(1);
        pointer p3 = x.allocate(2);
        pointer p4 = x.allocate(1);  // leave this one busy

        x.deallocate(p2, 1);
        x.deallocate(p3, 2);

        // free the rest of the memory
        x.deallocate(p1, 1);
        x.deallocate(p4, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires coalescing with the next free block.
     */
    void test_deallocate_3() {
        A x;
        pointer p1 = x.allocate(1);  // leave this one busy
        pointer p2 = x.allocate(1);
        pointer p3 = x.allocate(1);
        pointer p4 = x.allocate(2);
        pointer p5 = x.allocate(1);  // leave this one busy

        x.deallocate(p4, 2);
        x.deallocate(p3, 1);

        // free the rest of the memory
        x.deallocate(p1, 1);
        x.deallocate(p2, 1);
        x.deallocate(p5, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires coalescing with the previous and next blocks.
     */
    void test_deallocate_4() {
        A x;
        pointer p1 = x.allocate(1);  // leave this one busy
        pointer p2 = x.allocate(1);
        pointer p3 = x.allocate(2);
        pointer p4 = x.allocate(1);
        pointer p5 = x.allocate(1);  // leave this one busy

        x.deallocate(p4, 1);
        x.deallocate(p2, 1);
        x.deallocate(p3, 2);

        // free the rest of the memory
        x.deallocate(p1, 1);
        x.deallocate(p5, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     *
     * Deallocate twice and make sure nothing is coalesced.
     */
    void test_deallocate_5() {
        A x;
        pointer p1 = x.allocate(1);
        pointer p2 = x.allocate(1);
        pointer p3 = x.allocate(1);
        pointer p4 = x.allocate(2);
        pointer p5 = x.allocate(1);

        x.deallocate(p2, 1);
        x.deallocate(p4, 2);

        // free the rest of the memory
        x.deallocate(p1, 1);
        x.deallocate(p3, 1);
        x.deallocate(p5, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires checking the special case that the block to free is at
     * the beginning of the allocator memory.
     */
    void test_deallocate_6() {
        A x;
        pointer p = x.allocate(1);
        *p = 42;
        pointer q = x.allocate(1);
        x.deallocate(p, 1);  // special case: deallocating the first block

        // free the rest of the memory
        x.deallocate(q, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires checking the special case that the block to free is at
     * the end of the allocator memory.
     */
    void test_deallocate_7() {
        A x;
        pointer p1 = x.allocate(1);
        pointer p2 = x.allocate(9);
        x.deallocate(p2, 9);

        // free the rest of the memory
        x.deallocate(p1, 1);
    }

    /**
     * Check that we don't trigger assertions (i.e. is valid).
     * This requires checking the special case that the block to free is at
     * the beginning and end of the allocator memory (the whole heap).
     */
    void test_deallocate_8() {
        A x;
        pointer p1 = x.allocate(11);
        x.deallocate(p1, 11);
    }

    // --------
    // test_one
    // --------

    void test_one() {
        A x;
        const difference_type s = 1;
        const value_type v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        x.deallocate(p, s);
    }

    // --------
    // test_ten
    // --------

    void test_ten() {
        A x;
        const difference_type s = 10;
        const value_type v = 2;
        const pointer b = x.allocate(s);
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;
            }
        } catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);
            }
            x.deallocate(b, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);
        }
        x.deallocate(b, s);
    }

    // -----
    // suite
    // -----

CPPUNIT_TEST_SUITE(TestAllocator);
        CPPUNIT_TEST(test_constructor);
        CPPUNIT_TEST(test_allocate_1);
        CPPUNIT_TEST(test_allocate_2);  // allocate 0
        CPPUNIT_TEST(test_allocate_3);
        CPPUNIT_TEST(test_allocate_4);
        CPPUNIT_TEST(test_allocate_5);
        CPPUNIT_TEST(test_deallocate_1);
        CPPUNIT_TEST(test_deallocate_2);
        CPPUNIT_TEST(test_deallocate_3);
        CPPUNIT_TEST(test_deallocate_4);
        CPPUNIT_TEST(test_deallocate_5);
        CPPUNIT_TEST(test_deallocate_6);
        CPPUNIT_TEST(test_deallocate_7);
        CPPUNIT_TEST(test_deallocate_8);
        CPPUNIT_TEST(test_one);
        CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestAllocator<std::allocator<int> >::suite());
    tr.addTest(TestAllocator<Allocator<int, 100> >::suite());

    tr.addTest(TestAllocator<std::allocator<double> >::suite());
    tr.addTest(TestAllocator<Allocator<double, 100> >::suite());

    tr.addTest(TestPrivate<int, 100>::suite());
    tr.addTest(TestPrivate<double, 100>::suite());

    tr.run();

    cout << "Done." << endl;
    return 0;
}
