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

#include <iostream>
#include <algorithm> // count
#include <memory>    // allocator
#include <string>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

// cancel C++ encapsulation
#define private public // enable access to private vars/methods for testing
#define protected public // enable access to protected vars/methods for testing
#define class struct 
#define RAND_SIZE 23

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
      const difference_type s = 1; // how many to make
      const value_type      v = 9999; // what value to put into the allocated space
      const pointer         p = x.allocate(s); // allocate s many types
      x.construct(p, v); // construct with value v at pointer
      CPPUNIT_ASSERT(*p == v); // v is in little endian on 32-bit cs linux machine
      x.destroy(p);
      x.deallocate(p, s);
    }

    // -------------
    // test_allocate
    // -------------
    void test_alloc_one () {
      A x;
      try{
        const pointer p = x.allocate(1);
        x.destroy(p);
        x.deallocate(p, 1);
        CPPUNIT_ASSERT(true);
      } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(false); }
    }

    void test_alloc_fail_nospace () {
      A x;
      size_t word_size = -1;
      try{
        const pointer p = x.allocate(word_size);
        x.destroy(p);
        CPPUNIT_ASSERT(false);
      } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(true); }
    }

    void test_alloc_fail_neg () {
      A x;
      try{
        const pointer p = x.allocate(-4);
        x.destroy(p);
        CPPUNIT_ASSERT(false);
      } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(true); }
    }
   
    void test_alloc_zero () {
      A x;
      try{
        const pointer p = x.allocate(0);
        x.construct(p, 888);
        x.destroy(p);
        x.deallocate(p, 888);
        CPPUNIT_ASSERT(*p == 888);
      } catch (...) { CPPUNIT_ASSERT(false); }
    }
