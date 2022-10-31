#include "gtest-1.8.1/gtest.h"
#include "../src/string_map.h"

TEST(string_map_test, empty) {
    string_map<int> empty;

    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(empty.count("hola"), 0);
}

TEST(string_map_test, asign) {
    string_map<int> singleton;
    singleton.insert(make_pair("hola", 1));

    EXPECT_EQ(singleton.at("hola"), 1);
    EXPECT_EQ(singleton.size(), 1);
}

TEST(string_map_test, obtain) {
    string_map<int> no_prefixes;
    string_map<int> prejixes;

    no_prefixes.insert(make_pair("hola", 1));
    no_prefixes.insert(make_pair("chau", 2));
    no_prefixes.insert(make_pair("adios", 3));

    prejixes.insert(make_pair("c", 1));
    prejixes.insert(make_pair("casa", 2));
    prejixes.insert(make_pair("casona", 3));

    EXPECT_EQ(no_prefixes.at("hola"), 1);
    EXPECT_EQ(no_prefixes.at("chau"), 2);
    EXPECT_EQ(no_prefixes.at("adios"), 3);

    EXPECT_EQ(prejixes.at("c"), 1);
    EXPECT_EQ(prejixes.at("casa"), 2);
    EXPECT_EQ(prejixes.at("casona"), 3);
}

TEST(string_map_test, redefine) {
    string_map<int> prefixes;

    prefixes.insert(make_pair("c", 1));
    prefixes.insert(make_pair("casa", 2));
    prefixes.insert(make_pair("casona", 3));

    prefixes.insert(make_pair("c", 2));
    EXPECT_EQ(prefixes.at("c"), 2);
    prefixes.insert(make_pair("c", 3));
    EXPECT_EQ(prefixes.at("c"), 3);
}

TEST(string_map_test, count) {
    string_map<int> empty;
    string_map<int> no_prefixes;
    string_map<int> prefixes;

    no_prefixes.insert(make_pair("hola", 1));
    no_prefixes.insert(make_pair("chau", 2));
    no_prefixes.insert(make_pair("adios", 3));

    prefixes.insert(make_pair("c", 1));
    prefixes.insert(make_pair("casa", 2));
    prefixes.insert(make_pair("casona", 3));

	EXPECT_FALSE(empty.count("a") == 1);
	EXPECT_FALSE(empty.count("aaaa") == 1);
	EXPECT_FALSE(empty.count("adios") == 1);

	EXPECT_TRUE(no_prefixes.count("hola") == 1);
	EXPECT_TRUE(no_prefixes.count("chau") == 1);
	EXPECT_TRUE(no_prefixes.count("adios") == 1);

	EXPECT_FALSE(no_prefixes.count("h") == 1);
	EXPECT_FALSE(no_prefixes.count("ho") == 1);
	EXPECT_FALSE(no_prefixes.count("hol") == 1);

	EXPECT_TRUE(prefixes.count("c") == 1);
	EXPECT_TRUE(prefixes.count("casa") == 1);
	EXPECT_TRUE(prefixes.count("casona") == 1);
	EXPECT_FALSE(prefixes.count("ca") == 1);
	EXPECT_FALSE(prefixes.count("cas") == 1);
	EXPECT_FALSE(prefixes.count("caso") == 1);
}

TEST(string_map_test, copy) {
    string_map<int> no_prefixes;
    string_map<int> prefixes;

    no_prefixes.insert(make_pair("hola", 1));
    no_prefixes.insert(make_pair("chau", 2));
    no_prefixes.insert(make_pair("adios", 3));

    prefixes.insert(make_pair("c", 1));
    prefixes.insert(make_pair("casa", 2));
    prefixes.insert(make_pair("casona", 3));

    string_map<int> copia(no_prefixes);

	EXPECT_TRUE(copia.count("hola") == 1);
	EXPECT_TRUE(copia.count("chau") == 1);
	EXPECT_TRUE(copia.count("adios") == 1);

	EXPECT_FALSE(copia.count("h") == 1);
	EXPECT_FALSE(copia.count("ho") == 1);
	EXPECT_FALSE(copia.count("hol") == 1);

	EXPECT_EQ(no_prefixes.at("hola"), copia.at("hola"));
	EXPECT_EQ(no_prefixes.at("chau"), copia.at("chau"));
	EXPECT_EQ(no_prefixes.at("adios"), copia.at("adios"));

	string_map<int> copia2(prefixes);

	EXPECT_TRUE(copia2.count("c") == 1);
	EXPECT_TRUE(copia2.count("casa") == 1);
	EXPECT_TRUE(copia2.count("casona") == 1);
	EXPECT_FALSE(copia2.count("ca") == 1);
	EXPECT_FALSE(copia2.count("cas") == 1);
	EXPECT_FALSE(copia2.count("caso") == 1);

	EXPECT_EQ(copia2.at("c"), 1);
	EXPECT_EQ(copia2.at("casa"), 2);
	EXPECT_EQ(copia2.at("casona"), 3);
}

