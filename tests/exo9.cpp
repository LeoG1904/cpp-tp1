#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Importation de l'exercice
import std;
import exo9;
using namespace exo9;

TEST_CASE("Exo9", "BinaryTree") {
    auto tree = BinaryTree<std::string>{};

    auto vecTest = [&](const std::vector<std::string>& result) {
        std::vector<std::string> vec;
        tree.Traversal([&vec](const std::string i) {
            vec.push_back(i);
        });
        REQUIRE(vec == result);
    };

    vecTest({});
    tree.Insert("C++");
    vecTest({"C++"});
    tree.Insert("ASM");
    vecTest({"ASM", "C++"});
    tree.Insert("GO");
    vecTest({"ASM", "C++", "GO"});
    tree.Insert("Rust");
    vecTest({"ASM", "C++", "GO", "Rust"});
    tree.Insert("JavaScript");
    vecTest({"ASM", "C++", "GO", "JavaScript", "Rust"});
}

TEST_CASE("Exo9 Map", "Map") {
    auto map = Map<std::string, int>{};
    REQUIRE(map.GetSize() == 0);
    REQUIRE_FALSE(map.Contains("Jean"));

    map.Put("Jean", 18);
    map.Put("Georges", 20);
    map.Put("Paul", 25);
    REQUIRE(map.GetSize() == 3);
    REQUIRE(map.Contains("Jean"));
    REQUIRE(map.Contains("Georges"));
    REQUIRE_FALSE(map.Contains("Jeanne"));
    REQUIRE(map.Get("Jean") == 18);

    // Put sur une clé existante modifie la valeur sans ajouter d'entrée
    map.Put("Jean", 19);
    REQUIRE(map.GetSize() == 3);
    REQUIRE(map.Get("Jean") == 19);
    map.Get("Jean") = 18;
    REQUIRE(map.Get("Jean") == 18);

    // Find
    auto jean = map.Find("Jean");
    REQUIRE(jean.has_value());
    REQUIRE(jean->get() == 18);
    REQUIRE_FALSE(map.Find("Jeanne").has_value());

    // FindExpected
    auto georges = map.FindExpected("Georges");
    REQUIRE(georges.has_value());
    REQUIRE(georges->get() == 20);
    const auto missing = map.FindExpected("Jeanne");
    REQUIRE_FALSE(missing.has_value());
    REQUIRE(missing.error() == "Key not found");

    // Clear
    map.Clear();
    REQUIRE(map.GetSize() == 0);
    REQUIRE_FALSE(map.Contains("Jean"));
    REQUIRE_FALSE(map.Find("Jean").has_value());
}
