#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdarg>
#include <memory>
#include <cstdio>
#include "font.h"
#include "logo.h"

#ifndef BATTERY_THRESHOLD
#define BATTERY_THRESHOLD 21
#endif

int screwreturnslol;

std::string exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}


void makewarn() {

	
    sf::RenderWindow window(sf::VideoMode({341, 192}), "Please charge your device.");
    sf::Font font;
    screwreturnslol = font.openFromMemory(_xProtoNerdFont_Regular_ttf, _xProtoNerdFont_Regular_ttf_size);
    sf::Text text(font);
 // a font is required to make a text object

    sf::Texture texture;
screwreturnslol=texture.loadFromMemory(archlogo_png, archlogo_png_size);
    texture.setSmooth(true);
    sf::Sprite sprite(texture);

// set the string to display
text.setString("Please charge your Arch Linux system.\nI'm fot nucking around, you better \nchucking farge me right now.");

// set the character size
text.setCharacterSize(20/2); // in pixels, not points!

// set the color
text.setFillColor(sf::Color::Red);
sprite.setScale({0.34/2, 0.14/2});
sprite.setPosition({0, 50});
// set the text style

   while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(text);
	window.draw(sprite);
        window.display();
    }






}

int main()
{
	std::cout << BATTERY_THRESHOLD;
	std::cout << "hewo";
	std::string level;
	std::string last;
	bool hasbeen = false;
	while(true) {
		last=level;
		usleep(5000);
		level = exec("cat /sys/class/power_supply/BAT1/capacity");
		if(atoi(level.c_str()) < BATTERY_THRESHOLD && !hasbeen ) {
		hasbeen=true;
		makewarn();
		}
		if(atoi(level.c_str()) >= BATTERY_THRESHOLD) {
		hasbeen=false;
		}
	}

    return 0;
}

