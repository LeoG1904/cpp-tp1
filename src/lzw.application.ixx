module;
import std;

export module lzw.application;

import lzw.encoder;
import lzw.encoderv1;
import lzw.encoderv2;
import lzw.encoderv3;

export namespace lzw {

    class Application {
    public:
        Application(const std::string& source,
                    const std::string& compressed,
                    const std::string& uncompressed) {
            // On exécute les trois versions pour comparer les temps
            auto encoderV1 = EncoderV1{};
            Run(encoderV1, source, compressed, uncompressed);
            auto encoderV2 = EncoderV2{};
            Run(encoderV2, source, compressed, uncompressed);
            auto encoderV3 = EncoderV3{};
            Run(encoderV3, source, compressed, uncompressed);
        }

    private:
        // Compresse source -> compressed, décompresse compressed -> uncompressed,
        // puis affiche les statistiques et les temps
        static void Run(Encoder& encoder,
                        const std::string& source,
                        const std::string& compressed,
                        const std::string& uncompressed) {
            {
                auto in = std::ifstream{source, std::ios::binary};
                auto out = std::ofstream{compressed, std::ios::binary};
                CheckOpen(in.is_open() && out.is_open());

                const auto start = std::chrono::high_resolution_clock::now();
                encoder.Encode(in, out);
                out.close();
                const auto end = std::chrono::high_resolution_clock::now();
                const auto elapsed = std::chrono::duration<double, std::milli>(end - start).count();

                const auto sourceSize = static_cast<double>(std::filesystem::file_size(source));
                const auto compressedSize = static_cast<double>(std::filesystem::file_size(compressed));
                std::println("{} bytes uncompressed, {} bytes compressed, {:.6g}% in {:.6g}ms",
                             sourceSize, compressedSize, compressedSize / sourceSize * 100.0, elapsed);
            }
            {
                auto in = std::ifstream{compressed, std::ios::binary};
                auto out = std::ofstream{uncompressed, std::ios::binary};
                CheckOpen(in.is_open() && out.is_open());

                const auto start = std::chrono::high_resolution_clock::now();
                encoder.Decode(in, out);
                out.close();
                const auto end = std::chrono::high_resolution_clock::now();
                const auto elapsed = std::chrono::duration<double, std::milli>(end - start).count();
                std::println("uncompress in {:.6g}ms", elapsed);
            }
        }

        static void CheckOpen(const bool ok) {
            if (!ok) {
                throw std::runtime_error{"Impossible d'ouvrir un fichier"};
            }
        }
    };
}