/*  
    // WHY DOES THIS WORK FOR STD::ALLOCATOR
    void test_alloc_zero_WTF () {
      A x;
      const difference_type s = 0;
      const value_type v = 888;
      const pointer b = x.allocate(s);
      pointer e = b + 5;
      pointer p = b;

      try {
        while (p != e) {
          x.construct(p, v);
          std::cout << "filling p, p = " << *p << std::endl;
          ++p;
        }
      } catch (...) {
        while (b != p) {
           --p;
           x.destroy(p);}
           x.deallocate(b, s);
           std::cout << "shit." << std::endl;
           throw;
      } 
      std::cout << std::count(b, e, 5) << std::endl;
    }
*/
    // --------------
    // test_construct
    // --------------
    void test_construct_one () {
      A x;
      const pointer b = x.allocate(1);
      x.construct(b, 11);
      CPPUNIT_ASSERT(*b == 11);
      x.deallocate(b, 1);
    }

    void test_construct_two () {
      A x;
      const pointer b = x.allocate(2);
      pointer p = b;
      pointer e = p+2;
      while (p != e) {
        x.construct(p, 88);
        p++; 
      }
      CPPUNIT_ASSERT(std::count(b, e, 88) == 2);
      x.deallocate(b, 2);
    }
   
    void test_construct_multi () {
      A x;
      const pointer b1 = x.allocate(3);
      const pointer b2 = x.allocate(3);
      pointer p1 = b1;
      pointer e1 = p1+3;
      pointer p2 = b2;
      pointer e2 = p2+3;
      while (p1 != e1) {
        x.construct(p1, 96);
        p1++;
      }
      CPPUNIT_ASSERT(std::count(b1, e1, 96) == 3);
      
      while (p1 != b1) {
        --p1;
        x.destroy(p1);
      }
      while (p2 != e2) {
        x.construct(p2, 69);
        p2++;
      }
      CPPUNIT_ASSERT(std::count(b2, e2, 69) == 3);
      while (p2 != b2) {
        --p2;
        x.destroy(p2);
      }
      x.deallocate(b1, 3); x.deallocate(b2, 3);
    }

    // ------------
    // test_destroy
    // ------------
    void test_destroy_one () {
      A x;
      const pointer b = x.allocate(1);
      x.construct(b, 88);
      ++*b;
      CPPUNIT_ASSERT(*b == 89);
      x.destroy(b);
      try {
        value_type v = *b;
        v++;
        CPPUNIT_ASSERT(false);
      } catch (...) { 
        x.deallocate(b,1);
        CPPUNIT_ASSERT(true); }
    }

    void test_destroy_two () {
      A x;
      const pointer b = x.allocate(2);
      pointer b1 = b+1;
      x.construct(b, 88);
      x.construct(b1, 89);
      ++*b; ++*b1;
      CPPUNIT_ASSERT(*b == 89 && *b1 == 90);
      x.destroy(b);
      x.destroy(b1);
      try {
        value_type v = *b1; value_type u = *b;
        v++; u++;
        CPPUNIT_ASSERT(false);
      } catch (...) { 
        x.deallocate(b,1);
        CPPUNIT_ASSERT(true); }
    }

    void test_destroy_multi () {
      A x;
      const pointer b = x.allocate(1);
      const pointer b1 = x.allocate(1);
      x.construct(b, 88); x.construct(b1, 99);
      CPPUNIT_ASSERT(*b == 88 && *b1 == 99);
      x.destroy(b); x.destroy(b1);
      try {
        value_type v = *b1; value_type u = *b;
        v++; u++;
        CPPUNIT_ASSERT(false);
      } catch (...) { 
        x.deallocate(b,1); x.deallocate(b1,1);
        CPPUNIT_ASSERT(true); }
    }
   
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

    // ---------
    // test_fill
    // ---------
    void test_fill () {
      A x;
      const difference_type s = 1; 
      const value_type v = 2;
      const difference_type t = 1;
      const value_type u = 3;
      const difference_type r = 1;
      const value_type w = 4;
      
      try {
        const pointer p0 = x.allocate(s);
        x.construct(p0, v);
        CPPUNIT_ASSERT(*p0 == v);
        
        const pointer p1 = x.allocate(t);
        x.construct(p1, u);
        CPPUNIT_ASSERT(*p1 == u);
        
        const pointer p2 = x.allocate(r);
        x.construct(p2, w);
        CPPUNIT_ASSERT(*p2 == w);
      
        x.destroy(p0); x.destroy(p1); x.destroy(p2);
        x.deallocate(p0, s); x.deallocate(p1, t); x.deallocate(p2, r);
      } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(true); }
    }
    
    // -------------
    // test_coalesce
    // -------------
    void test_coalesce () {
      A x;
      size_t sizeT = sizeof(value_type);

      const difference_type r = 8/sizeT;
      const value_type v = 1;
      const pointer p0 = x.allocate(r);
      x.construct(p0, v);
      CPPUNIT_ASSERT(*p0 == v);

      const value_type u = 2;
      const pointer p1 = x.allocate(r);
      x.construct(p1, u);
      CPPUNIT_ASSERT(*p1 == u);

      const difference_type s = 16/sizeT;
      const value_type w = 3;
      const pointer p2 = x.allocate(s);
      x.construct(p2, w);
      CPPUNIT_ASSERT(*p2 == w);
      
      x.destroy(p0); x.deallocate(p0, r);
      x.destroy(p1); x.deallocate(p1, r); // free memory, should coalesce p0 and p1

      const pointer p3 = x.allocate(16/sizeT);
      x.construct(p3, w);
      CPPUNIT_ASSERT(*p3 == w);
      
      std::allocator<value_type> std_a;
      std::string str1 = typeid(std_a).name();
      std::string str2 = typeid(x).name();
  
      x.destroy(p3); x.deallocate(p3, s);
      x.destroy(p2); x.deallocate(p2, s); // free everything
      const difference_type t = (RAND_SIZE-(2*sizeof(int))) / sizeT;
      const pointer p4 = x.allocate(t); 
      pointer b = p4;
      pointer e = b+t;
      try {
        while (b != e) {
          x.construct(b, v); // fill entire array
          CPPUNIT_ASSERT(*b == v);
          b++;
        }
      } catch (...) {
        while (b != p4) {
          --b;
          x.destroy(b);
        }
        x.deallocate(b, t);
        throw;
      }
      CPPUNIT_ASSERT(std::count(p4, e, v) == t);
      x.destroy(p4); x.deallocate(p4, t);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);

    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_alloc_one);
    CPPUNIT_TEST(test_alloc_fail_nospace);
    CPPUNIT_TEST(test_alloc_fail_neg);
