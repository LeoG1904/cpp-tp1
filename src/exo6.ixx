module;
import std;

export module exo6;

export namespace exo6 {

    // Fonctions "static" : appelées directement avec VectorUtils::Fonction(...)
    class VectorUtils {
    public:

        // span = fenêtre sans copie sur une séquence contiguë (vector, array...),
        // string_view = pareil pour du texte. Le label est facultatif.
        static void Print(const std::span<const int> values, const std::string_view label = {}) {
            if (!label.empty()) {
                std::print("{}: ", label);
            }
            std::ranges::for_each(values, [](const int value) {
                std::print("{} ", value);
            });
            std::println("");
        }

        static void SortAndRemoveDuplicates(std::vector<int>& vec) {
            std::ranges::sort(vec);
            // unique pousse les doublons en fin de vector, erase les supprime vraiment
            const auto duplicates = std::ranges::unique(vec);
            vec.erase(duplicates.begin(), duplicates.end());
        }

        static int CountGreaterThan(const std::span<const int> values, const int threshold) {
            // [threshold] : la lambda capture la valeur ; static_cast car count_if
            // retourne un type plus grand que int (warning = erreur dans ce projet)
            return static_cast<int>(std::ranges::count_if(values, [threshold](const int value) {
                return value > threshold;
            }));
        }

        // Retourne une view paresseuse : le filtre n'est appliqué qu'au parcours,
        // sans copie. Les données d'origine doivent rester valides.
        static auto GreaterThan(const std::span<const int> values, const int threshold) {
            return values | std::views::filter([threshold](const int value) {
                return value > threshold;
            });
        }
    };

    // Démonstration des fonctions
    class Application {
    public:
        Application() {
            auto vec = std::vector<int>{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};
            VectorUtils::Print(vec, "Avant");

            VectorUtils::SortAndRemoveDuplicates(vec);
            VectorUtils::Print(vec, "Trié sans doublons");

            std::println("Nombre de valeurs > 5 : {}", VectorUtils::CountGreaterThan(vec, 5));

            std::print("Valeurs > 5 : ");
            for (const auto value : VectorUtils::GreaterThan(vec, 5)) {
                std::print("{} ", value);
            }
            std::println("");

            // Un std::array est converti automatiquement en span
            const auto array = std::array{1, 6, 2, 7};
            VectorUtils::Print(array, "Array");
            std::println("Nombre de valeurs > 5 dans l'array : {}",
                         VectorUtils::CountGreaterThan(array, 5));
        }
    };
}
