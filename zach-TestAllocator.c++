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

    // NOTE ---------------------------------------------------------
    // Since it is difficult to tease out specific parts of the
    // allocator, the unit tests sometimes overlap. Since this is
    // the case, we felt the need to specify specific assertions,
    // their purpose in terms of testing, and the number (so that
    // it can be verified that there are 3 for each method/function).
    // We felt that these still fall in the same category of "unit
    // tests" since the two tests provided by Professor Downing also
    // appeared in this way. 
    // NO MATTER WHAT, we can affirm that these
    // tests do, in fact, test each individual element of the
    // program. It is also difficult to perform one action without
    // the others since allocating space without deallocating, for
    // instance, creates a memory leak.
    // --------------------------------------------------------------

    // -------
    // mytest1 - tests allocate, construct, deallocate
    // -------

    void mytest1 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        const pointer         r = x.allocate(s);
        // testing construct
        x.construct(p, v);
        x.construct(q, v);
        x.construct(r, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v);
        CPPUNIT_ASSERT(*r == v);

        x.destroy(q);
        x.destroy(p);

        x.deallocate(q, s);
        x.deallocate(p, s);

        pointer b = x.allocate(s * 2);

        x.destroy(r);
        
        // testing coalescing
        x.deallocate(b, s * 2);
        x.deallocate(r, s);
    }

    // -------
    // mytest2 - tests allocate
    // -------

    void mytest2 () {
        A x;
        const difference_type s = 25;
        
        // testing allocate
        try {

          const pointer         p = x.allocate(s);
          x.deallocate(p, s);

        } catch (std::bad_alloc& e) {
          CPPUNIT_ASSERT(true);
        }

    }

    // -------
    // mytest3 - tests allocate, deallocate
    // -------

    void mytest3 () {
        A x;
        const difference_type s = 10;
        const pointer         a = x.allocate(s);

        // testing allocate
        try {

          const pointer       p = x.allocate(s);
          x.deallocate(p, s);

        } catch (std::bad_alloc& e) {
          CPPUNIT_ASSERT(true);
        }

        x.deallocate(a, s);
    }

    // -------
    // mytest4 - tests allocate, construct, destroy
    // -------

    void mytest4 () {
        A x;
        const difference_type s = 5;
        const value_type      v = 2;
        const pointer         a = x.allocate(s);

        pointer begin = a;
        pointer end = a + s;

        while (begin != end) {
          x.construct(begin, v);
          begin++;
        }

        CPPUNIT_ASSERT(std::count(a, end, v) == s);

        begin = a;

        while (begin != end) {
          x.destroy(end);
          begin++;
        }

        // testing destroy - if it's valid it worked
        x.deallocate(a, s);
    }

    // -------
    // mytest5 - tests allocate, construct, destroy, deallocate, valid
    // -------

    void mytest5 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         a = x.allocate(s);
        x.construct(a, v);
        CPPUNIT_ASSERT(*a == v);
        x.destroy(a);
        x.deallocate(a, s);
        const pointer         b = x.allocate(s);
        x.construct(b, v);
        CPPUNIT_ASSERT(*b == v);
        x.destroy(b);
        x.deallocate(b, s);
        const pointer         c = x.allocate(s);
        x.construct(c, v);
        CPPUNIT_ASSERT(*c == v);
        x.destroy(c);
        x.deallocate(c, s);
        const pointer         d = x.allocate(s);
        x.construct(d, v);
        CPPUNIT_ASSERT(*d == v);
        x.destroy(d);
        x.deallocate(d, s);
        const pointer         e = x.allocate(s);
        x.construct(e, v);
        CPPUNIT_ASSERT(*e == v);
        x.destroy(e);
        x.deallocate(e, s);
    }

    // -------
    // mytest6 - tests allocate, construct, destroy, deallocate, valid
    // -------

    void mytest6 () {
        A x;
        const difference_type s = 2;
        const value_type      v = 2;
        const pointer         a = x.allocate(s);
        x.construct(a, v);
        CPPUNIT_ASSERT(*a == v);
        x.destroy(a);
        x.deallocate(a, s);
        const pointer         b = x.allocate(s);
        x.construct(b, v);
        CPPUNIT_ASSERT(*b == v);
        x.destroy(b);
        x.deallocate(b, s);
        const pointer         c = x.allocate(s);
        x.construct(c, v);
        CPPUNIT_ASSERT(*c == v);
        x.destroy(c);
        x.deallocate(c, s);
        const pointer         d = x.allocate(s);
        x.construct(d, v);
        CPPUNIT_ASSERT(*d == v);
        x.destroy(d);
        x.deallocate(d, s);
        const pointer         e = x.allocate(s);
        x.construct(e, v);
        CPPUNIT_ASSERT(*e == v);
        x.destroy(e);
        x.deallocate(e, s);
    }

    // -------
    // mytest7 - tests allocate, construct, destroy, deallocate, valid
    // -------

    void mytest7 () {
        A x;
        const difference_type s = 10;
        const value_type      v = 2;
        const pointer         a = x.allocate(s);

        pointer begin = a;
        pointer end = a + s;

        while (begin != end) {
          x.construct(begin, v);
          begin++;
        }

        CPPUNIT_ASSERT(std::count(a, end, v) == s);

        begin = a;

        while (begin != end) {
          x.destroy(end);
          begin++;
        }

        // testing destroy - if it's valid it worked
        x.deallocate(a, s);

        const pointer b = x.allocate(s);

        begin = b;
        end = b + s;

        while (begin != end) {
          x.construct(begin, v);
          begin++;
        }

        CPPUNIT_ASSERT(std::count(b, end, v) == s);

        begin = b;

        while (begin != end) {
          x.destroy(end);
          begin++;
        }

        // testing destroy - if it's valid it worked
        x.deallocate(b, s);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(mytest1);
    CPPUNIT_TEST(mytest2);
    CPPUNIT_TEST(mytest3);
    CPPUNIT_TEST(mytest4);
    CPPUNIT_TEST(mytest5);
    CPPUNIT_TEST(mytest6);
    CPPUNIT_TEST(mytest7);
    CPPUNIT_TEST_SUITE_END();};

