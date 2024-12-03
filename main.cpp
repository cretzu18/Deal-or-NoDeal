#include "headers/Game.h"

int main() {
    try {
        Game game;
        game.play();
    } catch (const FontError& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    } catch (const MusicError& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    } catch (const BackgroundError& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    } catch (const TextureError& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return 0;
}