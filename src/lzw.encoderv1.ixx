module;
import std;

export module lzw.encoderv1;

import lzw.encoder;
import exo9;

export namespace lzw {

    // Version 1 : le dictionnaire de l'encodeur est notre Map (exo 9)
    class EncoderV1 : public Encoder {
    public:
        void Encode(std::ifstream& in, std::ofstream& out) override {
            // Dictionnaire : chaîne -> code, avec une entrée par octet possible
            auto dictionary = exo9::Map<std::string, CodeType>{};
            for (auto i = 0; i < byteCount; ++i) {
                dictionary.Put(std::string(1, static_cast<char>(i)), static_cast<CodeType>(i));
            }
            // GetSize() parcourt tout l'arbre : on compte les codes nous-mêmes
            auto nextCode = static_cast<std::size_t>(byteCount);

            auto s = std::string{};
            auto c = char{};
            while (in.get(c)) {
                const auto sc = s + c;
                if (dictionary.Contains(sc)) {
                    s = sc;
                } else {
                    // Nouvelle séquence : on lui donne le prochain code (tant qu'il en reste)
                    if (nextCode < maxCodes) {
                        dictionary.Put(sc, static_cast<CodeType>(nextCode));
                        ++nextCode;
                    }
                    WriteCode(out, dictionary.Get(s));
                    s = std::string(1, c);
                }
            }
            if (!s.empty()) {
                WriteCode(out, dictionary.Get(s));
            }
        }

        void Decode(std::ifstream& in, std::ofstream& out) override {
            // Dictionnaire : code -> chaîne (l'indice du tableau est le code)
            auto dictionary = std::vector<std::string>{};
            for (auto i = 0; i < byteCount; ++i) {
                dictionary.emplace_back(1, static_cast<char>(i));
            }

            auto s = std::string{};
            auto k = CodeType{};
            while (ReadCode(in, k)) {
                if (k > dictionary.size()) {
                    throw std::runtime_error{"Impossible de décoder : code invalide"};
                }
                if (k == dictionary.size()) {
                    // Cas spécial : le code désigne l'entrée en cours de création
                    dictionary.push_back(s + s[0]);
                } else if (!s.empty() && dictionary.size() < maxCodes) {
                    dictionary.push_back(s + dictionary[k][0]);
                }
                const auto& decoded = dictionary[k];
                out.write(decoded.data(), static_cast<std::streamsize>(decoded.size()));
                s = decoded;
            }
        }

    private:
        // Un code est écrit sur 2 octets
        using CodeType = std::uint16_t;
        static constexpr auto byteCount = 256;
        static constexpr auto maxCodes = std::size_t{65536};

        static void WriteCode(std::ofstream& out, const CodeType code) {
            out.put(static_cast<char>(code & 0xFF));
            out.put(static_cast<char>(code >> 8));
        }

        // Retourne false à la fin du fichier
        static bool ReadCode(std::ifstream& in, CodeType& code) {
            const auto low = in.get();
            const auto high = in.get();
            if (high == std::char_traits<char>::eof()) {
                return false;
            }
            code = static_cast<CodeType>(low | (high << 8));
            return true;
        }
    };
}
