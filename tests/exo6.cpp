#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Importation de l'exercice
import std;
import exo6;
using namespace exo6;
//
// TEST_CASE("Exo6", "VectorUtils") {
//     auto vec = std::vector<int>{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};
//     VectorUtils::SortAndRemoveDuplicates(vec);
//     const auto result = std::vector<int>{1, 2, 4, 5, 7, 8, 9};
//     REQUIRE(vec == result);
//
//     REQUIRE(VectorUtils::CountGreaterThan(vec, 5) == 3);
//
//     auto filtered = std::vector<int>{};
//     for (const auto value : VectorUtils::GreaterThan(vec, 5)) {
//         filtered.push_back(value);
//     }
//     REQUIRE(filtered == std::vector<int>{7, 8, 9});
//
//     const auto array = std::array{1, 6, 2, 7};
//     REQUIRE(VectorUtils::CountGreaterThan(array, 5) == 2);
// }
