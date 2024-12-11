#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iostream>

class Animation {
public:
// Constructor to initialize frame timing and load images
Animation(int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isPlaying(false) {}

    // Load a sequence of frames (e.g., 001.png to 024.png) into textures
    void loadFrames(const std::string& baseFilename, int start, int end) {
        frames.clear();
        for (int i = start; i <= end; ++i) {
            sf::Texture texture;
            std::string filename = (i < 10) ? "00" + std::to_string(i) + ".png" : "0" + std::to_string(i) + ".png";
            if (!texture.loadFromFile(filename)) {
                std::cerr << "Error loading " << filename << std::endl;
                continue;
            }
            frames.push_back(texture);
        }
    }

    // Start the animation
    void play() {
        isPlaying = true;
        frameIndex = 0;
        clock.restart();
    }

    // Update the animation frame based on the elapsed time
    void update(sf::Sprite& sprite) {
        if (!isPlaying) return;

        if (clock.getElapsedTime().asMilliseconds() > frameDelay) {
            frameIndex++;
            if (frameIndex < frames.size()) {
                sprite.setTexture(frames[frameIndex]);
                clock.restart();
            } else {
                // End animation and display a random dice face (1 to 6)
                std::mt19937 rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
                std::uniform_int_distribution<int> dist(1, 6);
                int finalDiceFace = dist(rng);
                std::string finalFilename = std::to_string(finalDiceFace) + ".png";
                if (!texture.loadFromFile(finalFilename)) {
                    std::cerr << "Error loading " << finalFilename << std::endl;
                    return;
                }
                sprite.setTexture(texture);
                isPlaying = false;
            }
        }
    }

    bool isAnimationPlaying() const { return isPlaying; }

private:
    std::vector<sf::Texture> frames; // Vector to store frames for animation
    sf::Texture texture; // Texture for final dice face
    int frameIndex; // Current frame index
    int frameDelay; // Delay per frame in milliseconds
    bool isPlaying; // Is the animation playing?
    sf::Clock clock; // Clock for frame timing
};

int main() {
sf::RenderWindow window(sf::VideoMode(200, 200), "Dice Roll Animation");

    // Initialize animation with 24 frames at a 50ms delay
    Animation diceAnimation(50);
    diceAnimation.loadFrames("", 1, 24);

    // Sprite to display the animation
    sf::Sprite sprite;
    sprite.setPosition(50, 50);  // Adjust position as needed

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Start or restart animation on mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!diceAnimation.isAnimationPlaying()) {
                    diceAnimation.play();
                }
            }
        }

        // Update the animation
        diceAnimation.update(sprite);

        // Clear, draw, and display the window
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;

}