TEST(string_map_test, no_aliasing) {
    string_map<int> singleton;
    singleton.insert(make_pair("hola", 1));

	string_map<int> copia(singleton);
	copia.insert(make_pair("hare", 2));
	ASSERT_FALSE(singleton.count("hare") == 1);
}


TEST(string_map_test, TrieOfTries) {
    string_map<int> vacio;
    string_map<int> singleton;
    string_map<int> no_prefixes;
    string_map<int> prefixes;
    string_map<string_map<int>> dicc_dicc;

    singleton.insert(make_pair("hola", 1));

    no_prefixes.insert(make_pair("hola", 1));
    no_prefixes.insert(make_pair("chau", 2));
    no_prefixes.insert(make_pair("adios",  3));

    prefixes.insert(make_pair("c",  1));
    prefixes.insert(make_pair("casa",  2));
    prefixes.insert(make_pair("casona",  3));

    dicc_dicc.insert(make_pair("vacio",  vacio));
    dicc_dicc.insert(make_pair("singleton",  singleton));
    dicc_dicc.insert(make_pair("no_prefixes",  no_prefixes));
    dicc_dicc.insert(make_pair("prefixes",  prefixes));

	EXPECT_FALSE(dicc_dicc.at("vacio").count("hola") == 1);

	EXPECT_EQ(dicc_dicc.at("singleton").at("hola"), 1);

	EXPECT_EQ(dicc_dicc.at("no_prefixes").at("hola"), 1);
	EXPECT_EQ(dicc_dicc.at("no_prefixes").at("chau"), 2);
	EXPECT_EQ(dicc_dicc.at("no_prefixes").at("adios"), 3);

	EXPECT_EQ(dicc_dicc.at("prefixes").at("c"), 1);
	EXPECT_EQ(dicc_dicc.at("prefixes").at("casa"), 2);
	EXPECT_EQ(dicc_dicc.at("prefixes").at("casona"), 3);

}

TEST(string_map_test, eraseOnlyKey) {
    string_map<int> singleton;
    singleton.insert(make_pair("hola", 1));

    EXPECT_TRUE(singleton.count("hola") == 1);

    singleton.erase("hola");

    EXPECT_FALSE(singleton.count("hola") == 1);
}


TEST(string_map_test, erase) {
    string_map<int> no_prefixes;
    string_map<int> prefixes;

    no_prefixes.insert(make_pair("hola", 1));
    no_prefixes.insert(make_pair("chau", 2));
    no_prefixes.insert(make_pair("adios",  3));

    prefixes.insert(make_pair("c",  1));
    prefixes.insert(make_pair("casa",  2));
    prefixes.insert(make_pair("casona",  3));

    prefixes.erase("c");
    EXPECT_FALSE(prefixes.count("c") == 1);

    EXPECT_TRUE(prefixes.count("casa") == 1);
    EXPECT_TRUE(prefixes.count("casona") == 1);

    prefixes.erase("casona");
    EXPECT_FALSE(prefixes.count("casona") == 1);

    EXPECT_TRUE(prefixes.count("casa") == 1);

    prefixes.erase("casa");
    EXPECT_FALSE(prefixes.count("casa") == 1);

    no_prefixes.erase("hola");
    EXPECT_FALSE(no_prefixes.count("hola") == 1);

    no_prefixes.erase("chau");
    EXPECT_FALSE(no_prefixes.count("chau") == 1);

    no_prefixes.erase("adios");
    EXPECT_FALSE(no_prefixes.count("adios") == 1);
}

#ifdef EXT

TEST(string_map_test, operator_corchetes) {
    string_map<int> no_prefixes;
    string_map<int> prefixes;

    no_prefixes["hola"] = 1;
    no_prefixes["chau"] = 2;
    no_prefixes["adios"] =  3;

    prefixes["c"] =  1;
    prefixes["casa"] =  2;
    prefixes["casona"] =  3;

    EXPECT_EQ(no_prefixes["hola"], 1);
    EXPECT_EQ(no_prefixes["chau"], 2);
    EXPECT_EQ(no_prefixes["adios"], 3);

    EXPECT_EQ(prefixes["c"], 1);
    EXPECT_EQ(prefixes["casa"], 2);
    EXPECT_EQ(prefixes["casona"], 3);
}

#endif

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
