#include "gtest-1.8.1/gtest.h"
#include "../src/List.h"

TEST(lista_test, empty_constructor_test) {
    List l;
    ASSERT_EQ(l.length(), 0);
}

TEST(lista_test, pushFront_test) {
    List l;
    l.pushFront(42);
    ASSERT_EQ(l.length(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, pushBack_test) {
    List l;
    l.pushBack(42);
    ASSERT_EQ(l.length(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, push_several_front_test) {
    List l;
    l.pushFront(42);
    l.pushFront(41);
    l.pushFront(40);
    l.pushFront(39);
    ASSERT_EQ(l.length(), 4);
    ASSERT_EQ(l.iesimo(0), 39);
    ASSERT_EQ(l.iesimo(1), 40);
    ASSERT_EQ(l.iesimo(2), 41);
    ASSERT_EQ(l.iesimo(3), 42);
}

TEST(lista_test, push_several_back_test) {
    List l;
    l.pushBack(42);
    l.pushBack(43);
    l.pushBack(44);
    l.pushBack(45);
    ASSERT_EQ(l.length(), 4);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 43);
    ASSERT_EQ(l.iesimo(2), 44);
    ASSERT_EQ(l.iesimo(3), 45);
}

TEST(lista_test, push_several_front_back_test) {
    List l;
    l.pushFront(42);
    l.pushFront(41);
    l.pushBack(43);
    l.pushFront(40);
    l.pushBack(44);
    ASSERT_EQ(l.length(), 5);
    ASSERT_EQ(l.iesimo(0), 40);
    ASSERT_EQ(l.iesimo(1), 41);
    ASSERT_EQ(l.iesimo(2), 42);
    ASSERT_EQ(l.iesimo(3), 43);
    ASSERT_EQ(l.iesimo(4), 44);
}

TEST(lista_test, remove_elements_test) {
    List l;
    l.pushBack(42);
    l.pushBack(43);
    l.pushBack(44);
    l.pushBack(45);

    l.remove(1);

    ASSERT_EQ(l.length(), 3);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);
    ASSERT_EQ(l.iesimo(2), 45);

    l.remove(2);

    ASSERT_EQ(l.length(), 2);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);

    l.remove(0);
    l.remove(0);

    ASSERT_EQ(l.length(), 0);
}

TEST(lista_test, constructor_by_copy) {
    List l;
    l.pushBack(42);
    l.pushBack(43);
    l.pushBack(44);
    l.pushBack(45);

    List otra(l);
    ASSERT_EQ(otra.length(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);
}

TEST(lista_test, asignation) {
    List l;
    l.pushBack(42);
    l.pushBack(43);
    l.pushBack(44);
    l.pushBack(45);

    List otra = l;
    ASSERT_EQ(otra.length(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);

    // test pisar memoria preexistente
    l.remove(0);
    otra = l;
    ASSERT_EQ(otra.length(), 3);

    otra = List();
    ASSERT_EQ(otra.length(), 0);
}

