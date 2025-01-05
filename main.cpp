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

	
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width/6, sf::VideoMode::getDesktopMode().height/6), "Please charge your device.");
    sf::Font font;
    font.loadFromFile("/home/duck/Documents/duckdependencies/0xProtoNerdFont-Regular.ttf");
    sf::Text text;
    text.setFont(font); // a font is required to make a text object
    sf::Texture texture;
    texture.loadFromFile("/home/duck/Documents/duckdependencies/archlogo.png");
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
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
	std::string level;
	std::string last;
	bool hasbeen = false;
	while(true) {
		last=level;
		usleep(5000);
		level = exec("cat /sys/class/power_supply/BAT1/capacity");
		if(atoi(level.c_str()) < 21 && !hasbeen ) {
		hasbeen=true;
		makewarn();
		}
		if(atoi(level.c_str()) >= 21) {
		hasbeen=false;
		}
	}

    return 0;
}

