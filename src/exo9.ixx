module;
import std;

export module exo9;

export namespace exo9 {

    // ---------- Partie 1 : arbre binaire générique ----------

    // T est le type de donnée, choisi à l'utilisation : Node<int>, Node<std::string>...
    // Un noeud possède ses deux enfants via unique_ptr : pas de delete à écrire,
    // toute la sous-arborescence est détruite avec le noeud.
    template <typename T>
    struct Node {
        T value;
        std::unique_ptr<Node<T>> left{};
        std::unique_ptr<Node<T>> right{};

        explicit Node(const T& value)
            : value{value} {}
    };

    // T doit supporter l'opérateur < pour pouvoir être comparé
    template <typename T>
    class BinaryTree {
    public:
        // Ajoute une valeur (crée la racine si l'arbre est vide)
        void Insert(const T& value) {
            RecursiveInsert(root, value);
        }

        // Parcours dans l'ordre croissant : la lambda est appelée sur chaque valeur
        void Traversal(const std::function<void(const T&)>& action) const {
            RecursiveTraversal(root, action);
        }

        // Pour la Map : cherche une valeur équivalente (ni < ni >), nullptr si absente.
        // Deux versions : une qui permet de modifier la valeur, une en lecture seule.
        T* Find(const T& value) {
            return FindNode(root.get(), value);
        }

        const T* Find(const T& value) const {
            return FindNode(root.get(), value);
        }

    private:
        std::unique_ptr<Node<T>> root{nullptr};

        // On reçoit le unique_ptr par référence pour pouvoir y placer le nouveau noeud
        static void RecursiveInsert(std::unique_ptr<Node<T>>& node, const T& value) {
            if (!node) {
                node = std::make_unique<Node<T>>(value);
            } else if (value < node->value) {
                RecursiveInsert(node->left, value);
            } else {
                RecursiveInsert(node->right, value);
            }
        }

        // Gauche, noeud, droite : donne les valeurs triées
        static void RecursiveTraversal(const std::unique_ptr<Node<T>>& node,
                                       const std::function<void(const T&)>& action) {
            if (!node) {
                return;
            }
            RecursiveTraversal(node->left, action);
            action(node->value);
            RecursiveTraversal(node->right, action);
        }

        // "auto*" accepte Node<T>* et const Node<T>* : une seule fonction pour les deux Find
        static auto FindNode(auto* node, const T& value) -> decltype(&node->value) {
            while (node) {
                if (value < node->value) {
                    node = node->left.get();
                } else if (node->value < value) {
                    node = node->right.get();
                } else {
                    return &node->value;
                }
            }
            return nullptr;
        }
    };

    // ---------- Partie 2 : dictionnaire ----------

    // Une paire clé/valeur. Les comparaisons ne regardent que la clé,
    // ce qui permet de ranger les entrées dans l'arbre par clé.
    template <typename K, typename V>
    struct MapEntry {
        K key;
        V value;

        bool operator<(const MapEntry& other) const { return key < other.key; }
        bool operator<=(const MapEntry& other) const { return key <= other.key; }
        bool operator>(const MapEntry& other) const { return key > other.key; }
        bool operator>=(const MapEntry& other) const { return key >= other.key; }
        bool operator==(const MapEntry& other) const { return key == other.key; }
        bool operator!=(const MapEntry& other) const { return key != other.key; }
    };

    // K = type des clés, V = type des valeurs (V doit avoir un constructeur par défaut)
    template <typename K, typename V>
    class Map {
    public:
        void Clear() {
            // On remplace l'arbre par un arbre vide : l'ancien est détruit
            tree = BinaryTree<MapEntry<K, V>>{};
        }

        std::size_t GetSize() const {
            auto size = std::size_t{};
            tree.Traversal([&size](const MapEntry<K, V>&) {
                ++size;
            });
            return size;
        }

        bool Contains(const K& key) const {
            return tree.Find(MapEntry<K, V>{key, V{}}) != nullptr;
        }

        // Lève une exception (bad_optional_access) si la clé n'existe pas
        V& Get(const K& key) {
            return Find(key).value().get();
        }

        // Crée l'entrée ou modifie sa valeur
        void Put(const K& key, const V& value) {
            if (auto* entry = tree.Find(MapEntry<K, V>{key, V{}})) {
                entry->value = value;
            } else {
                tree.Insert(MapEntry<K, V>{key, value});
            }
        }

        // reference_wrapper : une référence qu'on peut ranger dans un optional
        std::optional<std::reference_wrapper<V>> Find(const K& key) {
            if (auto* entry = tree.Find(MapEntry<K, V>{key, V{}})) {
                return std::ref(entry->value);
            }
            return std::nullopt;
        }

        // Comme Find, mais l'absence est une erreur avec un message
        std::expected<std::reference_wrapper<V>, std::string> FindExpected(const K& key) {
            if (auto* entry = tree.Find(MapEntry<K, V>{key, V{}})) {
                return std::ref(entry->value);
            }
            return std::unexpected{std::string{"Key not found"}};
        }

    private:
        BinaryTree<MapEntry<K, V>> tree;
    };
}
