module;
import std;

export module exo8;

export namespace exo8 {

    // Un noeud possède ses deux enfants via unique_ptr : pas de delete à écrire,
    // toute la sous-arborescence est détruite avec le noeud.
    struct Node {
        int value;
        std::unique_ptr<Node> left{};
        std::unique_ptr<Node> right{};

        explicit Node(const int value)
            : value{value} {}
    };

    class BinaryTree {
        public:
            // Ajoute une valeur (crée la racine si l'arbre est vide)
            void Insert(const int value) {
                RecursiveInsert(root, value);
            }

            // Parcours dans l'ordre croissant : la lambda est appelée sur chaque valeur
            void Traversal(const std::function<void(int)>& action) const {
                RecursiveTraversal(root, action);
            }

        private:
            std::unique_ptr<Node> root{nullptr};

            // On reçoit le unique_ptr par référence pour pouvoir y placer le nouveau noeud
            static void RecursiveInsert(std::unique_ptr<Node>& node, const int value) {
                if (!node) {
                    node = std::make_unique<Node>(value);
                } else if (value < node->value) {
                    RecursiveInsert(node->left, value);
                } else {
                    RecursiveInsert(node->right, value);
                }
            }

            // Gauche, noeud, droite : donne les valeurs triées
            static void RecursiveTraversal(const std::unique_ptr<Node>& node,
                                           const std::function<void(int)>& action) {
                if (!node) {
                    return;
                }
                RecursiveTraversal(node->left, action);
                action(node->value);
                RecursiveTraversal(node->right, action);
            }
    };
}
