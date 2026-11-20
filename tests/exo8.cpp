#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Importation de l'exercice
import std;
import exo8;
using namespace exo8;
//
// TEST_CASE("Exo8", "BinaryTree") {
//     auto tree = BinaryTree{};
//
//     auto vecTest = [&](const std::vector<int>& result) {
//         std::vector<int> vec;
//         tree.Traversal([&](const int i) {
//             vec.push_back(i);
//         });
//         REQUIRE(vec == result);
//     };
//
//     vecTest({});
//     tree.Insert(10);
//     vecTest({10});
//     tree.Insert(5);
//     vecTest({5, 10});
//     tree.Insert(15);
//     vecTest({5, 10, 15});
//     tree.Insert(3);
//     vecTest({3, 5, 10, 15});
//     tree.Insert(7);
//     vecTest({3, 5, 7, 10, 15});
// }
