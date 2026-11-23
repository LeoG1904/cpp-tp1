module;
import std;

export module exo7;

export namespace exo7 {

    class Resource {
    public:
        Resource() {
            std::println("Resource() constructor called");
        }

        ~Resource() {
            std::println("~Resource() destructor called");
        }

        static void DoSomething() {
            std::println("Doing something");
        }
    };

    class Application {
    public:
        // Alloue une Resource avec make_unique : elle est détruite automatiquement
        // à la fin de la fonction (RAII), sans delete.
        static void UniquePtr() {
            const auto res = std::make_unique<Resource>();
            exo7::Resource::DoSomething();
        }

        // res est passé par copie : la Resource n'est pas copiée, mais le shared_ptr
        // l'est, ce qui incrémente le compteur de références à chaque appel récursif.
        static void UseSharedPtr(const std::shared_ptr<Resource>& res) {
            std::println("resource use count: {}", res.use_count());
            Resource::DoSomething();
            if (res.use_count() < 5) {
                UseSharedPtr(res);
            }
        }

        // Alloue une Resource avec make_shared et affiche le compteur avant/après
        static void SharedPtr() {
            const auto res = std::make_shared<Resource>();
            std::println("resource use count: {}", res.use_count());
            UseSharedPtr(res);
            std::println("resource use count: {}", res.use_count());
        }

        Application() {
            UniquePtr();
            SharedPtr();
        }
    };
}