//    CPPUNIT_TEST(test_alloc_zero);

    CPPUNIT_TEST(test_construct_one);
    CPPUNIT_TEST(test_construct_two);
    CPPUNIT_TEST(test_construct_multi);

    CPPUNIT_TEST(test_destroy_one);
    CPPUNIT_TEST(test_destroy_two);
    CPPUNIT_TEST(test_destroy_multi);
    CPPUNIT_TEST(test_fill);
    CPPUNIT_TEST(test_coalesce);
   
    CPPUNIT_TEST_SUITE_END(); };


template <typename A>
struct TestFisherPriceAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;

    // -------------------------------------------------
    // test allocate and construct for capacity of array
    // -------------------------------------------------
    void test_alloc_cons_capacity () {
      A x;
      try{
        const difference_type s = x.max_size / sizeof(value_type);
        const value_type v = 8;
        const pointer b = x.allocate(s);
        pointer p = b;
        pointer e = b + s;
        try {
          while (p != e) {
                x.construct(p, v);
                ++p;}
        } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(false); }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
      } catch (std::bad_alloc& e) { CPPUNIT_ASSERT(false); }
      CPPUNIT_ASSERT(true);    
    }

    // ---------------
    // test_deallocate
    // ---------------
    void test_dealloc_one () {
      A x;
      const pointer b = x.allocate(1);
      x.destroy(b); x.deallocate(b);     
    }

    void test_dealloc_two () {
      A x;
      const pointer b = x.allocate(1);
      const pointer b1 = x.allocate(2);
      x.deallocate(b); x.deallocate(b1); 
    }

    void test_dealloc_three () {
      A x;
      const pointer b = x.allocate(2);
      const pointer b1 = x.allocate(2);
      const pointer b2 = x.allocate(2);
      x.deallocate(b); x.destroy(b);
      x.deallocate(b2); x.destroy(b2);
      x.deallocate(b1); x.destroy(b1);
    }
    
    // -------------
    // test_coalesce
    // -------------
    void test_coalesce () {
      A x;
      size_t sizeT = sizeof(value_type);

      const difference_type r = 8/sizeT;
      const value_type v = 1;
      const pointer p0 = x.allocate(r);
      x.construct(p0, v);
      CPPUNIT_ASSERT(*p0 == v);

      const value_type u = 2;
      const pointer p1 = x.allocate(r);
      x.construct(p1, u);
      CPPUNIT_ASSERT(*p1 == u);

      const difference_type s = 16/sizeT;
      const value_type w = 3;
      const pointer p2 = x.allocate(s);
      x.construct(p2, w);
      CPPUNIT_ASSERT(*p2 == w);
      
      x.destroy(p0); x.deallocate(p0, r);
      x.destroy(p1); x.deallocate(p1, r); // free memory, should coalesce p0 and p1

      const pointer p3 = x.allocate(16/sizeT);
      x.construct(p3, w);
      CPPUNIT_ASSERT(*p3 == w);
      CPPUNIT_ASSERT(p3 == p0); // should have allocated in newly freed/coalesced region

      x.destroy(p3); x.deallocate(p3, s);
      x.destroy(p2); x.deallocate(p2, s); // free everything
      const difference_type t = x.max_size / sizeT;
      const pointer p4 = x.allocate(t); 
      pointer b = p4;
      pointer e = b+t;
      try {
        while (b != e) {
          x.construct(b, v); // fill entire array
          CPPUNIT_ASSERT(*b == v);
          b++;
        }
      } catch (...) {
        while (b != p4) {
          --b;
          x.destroy(b);
        }
        x.deallocate(b, t);
        throw;
      }
      CPPUNIT_ASSERT(p4 == p0); // should have allocated in newly freed/coalesced region
      CPPUNIT_ASSERT(std::count(p4, e, v) == t);
      x.destroy(p4); x.deallocate(p4, t);
    }

    // ------------
    // alloc_helper
    // ------------
    void test_alloc_helper_one () {
      A x;
      int index = 0;
      int hf_value = -12;
      x.alloc_helper (index, hf_value);
      int header = x.ctoi(index);
      int footer = x.ctoi(index+12+sizeof(int));
      CPPUNIT_ASSERT(header == hf_value);
      CPPUNIT_ASSERT(footer == hf_value);
    }

    void test_alloc_helper_two () {
      A x;
      int index = 0;
      int index2 = index+12+(2*sizeof(int));
      int hf_value = -12;
      int hf_value2 = 12;
      x.alloc_helper (index, hf_value);
      x.alloc_helper (index2, hf_value2);
      int header = x.ctoi(index);
      int footer = x.ctoi(index+12+sizeof(int));
      int header2 = x.ctoi(index2);
      int footer2 = x.ctoi(index2+12+sizeof(int));
      CPPUNIT_ASSERT(header == hf_value && footer == hf_value);
      CPPUNIT_ASSERT(header2 == hf_value2 && footer2 == hf_value2);
    }

    void test_alloc_helper_all () {
      A x;
      int index = 0;
      int hf_value = -(sizeof(x.a) - (2*sizeof(int)));
      x.alloc_helper (index, hf_value);
      int header = x.ctoi(index);
      int footer = x.ctoi(index+abs(hf_value)+sizeof(int));
      CPPUNIT_ASSERT(header == hf_value && footer == hf_value);
    }

    // ----
    // ctoi
    // ----
    void test_ctoi_pos () {
      A x;
      int i = 192;
      int index = 0;
      char* c = &x.a[0];
      x.a[3] = i & 0xFF;
      CPPUNIT_ASSERT(i == x.ctoi(index));
      CPPUNIT_ASSERT(i == x.ctoi(c));
    }

    void test_ctoi_neg () {
      A x;
      int i = -99;
      int index = 0;
      char* c = &x.a[0];
      x.a[3] = i & 0xFF;
      x.a[2] = (i >> 8) & 0xFF;
      x.a[1] = (i >> 16) & 0xFF;
      x.a[0] = (i >> 24) & 0xFF;
      CPPUNIT_ASSERT(i == x.ctoi(index));
      CPPUNIT_ASSERT(i == x.ctoi(c));
    }

    void test_ctoi_zero() {
      A x;
      int i = 0;
      int index = 0;
      char* c = &x.a[0];
      x.a[3] = i & 0xFF;
      x.a[2] = (i >> 8) & 0xFF;
      x.a[1] = (i >> 16) & 0xFF;
      x.a[0] = (i >> 24) & 0xFF;
      CPPUNIT_ASSERT(i == x.ctoi(index));
      CPPUNIT_ASSERT(i == x.ctoi(c));
    }

    // -----
    // valid
    // -----
    void test_valid_init_fails_zeros () {
      A x;
      CPPUNIT_ASSERT(x.valid());
      for (unsigned int j = 0; j < sizeof(x.a); j++) {
        x.a[j] = 0;
      }
//      x.a[3] = i & 0xFF;
//      x.a[2] = (i >> 8) & 0xFF;
//      x.a[1] = (i >> 16) & 0xFF;
//      x.a[0] = (i >> 24) & 0xFF;
      CPPUNIT_ASSERT(!x.valid());
    }

    void test_valid_two () {
      A x;
      int i = -2;
      int leftovers = sizeof(x.a) - 10 - (2*sizeof(int));
      x.payload = 1; 
      x.a[3] = i & 0xFF;
      x.a[2] = (i >> 8) & 0xFF;
      x.a[1] = (i >> 16) & 0xFF;
      x.a[0] = (i >> 24) & 0xFF;
      x.a[sizeof(int)+abs(i)+3] = i & 0xFF;
      x.a[sizeof(int)+abs(i)+2] = (i >> 8) & 0xFF;
      x.a[sizeof(int)+abs(i)+1] = (i >> 16) & 0xFF;
      x.a[sizeof(int)+abs(i)+0] = (i >> 24) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+3] = leftovers & 0xFF;
      x.a[2*sizeof(int)+abs(i)+2] = (leftovers >> 8) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+1] = (leftovers >> 16) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+0] = (leftovers >> 24) & 0xFF;
      x.a[sizeof(x.a)-1] = leftovers & 0xFF;
      x.a[sizeof(x.a)-2] = (leftovers >> 8) & 0xFF;
      x.a[sizeof(x.a)-3] = (leftovers >> 16) & 0xFF;
      x.a[sizeof(x.a)-4] = (leftovers >> 24) & 0xFF;
      CPPUNIT_ASSERT(x.valid());
    }

    void test_valid_fail () {
      A x;
      int i = 69;
      int ii = 70;
      int leftovers = sizeof(x.a) - 10 - (2*sizeof(int));
      x.a[3] = i & 0xFF;
      x.a[2] = (i >> 8) & 0xFF;
      x.a[1] = (i >> 16) & 0xFF;
      x.a[0] = (i >> 24) & 0xFF;
      x.a[sizeof(int)+abs(i)+3] = ii & 0xFF;
      x.a[sizeof(int)+abs(i)+2] = (ii >> 8) & 0xFF;
      x.a[sizeof(int)+abs(i)+1] = (ii >> 16) & 0xFF;
      x.a[sizeof(int)+abs(i)+0] = (ii >> 24) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+3] = leftovers & 0xFF;
      x.a[2*sizeof(int)+abs(i)+2] = (leftovers >> 8) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+1] = (leftovers >> 16) & 0xFF;
      x.a[2*sizeof(int)+abs(i)+0] = (leftovers >> 24) & 0xFF;
      x.a[sizeof(x.a)-1] = leftovers & 0xFF;
      x.a[sizeof(x.a)-2] = (leftovers >> 8) & 0xFF;
      x.a[sizeof(x.a)-3] = (leftovers >> 16) & 0xFF;
      x.a[sizeof(x.a)-4] = (leftovers >> 24) & 0xFF;
      CPPUNIT_ASSERT(!x.valid());
    }

    // ----------
    // TEST_SUITE
    // ----------
    CPPUNIT_TEST_SUITE(TestFisherPriceAllocator);
    CPPUNIT_TEST(test_alloc_helper_one);
    CPPUNIT_TEST(test_alloc_helper_two);
    CPPUNIT_TEST(test_alloc_helper_all);
    CPPUNIT_TEST(test_ctoi_pos);
    CPPUNIT_TEST(test_ctoi_neg);
    CPPUNIT_TEST(test_ctoi_zero);
    CPPUNIT_TEST(test_valid_init_fails_zeros);
    CPPUNIT_TEST(test_valid_two);
    CPPUNIT_TEST(test_valid_fail);
    CPPUNIT_TEST(test_coalesce);
    CPPUNIT_TEST(test_alloc_cons_capacity);  
    CPPUNIT_TEST(test_dealloc_one);
    CPPUNIT_TEST(test_dealloc_two);
    CPPUNIT_TEST(test_dealloc_three);
    CPPUNIT_TEST_SUITE_END(); };

