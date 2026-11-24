module;
import std;

export module lzw.encoderv2;

import lzw.encoder;

export namespace lzw {

    // Version 2 : même algorithme que la V1, mais avec std::map (arbre équilibré)
    class EncoderV2 : public Encoder {
    public:
        void Encode(std::ifstream& in, std::ofstream& out) override {
            auto dictionary = std::map<std::string, CodeType>{};
            for (auto i = 0; i < byteCount; ++i) {
                dictionary[std::string(1, static_cast<char>(i))] = static_cast<CodeType>(i);
            }

            auto s = std::string{};
            auto c = char{};
            while (in.get(c)) {
                const auto sc = s + c;
                if (dictionary.contains(sc)) {
                    s = sc;
                } else {
                    if (dictionary.size() < maxCodes) {
                        dictionary[sc] = static_cast<CodeType>(dictionary.size());
                    }
                    WriteCode(out, dictionary.at(s));
                    s = std::string(1, c);
                }
            }
            if (!s.empty()) {
                WriteCode(out, dictionary.at(s));
            }
        }

        void Decode(std::ifstream& in, std::ofstream& out) override {
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
        using CodeType = std::uint16_t;
        static constexpr auto byteCount = 256;
        static constexpr auto maxCodes = std::size_t{65536};

        static void WriteCode(std::ofstream& out, const CodeType code) {
            out.put(static_cast<char>(code & 0xFF));
            out.put(static_cast<char>(code >> 8));
        }

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
