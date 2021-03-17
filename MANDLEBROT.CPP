#include<iostream>
#include <SFML/Graphics.hpp>
#include<math.h>
int WIDTH = 800;
int HEIGHT = 800;
int MAX_ITERATIONS = 500;
long double min = -2.84;
long double max = 1.0;
long double factor = 1;
long double map(long double value, long double in_min,long double in_max,long double out_min,long double out_max) {

    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "MANDLEBROT");
    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }




     
       // image.setPixel(i, j, sf::Color(rand() % 255, rand() % 255, rand() % 255));
        int count = 0;
        while (1) {
            max -= 0.1 * factor;
            min += 0.15 * factor;
            factor *= 0.9349;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    long double a = map(i, 0, WIDTH, min, max);
                    long double b = map(j, 0, HEIGHT, min, max);
                    
                    long double ai = a;
                    long double bi = b;

                    int n = 0;
                    for (int Z = 0; Z < MAX_ITERATIONS;Z++) {
                        long double a1 = a * a - b * b;
                        long double b1 = 2 * a * b;
                        a = a1 + ai;
                        b = b1 + bi;
                        if (abs(a + b) > 2) {
                            break;
                        }
                        n++;
                    }
                    int bright = map(n,0,MAX_ITERATIONS,0,255);
                    if (n == MAX_ITERATIONS || bright < 10) {
                        bright = 0;
                    }
                    int red = map(bright*bright,0,6502,0,255);
                    int green = bright;
                    int blue = (bright*2)%255;
                    image.setPixel(i, j, sf::Color(red, green, blue));
                }
            }
            texture.loadFromImage(image);
            sf::Sprite sprite(texture);
            window.clear();
            window.draw(sprite);
            window.display();
            count++;
        }



    }

    return 0;
}