// ----
// main
// ----
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;
    
    cout << "*** TESTING STD::ALLOCATOR<INT> ***" << endl;
    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    cout << "*** TESTING ALLOCATOR<INT, 83> ***" << endl;
    tr.addTest(TestAllocator< Allocator<int, 83> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<int, 83> >::suite()); // uncomment!
    cout << "*** TESTING ALLOCATOR<INT, 100> ***" << endl;
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<int, 100> >::suite()); // uncomment!
    cout << "*** TESTING ALLOCATOR<INT, 144> ***" << endl;
    tr.addTest(TestAllocator< Allocator<int, 144> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<int, 144> >::suite()); // uncomment!

    cout << "*** TESTING STD::ALLOCATOR<DOUBLE> ***" << endl;
    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    cout << "*** TESTING ALLOCATOR<DOUBLE, 100> ***" << endl;
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<double, 100> >::suite()); // uncomment!
    cout << "*** TESTING ALLOCATOR<DOUBLE, 123> ***" << endl;
    tr.addTest(TestAllocator< Allocator<double, 123> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<double, 123> >::suite()); // uncomment!
    cout << "*** TESTING ALLOCATOR<DOUBLE, 169> ***" << endl;
    tr.addTest(TestAllocator< Allocator<double, 169> >::suite()); // uncomment!
    tr.addTest(TestFisherPriceAllocator< Allocator<double, 169> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}
