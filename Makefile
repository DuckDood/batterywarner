all: obj/logo.o obj/font.o obj/main.o build/batwarn

obj/logo.o:
	@echo -e "Compiling logo..."
	@g++ -c source/logo.cpp -o obj/logo.o
	@echo -e "Compililation done!"

obj/font.o:
	@echo -e "Compiling font..."
	@g++ -c source/font.cpp -o obj/font.o
	@echo -e "Compililation done!"

obj/main.o: source/main.cpp
	@echo -e "Compiling main..."
ifdef BATTERY_THRESHOLD
	@g++ -c source/main.cpp -o obj/main.o -DBATTERY_THRESHOLD=${BATTERY_THRESHOLD}
	@echo -e "Compililation done at ${BATTERY_THRESHOLD}%!"
else 
	@g++ -c source/main.cpp -o obj/main.o
	@echo -e "Compililation done!"
endif

build/batwarn:
	@echo -e "Linking..."
	@g++ obj/main.o obj/font.o obj/logo.o -o build/batwarn -lsfml-graphics -lsfml-window -lsfml-system
	@echo -e "Linking done!\n\nExecutable should be at build/batwarn."

clean:
	rm obj/main.o obj/logo.o obj/font.o build/batwarn
.PHONY: clean

cleanbin:
	rm obj/main.o build/batwarn
.PHONY: cleanbin

install:
	sudo install -m 755 build/batwarn /usr/local/bin
	@echo -e "exec-once = ~/Documents/batwarn\nwindowrulev2 = fullscreen, title:Please charge your device.\nwindowrulev2 = float, title:Please charge your device." >> ~/.config/hypr/hyprland.conf

.PHONY: install
