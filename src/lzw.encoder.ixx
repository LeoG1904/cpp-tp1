module;
import std;

export module lzw.encoder;

export namespace lzw {

    // Interface commune à toutes les versions de l'encodeur
    class Encoder {
    public:
        virtual ~Encoder() = default;
        virtual void Encode(std::ifstream& in, std::ofstream& out) = 0;
        virtual void Decode(std::ifstream& in, std::ofstream& out) = 0;
    };
}
