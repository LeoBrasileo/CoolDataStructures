#include "gtest-1.8.1/gtest.h"
#include "../src/Set.h"


/**
 * Test simple básico
 */
TEST(set_test, empty_set) {
    Set<int> c;
    EXPECT_EQ(c.cardinal(), 0);
}


TEST(set_test, one_value_insert) {
    Set<int> c;
    c.insert(5);
    EXPECT_EQ(c.cardinal(), 1);
}


TEST(set_test, five_values_insert) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    EXPECT_EQ(c.cardinal(), 5);
}

TEST(set_test, belong_test) {
  Set<int> c;
  
  for (int i = 0; i < 5; i++) {
    EXPECT_FALSE(c.in(i));
  }

  // Agrego el 3
    c.insert(3);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(c.in(i), i == 3);
  }

  // Agrego el 3
    c.insert(5);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(c.in(i), i == 3);
  }
  EXPECT_TRUE(c.in(5));

}

TEST(set_test, insert_remove_one_value_test) {
    Set<int> c;
    c.insert(5);
    c.remove(5);
    EXPECT_EQ(c.cardinal(), 0);
    c.insert(5);
    EXPECT_EQ(c.cardinal(), 1);
}

TEST(set_test, minimum_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    EXPECT_EQ(c.min(), 4);
}

TEST(set_test, maximum_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    EXPECT_EQ(c.max(), 8);
}

TEST(set_test, remove_one_child_case_test) {
    Set<int> c;
    c.insert(5);
    c.insert(6);
    c.insert(7);
    c.remove(6);
    EXPECT_EQ(c.cardinal(), 2);
}

TEST(set_test, remove_two_child_case_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    c.remove(7);
    EXPECT_EQ(c.cardinal(), 4);
}

TEST(set_test, remove_two_child_root_case_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    c.remove(5);
    EXPECT_EQ(c.cardinal(), 4);
}


TEST(set_test, remove_two_child_double_case_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(20);
    c.insert(15);
    c.insert(12);
    c.insert(16);
    c.insert(24);
    c.insert(22);
    c.insert(25);
    c.remove(20);
    EXPECT_EQ(c.cardinal(), 8);
}

TEST(set_test, next_inorder_test) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(20);
    c.insert(15);
    c.insert(12);
    c.insert(16);
    c.insert(24);
    c.insert(22);
    c.insert(25);

    EXPECT_EQ(c.next(20), 22);
    EXPECT_EQ(c.next(4), 5);
    EXPECT_EQ(c.next(15), 16);
}

const int NCLAVES = 1000;

int clave(int i) {
	return NCLAVES * ((i * i - 100 * i) % NCLAVES) + i;
}

TEST(set_test, test_stress) {
    Set<int> c;

    // Insertar
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_EQ(c.cardinal(), i);
	    ASSERT_FALSE(c.in(k));
        c.insert(k);
	    ASSERT_TRUE(c.in(k));
    }
    ASSERT_EQ(c.cardinal(), NCLAVES);

    // Insertar de nuevo
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_TRUE(c.in(k));
        c.insert(k);
	    ASSERT_TRUE(c.in(k));
	    ASSERT_EQ(c.cardinal(), NCLAVES);
    }

    // Eliminar los valores para i par
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_TRUE(c.in(k));
	    if (i % 2 == 0) {
            c.remove(k);
	    	ASSERT_FALSE(c.in(k));
	    }
    }
    ASSERT_EQ(c.cardinal(), NCLAVES / 2);

    // Eliminar los valores para i impar
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    if (i % 2 == 0) {
	    	ASSERT_FALSE(c.in(k));
	    } else {
	    	ASSERT_TRUE(c.in(k));
            c.remove(k);
	    	ASSERT_FALSE(c.in(k));
	    }
    }
    ASSERT_EQ(c.cardinal(), 0);

    // Verificar que no haya valores
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_FALSE(c.in(k));
    }
}

TEST(set_test, inorder_elements) {
    Set<int> c;
    c.insert(5);
    c.insert(4);
    c.insert(7);
    c.insert(6);
    c.insert(8);
    vector<int> v = {4,5,6,7,8};
    EXPECT_EQ(c.inorder_keys(), v);
}