// -------------
// TestOURAllocator
// -------------

template <typename A>
struct TestOURAllocator : CppUnit::TestFixture {

    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;

    // -------
    // mytest8 - tests readSentinel
    // -------

    void mytest8 () {
      A x;
      char tester[4] = { 0x00, 0x00, 0x00, 0x01 };
      
      CPPUNIT_ASSERT(x.readSentinel(tester) == 1);
    }
    // -------
    // mytest9 - tests readSentinel
    // -------

    void mytest9 () {
      A x;
      char tester[5] = { 0x00, 0x00, 0x00, 0x00, 0x01 };
      
      CPPUNIT_ASSERT(x.readSentinel(tester + 1) == 1);
    }

    // -------
    // mytest10 - tests readSentinel
    // -------

    void mytest10 () {
      A x;
      char tester[4] = { 0x01, 0x00, 0x00, 0x00};
      
      CPPUNIT_ASSERT(x.readSentinel(tester) == (1 << 24));
    }

    // -------
    // mytest11 - tests writeSentinel
    // -------

    void mytest11 () {
      A x;
      char tester[4];

      x.writeSentinel(tester, 0);
      
      CPPUNIT_ASSERT(tester[0] == 0x00);
      CPPUNIT_ASSERT(tester[1] == 0x00);
      CPPUNIT_ASSERT(tester[2] == 0x00);
      CPPUNIT_ASSERT(tester[3] == 0x00);
    }

    // -------
    // mytest12 - tests writeSentinel
    // -------

    void mytest12 () {
      A x;
      char tester[4];

      x.writeSentinel(tester, 1 << 24);
      
      CPPUNIT_ASSERT(tester[0] == 0x01);
      CPPUNIT_ASSERT(tester[1] == 0x00);
      CPPUNIT_ASSERT(tester[2] == 0x00);
      CPPUNIT_ASSERT(tester[3] == 0x00);
    }

    // -------
    // mytest13 - tests writeSentinel
    // -------

    void mytest13 () {
      A x;
      char tester[5];

      x.writeSentinel(tester + 1, 1);
      
      CPPUNIT_ASSERT(tester[1] == 0x00);
      CPPUNIT_ASSERT(tester[2] == 0x00);
      CPPUNIT_ASSERT(tester[3] == 0x00);
      CPPUNIT_ASSERT(tester[4] == 0x01);
    }

