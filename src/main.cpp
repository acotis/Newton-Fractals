#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>
#include <functional>


typedef std::pair<sf::Color,bool> MaybeColor;
typedef std::complex<float> Complex;
typedef std::function<Complex*(Complex)> TransformFun;
typedef std::function<MaybeColor*(Complex, int)> ColorFun;

int INF = 20;


TransformFun TRANSFORM = [](Complex z) {
    Complex num = z*z*z - 1.0f;
    Complex den = 3.0f*z*z;
    return new Complex(z - num/den);
};

ColorFun COLORATION = [](std::complex<float> z, int iterations) {
    Complex a(1, 0);
    Complex b(-.5f, -.866f);
    Complex c(-.5f, .866f);

    sf::Color color;
    bool finished = true;

    float limit = .01;

    float greyF = 1 - (iterations + .0f) / INF;
    greyF = std::pow(greyF, 1.0f);
    sf::Uint8 grey = (sf::Uint8) (255*greyF);

    if(std::abs(z-a) < limit) color = sf::Color(grey, 0, 0);
    else if(std::abs(z-b) < limit) color = sf::Color(0, grey, 0);
    else if(std::abs(z-c) < limit) color = sf::Color(0, 0, grey);
    else {
        color = sf::Color(0, 0, 0);
        finished = false; // Keep going only if not near a root
    }

    return new MaybeColor(color, finished);
};


sf::Color getColorForStartLocation(float x, float y) {
    std::complex<float> z(x, y);
    MaybeColor result;

    int iterations = 0;

    while(true) {
        result = *COLORATION(z, iterations);

        if(result.second || iterations==INF) {
            return result.first;
        }

        z = *TRANSFORM(z);
        iterations++;
    }
}


void drawFractal(sf::Image &image, int width, int height, sf::FloatRect bounds) {
    // Draw the portion of the fractal inside bounds onto the image

    float xStep = bounds.width / width;
    float yStep = bounds.height / height;
    sf::Uint8 *pixels = new sf::Uint8[width * height * 4]; // Four bytes for each pixel (RGBA)

    // Make the whole image cyan

    for(int xPix=0; xPix<width; xPix++) {
        for(int yPix=0; yPix<height; yPix++) {
            float x = bounds.left + xPix * xStep;
            float y = bounds.top + yPix * yStep;

            sf::Color color = getColorForStartLocation(x, y);

            int offset = (yPix*width + xPix) * 4;
            pixels[offset] = color.r;
            pixels[offset + 1] = color.g;
            pixels[offset + 2] = color.b;
            pixels[offset + 3] = color.a;
        }
    }

    std::cout << "Loading image from memory..." << std::endl;
    image.create((uint) width, (uint) height, pixels);
    std::cout << "Loaded." << std::endl;

    //delete pixels;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Newton fractal");
    sf::Event nextEvent;

    sf::Image fractalImage;
    drawFractal(fractalImage, 800, 600, sf::FloatRect(-2.4f, -1.8f, 4.8, 3.6));

    sf::Texture fractalTexture;
    fractalTexture.loadFromImage(fractalImage);
    fractalTexture.setSmooth(true);
    sf::Sprite fractalSprite;
    fractalSprite.setTexture(fractalTexture, true);

    while(window.isOpen()) {
        while(window.pollEvent(nextEvent)) {
            if(nextEvent.type == sf::Event::Closed) {
                std::cout << "Exiting game loop...";
                window.close();
            }
        }

        window.draw(fractalSprite);
        window.display();
    }

    std::cout << "Outside of loop now." << std::endl;

    return 0;
}