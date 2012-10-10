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
// -----------------------------------
// Redefine to test private attributes
// -----------------------------------
#define private public
#define HEAP_SIZE 100
// --------
// includes
// --------
#include <algorithm> // count
#include <memory>    // allocator
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include "Allocator.h"

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
    typedef typename A::size_type size_type;

    /**
     * test private valid method
     */
    void test_valid_1() {
        A x;
        CPPUNIT_ASSERT(x.valid());
        x.a[0] = -20;
        CPPUNIT_ASSERT(!x.valid());
    }

    void test_valid_2() {
        A x;

        const int num = (HEAP_SIZE - 2 * SENTINEL_SIZE) / sizeof(value_type);
        CPPUNIT_ASSERT(x.valid());
        x.allocate(num);
        CPPUNIT_ASSERT(x.valid());
        CPPUNIT_ASSERT( x.a[0] == - (HEAP_SIZE - 2*SENTINEL_SIZE));
    }

    void test_valid_3() {
        A x;
        CPPUNIT_ASSERT(x.valid());
        x.allocate(5);
        CPPUNIT_ASSERT(x.valid());
    }

    /**
     * test private helper method: find
     */

    void test_find_1() {
        A x;

        const int num = (HEAP_SIZE - 2 * SENTINEL_SIZE) / sizeof(value_type);
        char* found = x.find(num);
        CPPUNIT_ASSERT( found == &x.a[0]);
    }

    void test_find_2() {
        A x;

        const int num = (HEAP_SIZE - 4 * SENTINEL_SIZE - sizeof(value_type))
                / sizeof(value_type);
        x.allocate(num);
        char* found = x.find(1);
        CPPUNIT_ASSERT( found);
    }

    void test_find_3() {
        A x;

        const int num = (HEAP_SIZE - 6 * SENTINEL_SIZE - 2 * sizeof(value_type))
                / sizeof(value_type);
        x.allocate(num);
        x.allocate(1);
        char* found = x.find(1);
        CPPUNIT_ASSERT( found);
    }

    /**
     * test private helper method: merge
     */
    void test_merge_1() {
        A x;

        const int s[] = { 1, 2, 3, 1 };
        const int num = 4;
        pointer p[num];
        for (int i = 0; i < num; ++i)
            p[i] = x.allocate(s[i]);

        char* pa = &x.a[0];
        int block;
        for (int i = 0; i < num; ++i) {
            block = abs((int) *pa);
            *pa = block;
            pa = pa + SENTINEL_SIZE + block;
            *pa = block;
            pa = pa + SENTINEL_SIZE;
        }
        x.merge();
        CPPUNIT_ASSERT( x.a[0] = HEAP_SIZE - 2*SENTINEL_SIZE);
    }

    void test_merge_2() {
        A x;

        const int s[] = { 1, 1, 1 };
        const int num = 3;
        pointer p[num];
        for (int i = 0; i < num; ++i)
            p[i] = x.allocate(s[i]);

        char* pa = &x.a[0];
        int block;
        for (int i = 0; i < num; ++i) {
            block = abs((int) *pa);
            *pa = block;
            pa = pa + SENTINEL_SIZE + block;
            *pa = block;
            pa = pa + SENTINEL_SIZE;
        }
        x.merge();
        CPPUNIT_ASSERT( x.a[0] = HEAP_SIZE - 2*SENTINEL_SIZE);
    }

    void test_merge_3() {
        A x;

        const int s[] = { 1, 2, 2, 1 };
        const int num = 4;
        pointer p[num];
        for (int i = 0; i < num; ++i)
            p[i] = x.allocate(s[i]);

        char* pa = &x.a[0];
        int block;
        for (int i = 0; i < num; ++i) {
            block = abs((int) *pa);
            *pa = block;
            pa = pa + SENTINEL_SIZE + block;
            *pa = block;
            pa = pa + SENTINEL_SIZE;
        }
        x.merge();
        CPPUNIT_ASSERT( x.a[0] = HEAP_SIZE - 2*SENTINEL_SIZE);
    }

    /**
     * test max_size method
     */
    void test_max_size_1() {
        A x;
        CPPUNIT_ASSERT(x.max_size()>=1);
    }

    void test_max_size_2() {
        A x;
        int expected;

        expected = (HEAP_SIZE - 2 * SENTINEL_SIZE) / sizeof(value_type);
        CPPUNIT_ASSERT(expected == x.max_size());
        /* allocating*/
    }

    void test_max_size_3() {
        A x;
        int num = 3;

        int expected =
                (HEAP_SIZE - num * sizeof(value_type) - 4 * SENTINEL_SIZE)
                        / sizeof(value_type);
        x.allocate(num);
        CPPUNIT_ASSERT(expected == x.max_size());

    }
    /**
     * test allocate method
     */
    void test_allocate_1() {
        A x;
        int num = 5;

        int expected =
                (HEAP_SIZE - num * sizeof(value_type) - 4 * SENTINEL_SIZE)
                        / sizeof(value_type);
        x.allocate(num);
        CPPUNIT_ASSERT(expected == x.max_size());
    }

    void test_allocate_2() {
        A x;
        int num = 5;

        int expected =
                (HEAP_SIZE - num * sizeof(value_type) - 4 * SENTINEL_SIZE)
                        / sizeof(value_type);
        x.allocate(num);
        CPPUNIT_ASSERT(expected == x.max_size());
        int num2 = 2;
        expected = (HEAP_SIZE - (num2 + num) * sizeof(value_type)
                - 6 * SENTINEL_SIZE) / sizeof(value_type);
        x.allocate(num2);
        CPPUNIT_ASSERT(expected == x.max_size());
    }

    void test_allocate_3() {
        A x;
        int num = 1;

        int expected =
                (HEAP_SIZE - num * sizeof(value_type) - 4 * SENTINEL_SIZE)
                        / sizeof(value_type);
        x.allocate(num);
        CPPUNIT_ASSERT(expected == x.max_size());
        int num2 = 1;
        expected = (HEAP_SIZE - (num2 + num) * sizeof(value_type)
                - 6 * SENTINEL_SIZE) / sizeof(value_type);
        x.allocate(num2);
        CPPUNIT_ASSERT(expected == x.max_size());
    }

    /**
     * test construct method
     */
    void test_construct_1() {
        A x;
        const difference_type s = 1;
        const value_type v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
    }

    void test_construct_2() {
        A x;
        const difference_type s = 2;
        const value_type v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        x.construct(p + 1, v - 1);
        CPPUNIT_ASSERT(*p == v);
        CPPUNIT_ASSERT(*(p+1) == v - 1);
    }

    void test_construct_3() {
        A x;
        const difference_type s = 2;
        const value_type v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        const pointer q = x.allocate(s + 1);
        x.construct(q, v + 1);
    }

    /**
     * test deallocate method
     */
    void test_deallocate_1() {
        A x;
        const difference_type s = 3;
        const pointer p = x.allocate(s);
        x.deallocate(p, s);
        const pointer q = x.allocate(s);
        CPPUNIT_ASSERT(p == q);
        x.deallocate(q, s);
    }

    void test_deallocate_2() {
        A x;
        const int s[] = { 1, 2, 3 };
        pointer p[3];
        for (int i = 0; i < 3; ++i)
            p[i] = x.allocate(s[i]);
        x.deallocate(p[0], s[0]);
        x.deallocate(p[2], s[2]);
        x.deallocate(p[1], s[1]);

        int expected = (HEAP_SIZE - 2 * SENTINEL_SIZE) / sizeof(value_type);
        CPPUNIT_ASSERT(expected == x.max_size());
    }

    void test_deallocate_3() {
        A x;
        const int s[] = { 1, 2, 3, 1 };
        const int num = 4;
        pointer p[num];
        for (int i = 0; i < num; ++i)
            p[i] = x.allocate(s[i]);
        x.deallocate(p[0], s[0]);
        x.deallocate(p[2], s[2]);
        x.deallocate(p[3], s[3]);
        int expected = (HEAP_SIZE - 6 * SENTINEL_SIZE - 3 * sizeof(value_type))
                / sizeof(value_type);
        CPPUNIT_ASSERT(expected == x.max_size());
        x.allocate(s[0]);
    }

    void test_deallocate_4() {
        A x;
        const int s[] = { 1, 2, 3, 1 };
        const int num = 4;
        pointer p[num];
        for (int i = 0; i < num; ++i)
            p[i] = x.allocate(s[i]);
        x.deallocate(p[0], s[0]);
        x.deallocate(p[1], s[1]);
        x.deallocate(p[3], s[3]);
        int expected = -x.a[0];
        x.allocate(s[0] + s[1]);
        CPPUNIT_ASSERT(expected == x.a[0]);
    }

    /**
     * test destroy method by
     * running deallocation and allocation
     */
    void test_destroy_1() {
        A x;
        pointer p = x.allocate(2);
        x.construct(p, 2);
        x.destroy(p);
        x.construct(p, 1);
        x.deallocate(p);
    }

    void test_destroy_2() {
        A x;
        pointer p = x.allocate(1);
        x.construct(p, 20);
        x.destroy(p);
        x.construct(p, 1);
        x.deallocate(p);
    }

    void test_destroy_3() {
        A x;
        pointer p = x.allocate(3);
        x.construct(p, 29);
        x.destroy(p);
        x.construct(p, 1);
        x.deallocate(p);
    }

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

    void test_ten() {
        A x;
        const difference_type s = 10;
        const value_type v = 20;
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
        CPPUNIT_TEST(test_max_size_1);
        CPPUNIT_TEST(test_max_size_2);
        CPPUNIT_TEST(test_max_size_3);
        CPPUNIT_TEST(test_find_1);
        CPPUNIT_TEST(test_find_2);
        CPPUNIT_TEST(test_find_3);
        CPPUNIT_TEST(test_merge_1);
        CPPUNIT_TEST(test_merge_2);
        CPPUNIT_TEST(test_merge_3);
        CPPUNIT_TEST(test_allocate_1);
        CPPUNIT_TEST(test_allocate_2);
        CPPUNIT_TEST(test_allocate_3);
        CPPUNIT_TEST(test_construct_1);
        CPPUNIT_TEST(test_construct_2);
        CPPUNIT_TEST(test_construct_3);
        CPPUNIT_TEST(test_deallocate_1);
        CPPUNIT_TEST(test_deallocate_2);
        CPPUNIT_TEST(test_deallocate_3);
        CPPUNIT_TEST(test_deallocate_4);
        CPPUNIT_TEST(test_destroy_1);
        CPPUNIT_TEST(test_destroy_2);
        CPPUNIT_TEST(test_destroy_3);
        CPPUNIT_TEST(test_valid_1);
        CPPUNIT_TEST(test_valid_2);
        CPPUNIT_TEST(test_valid_3);
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

//    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    tr.addTest(TestAllocator<Allocator<int, 100> >::suite());

//    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator<Allocator<double, 100> >::suite());
    tr.addTest(TestAllocator<Allocator<char, 100> >::suite());

    tr.run();

    cout << "Done." << endl;
    return 0;
}
