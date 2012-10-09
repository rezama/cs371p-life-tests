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
     x.deallocate(p, s);
   }

    // --------
    // test_two
    // --------    
	
    void test_two () {
      A x;
      const difference_type s = 10;
      const value_type      v = 2;
      const pointer         b = x.allocate(s);
      pointer         e = b + s;
      pointer         p = b;
      try {
        while (p != e) {
          x.construct(p, v);
          ++p;}
	  }
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
      
    // ----------
	// test_three
	// ----------
    	
	void test_three() {
	  A x;	  
	  const difference_type s = 23;
	  const value_type v = 5;
	  try {
	  	const pointer b = x.allocate(s);
		  pointer e = b + s;
		  pointer p = b;
		  while (p != e) {
			  x.construct(p, v);
			  ++p;
		  }   
	    while (e != b) {
	  	  --e;
		    x.destroy(e);
		  }
		  x.deallocate(b, s);
      }
	  catch(std::bad_alloc& e) {
	    CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
	  }
	}


  // ---------
  // test_four
  // ---------
  void test_four () {
    A x;
    const difference_type s = 2;
    const value_type      v = 15;
  
    const pointer   p_one = x.allocate(s);    
    x.construct(p_one, v); 
    x.construct(p_one + 1, v);
  
    const pointer   p_two = x.allocate(s);    
    x.construct(p_two, v);
    x.construct(p_two + 1, v); 
   
    // new difference_type increased to 4
    const difference_type s1 = 4;

    const pointer   p_three = x.allocate(s1);    
    x.construct(p_three, v);
    x.construct(p_three + 1, v);
    x.construct(p_three + 2, v);
    x.construct(p_three + 3, v); 
    
    // should throw exception for double, not int
    try { 
	  const pointer  p_four = x.allocate(s);    
      x.construct(p_four, v + 10);
      x.construct(p_four + 1, v + 10);
      x.destroy(p_four);
      x.destroy(p_four + 1);
      x.deallocate(p_four, s); 
    }
    catch(std::bad_alloc& e) {
      CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
    }
    
    //destroy pointer one
    x.destroy(p_one);
    x.destroy(p_one + 1);
    x.deallocate(p_one, s);
    
    //destroy p_two
    x.destroy(p_two);
    x.destroy(p_two + 1);
    x.deallocate(p_two, s);
    
    //destroy p_three
    x.destroy(p_three); 
    x.destroy(p_three + 1); 
    x.destroy(p_three + 2); 
    x.destroy(p_three + 3); 
    x.deallocate(p_three, 4);
    
  }
   

	// ---------
    // test_five
    // ---------

    void test_five () {
      A x;      
	  const difference_type s = 1;
      const value_type      v = 5;
      const pointer         p = x.allocate(s);
      
	  x.construct(p, v);
      CPPUNIT_ASSERT(*p == v);
      x.destroy(p);
      x.deallocate(p, s);

      const pointer  p_one = x.allocate(6);      
	  x.construct(p_one, v);
      CPPUNIT_ASSERT(*p_one == v);
      x.destroy(p_one);
      x.deallocate(p_one, 6);

      const pointer p_two = x.allocate(8);
      
	  x.construct(p_two, v);
      CPPUNIT_ASSERT(*p_two == v);
      x.destroy(p_two);
      x.deallocate(p_two, 8);
    }


    // --------
	// test_six
	// --------
    // should faile regardless of type, too large.
	void test_six() {
 	  A x;
      const difference_type s = 100;
      try {
	    const pointer  p = x.allocate(s);
	    x.deallocate(p, s);
	  }
	  catch(std::bad_alloc& e) {
	     CPPUNIT_ASSERT(true);
	  }
	}


    // ---------
	// test_seven
	// ---------
	
    //tests edge case of 23 ints, allocating and deallocating some
    void test_seven () {    
      A x;
      const difference_type s = 1;
      const value_type      v = 2;
      const pointer         p = x.allocate(s);    
      x.construct(p, v); 
      x.destroy(p);
      x.deallocate(p, s); 
    
      const pointer  p_one = x.allocate(6);
        x.deallocate(p_one, 6); 
      try {
          const pointer    p_two = x.allocate(22);
          x.deallocate(p_two, 22);
          const pointer   p_three = x.allocate(1);
          x.deallocate(p_three, 1); 
        }   
      catch(std::bad_alloc& e){ 
          CPPUNIT_ASSERT(true);
      }   
    }   


	// ---------
	// test_eight
	// ---------

    void test_eight() {
      A x;   
	  const pointer p = x.allocate(0);
	  x.deallocate(p, 0);
      CPPUNIT_ASSERT(p);
	}

    // ---------
	// test_nine
	// ---------

	void test_nine() {
	  A x;	  
	  const difference_type s = 9;
	  const pointer  p = x.allocate(s);
	  const pointer  p_one = x.allocate(1);
	  
	  try {
	  	const pointer p_two = x.allocate(1);
	  	x.deallocate(p_two, 1);
	  }
	  catch(std::bad_alloc& e) {
	  	CPPUNIT_ASSERT(typeid(value_type) == typeid(double));	  	
	  }
	  x.deallocate(p, s);
	  x.deallocate(p_one, 1);
	   			  	  	  	
	}
	
	// -------
	// test_ten
	// --------
	
	void test_ten(){
       A x;
       CPPUNIT_ASSERT(x.a[0] == 92);
    }
    
    // ----------
    // test_eleven
    // -----------
    
    void test_eleven(){
       A x;
       CPPUNIT_ASSERT(x.a[96] == 92);
    }
	
	// ----------
	// test_twelve
	// -----------
    void test_twelve(){
       A x;
       const pointer b = x.allocate(1);
       CPPUNIT_ASSERT(b != 0);
       if(typeid(value_type) == typeid(int)){
             CPPUNIT_ASSERT(x.a[0] == -4);
             CPPUNIT_ASSERT(x.a[8] == -4);
             CPPUNIT_ASSERT(x.a[12] == 80);
       }
       else if(typeid(value_type) == typeid(double)) {
             CPPUNIT_ASSERT(x.a[0] == -8);
             CPPUNIT_ASSERT(x.a[12] == -8);
             CPPUNIT_ASSERT(x.a[16] == 76);
       }
       else CPPUNIT_ASSERT(false);
   }
   
	// -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
	CPPUNIT_TEST(test_two);
    CPPUNIT_TEST(test_three);
    CPPUNIT_TEST(test_four);
	CPPUNIT_TEST(test_five);
    CPPUNIT_TEST(test_six);
	CPPUNIT_TEST(test_seven);
	CPPUNIT_TEST(test_eight);
	CPPUNIT_TEST(test_nine);
	CPPUNIT_TEST(test_ten);
	CPPUNIT_TEST(test_eleven);	
	CPPUNIT_TEST(test_twelve);
	CPPUNIT_TEST_SUITE_END();
 };
// ----
// main
// ----

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
  cout << "TestAllocator.c++" << endl;

  CppUnit::TextTestRunner tr;

  
  //tr.addTest(TestAllocator< std::allocator<int> >::suite());
  tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

  //tr.addTest(TestAllocator< std::allocator<double> >::suite());
  tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!
  
  
  tr.run();

  cout << "Done." << endl;
  return 0;}