    void test_valid1 () {
      A x;
      
      x.writeSentinel(x.a, sizeof(x.a) - 8);
      x.writeSentinel(x.a + sizeof(x.a) - 4, sizeof(x.a) - 8);

      CPPUNIT_ASSERT(x.valid() == true);
      
    }

    void test_valid2 () {
      A x;
      
      x.writeSentinel(x.a, sizeof(x.a) - 2);
      x.writeSentinel(x.a + sizeof(x.a) - 4, sizeof(x.a) - 8);

      CPPUNIT_ASSERT(x.valid() == false);
      
    }

    void test_valid3 () {
      A x;
      
      x.writeSentinel(x.a, sizeof(x.a) - 8);
      x.writeSentinel(x.a + sizeof(x.a) - 4, sizeof(x.a) - 4);

      CPPUNIT_ASSERT(x.valid() == false);
      
    }

    // ----
    // allocator_test1
    // ----

    void allocator_test1 () {
        A x;
        const difference_type s = 1;
        const pointer         p = x.allocate(s);

        if (typeid(value_type) == typeid(int)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[8]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == 80);
        } 
        else if (typeid(value_type) == typeid(double)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[16]) == 76);
        }
        else
          CPPUNIT_ASSERT(false);

        x.deallocate(p, s);
    }

    // ----
    // allocator_test2
    // ----

    void allocator_test2 () {
        A x;
        const difference_type s = 1;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);


        if (typeid(value_type) == typeid(int)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(q != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[8]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[20]) == -4);
        } 
        else if (typeid(value_type) == typeid(double)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(q != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[16]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[28]) == -8);
        }
        else
          CPPUNIT_ASSERT(false);

        x.deallocate(p, s);
        x.deallocate(q, s);
    }

    // ----
    // allocator_test3
    // ----

    void allocator_test3 () {
        A x;
        const difference_type s = 1;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        const pointer         r = x.allocate(s);


        if (typeid(value_type) == typeid(int)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(q != 0);
          CPPUNIT_ASSERT(r != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[8]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[20]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[24]) == -4);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[32]) == -4);
        } 
        else if (typeid(value_type) == typeid(double)) {
          CPPUNIT_ASSERT(p != 0);
          CPPUNIT_ASSERT(q != 0);
          CPPUNIT_ASSERT(r != 0);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[12]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[16]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[28]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[32]) == -8);
          CPPUNIT_ASSERT(x.readSentinel(&x.a[44]) == -8);
        }
        else
          CPPUNIT_ASSERT(false);

        x.deallocate(p, s);
        x.deallocate(q, s);
        x.deallocate(r, s);
    }

    // ----
    // constructor_test1
    // ----

    void constructor_test1 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        // testing construct
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v); 

        x.destroy(p);

        x.deallocate(p, s);
    }

    // ----
    // constructor_test2
    // ----

    void constructor_test2 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        // testing construct
        x.construct(p, v);
        x.construct(q, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v);

        x.destroy(q);
        x.destroy(p);

        x.deallocate(q, s);
        x.deallocate(p, s);
    }

    // ----
    // constructor_test3
    // ----

    void constructor_test3 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        const pointer         r = x.allocate(s);
        // testing construct
        x.construct(p, v);
        x.construct(q, v);
        x.construct(r, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v);
        CPPUNIT_ASSERT(*r == v);

        x.destroy(q);
        x.destroy(p);

        x.deallocate(q, s);
        x.deallocate(p, s);

        x.destroy(r);
        
        x.deallocate(r, s);
    }

    // ----
    // destroy_test1
    // ----

    void destroy_test1 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v); 

        x.destroy(p);

        try {
          value_type z = *p;
          --z;
          CPPUNIT_ASSERT(false);
        } catch (...) {
          CPPUNIT_ASSERT(true);
        }

        x.deallocate(p, s);
    }

    // ----
    // destroy_test2
    // ----

    void destroy_test2 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        x.construct(p, v);
        x.construct(q, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v); 

        x.destroy(p);
        x.destroy(q);

        try {
          value_type z = *p;
          --z;
          CPPUNIT_ASSERT(false);
        } catch (...) {
          CPPUNIT_ASSERT(true);
        }
        try {
          value_type z = *q;
          --z;
          CPPUNIT_ASSERT(false);
        } catch (...) {
          CPPUNIT_ASSERT(true);
        }

        x.deallocate(p, s);
        x.deallocate(q, s);
    }

    // ----
    // destroy_test3
    // ----

    void destroy_test3 () {
        A x;
        const difference_type s = 5;
        const value_type      v = 2;
        const pointer         a = x.allocate(s);

        pointer begin = a;
        pointer end = a + s;

        while (begin != end) {
          x.construct(begin, v);
          begin++;
        }

        CPPUNIT_ASSERT(std::count(a, end, v) == s);

        begin = a;

        while (begin != end) {
          x.destroy(end);
          begin++;
        }
        try {
          value_type z = *(a);
          --z;
          CPPUNIT_ASSERT(false);
        } catch (...) {
          CPPUNIT_ASSERT(true);
        }
        try {
          value_type z = *(a + 4);
          --z;
          CPPUNIT_ASSERT(false);
        } catch (...) {
          CPPUNIT_ASSERT(true);
        }

        x.deallocate(a, s);
    }

    // ----
    // deallocate_test1
    // ----

    void deallocate_test1 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        // testing construct
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v); 

        x.destroy(p);

        x.deallocate(p, s);
        CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == 92);
        CPPUNIT_ASSERT(x.readSentinel(&x.a[96]) == 92);
    }

    // ----
    // deallocate_test2
    // ----

    void deallocate_test2 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        // testing construct
        x.construct(p, v);
        x.construct(q, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v);

        x.destroy(q);
        x.destroy(p);

        x.deallocate(q, s);
        x.deallocate(p, s);
        CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == 92);
        CPPUNIT_ASSERT(x.readSentinel(&x.a[96]) == 92);
    }

    // ----
    // deallocate_test3
    // ----

    void deallocate_test3 () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         q = x.allocate(s);
        const pointer         r = x.allocate(s);
        // testing construct
        x.construct(p, v);
        x.construct(q, v);
        x.construct(r, v);
        CPPUNIT_ASSERT(*p == v); 
        CPPUNIT_ASSERT(*q == v);
        CPPUNIT_ASSERT(*r == v);

        x.destroy(q);
        x.destroy(p);
        x.destroy(r);

        x.deallocate(q, s);
        x.deallocate(p, s);
        x.deallocate(r, s);

        CPPUNIT_ASSERT(x.readSentinel(&x.a[0]) == 92);
        CPPUNIT_ASSERT(x.readSentinel(&x.a[96]) == 92);
    }

    CPPUNIT_TEST_SUITE(TestOURAllocator);
    CPPUNIT_TEST(mytest8);
    CPPUNIT_TEST(mytest9);
    CPPUNIT_TEST(mytest10);
    CPPUNIT_TEST(mytest11);
    CPPUNIT_TEST(mytest12);
    CPPUNIT_TEST(mytest13);
    CPPUNIT_TEST(allocator_test1);
    CPPUNIT_TEST(allocator_test2);
    CPPUNIT_TEST(allocator_test3);
    CPPUNIT_TEST(constructor_test1);
    CPPUNIT_TEST(constructor_test2);
    CPPUNIT_TEST(constructor_test3);
    CPPUNIT_TEST(destroy_test1);
    CPPUNIT_TEST(destroy_test2);
    CPPUNIT_TEST(destroy_test3);
    CPPUNIT_TEST(deallocate_test1);
    CPPUNIT_TEST(deallocate_test2);
    CPPUNIT_TEST(deallocate_test3);
    CPPUNIT_TEST(test_valid1);
    CPPUNIT_TEST(test_valid2);
    CPPUNIT_TEST(test_valid3);
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
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!
    tr.addTest(TestOURAllocator< Allocator<int, 100> >::suite()); 

    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!
    tr.addTest(TestOURAllocator< Allocator<double, 100> >::suite()); 

    tr.run();

    cout << "Done." << endl;
    return 0;}
