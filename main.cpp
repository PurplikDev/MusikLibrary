#include <iostream>
#include <string>
#include <windows.h>
#include <bits/stdc++.h>

/*
1  : Blue
2  : Green
3  : Cyan
4  : Red
5  : Purple
6  : Yellow(dark)
7  : Default white
8  : Grey
9  : Bright blue
10 : Bright green
11 : Bright cyan
12 : Bright red
13 : pink
14 : yellow
15 : Bright white
*/

HANDLE col;

void separate(){
    for(int i = 0; i < 25; i++) {
        std::cout << "=";
    }
    std::cout << std::endl;
}

void printOptions() {

    separate();

    SetConsoleTextAttribute(col, 6);
    std::cout << "ADD";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Add an interpret" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "REMOVE";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Remove data from memory" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "SAVE";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Save data into a file" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "LOAD";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Load data from a file" << std::endl;

    SetConsoleTextAttribute(col, 12);
    std::cout << "END";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - End program" << std::endl;

    SetConsoleTextAttribute(col, 7);
    separate();

}

std::string checkInputs() {
    std::string input;
    std::cin >> input;
    return input;
}

int getNumberInput() {
    int input;
    std::cin >> input;
    return input;
}

struct Song {
public:
    std::string songName;
};


struct Album {
public:
    std::string albumName;
    std::list<Song> songs;
};

struct Interpret {
public:
    std::string interpretName;
    std::list<Album> albums;
};

Song getSong() {
    Song tempSong;
    std::cout << "What's the name of this song?" << std::endl;
    tempSong.songName = checkInputs();
    return tempSong;
}

Album getAlbum() {
    Album tempAlbum;
    std::cout << "What's the name of this album?" << std::endl;
    tempAlbum.albumName = checkInputs();

    std::cout << "How many songs does this album contain?" << std::endl;
    int songAmount = getNumberInput();

    for(int i = 0; i < songAmount; i++) {
        tempAlbum.songs.push_back(getSong());
    }
    return tempAlbum;
}

Interpret getInterpret() {
    Interpret tempInterpret;
    std::cout << "What's the name of this interpret?" << std::endl;
    tempInterpret.interpretName = checkInputs();

    std::cout << "How many albums does this interpret have?" << std::endl;
    int albumAmount = getNumberInput();
    for(int i = 0; i < albumAmount; i++) {
        tempInterpret.albums.push_back(getAlbum());
    }
    return tempInterpret;
}

std::list<Interpret> interprets;

void AddInterpret() {
    interprets.push_back(getInterpret());
}

int main() {
    col =  GetStdHandle(STD_OUTPUT_HANDLE);
    bool working = true;

    std::cout << "Welcome to the Musik Library" << std::endl;

    while(working) {
        printOptions();
        std::string menuInput = checkInputs();

        separate();

        if(menuInput == "ADD" || menuInput == "add") {
            AddInterpret();
        }

        if(menuInput == "END" || menuInput == "end") {
            working = false;
        }
    }

    return 0;
}
