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

    /*
    SetConsoleTextAttribute(col, 6);
    std::cout << "REMOVE";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Remove data from memory" << std::endl;
    */
    SetConsoleTextAttribute(col, 6);
    std::cout << "LIST";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - List all interprets, their albums and songs in them" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "ADDPLAYLIST";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Add a song to a playlist" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "PLAYLIST";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Display all songs in the current playlist" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "NEWPLAYLIST";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Clear current and make new playlist" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "SAVE";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Save data into a file" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "LOAD";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Load data from a file" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "SAVEINTERPRETS";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Save interpret data into a file" << std::endl;

    SetConsoleTextAttribute(col, 6);
    std::cout << "LOADINTERPRETS";
    SetConsoleTextAttribute(col, 8);
    std::cout << " - Load interpret data from a file" << std::endl;

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
std::list<Song> playlist;

void AddInterpret() {
    interprets.push_back(getInterpret());
}

void ListSongs(std::list<Song> songs) {
    for (auto song : songs)
    {
        std::cout << "   - " << song.songName << std::endl;
    }
}

void ListAlbums(std::list<Album> albums) {
    for (auto album : albums)
    {
        std::cout << " - " << album.albumName << std::endl;
        ListSongs(album.songs);
    }
}

void ListInterprets(std::list<Interpret> interprets) {
    for (auto interpret : interprets)
    {
        std::cout << interpret.interpretName << std::endl;
        ListAlbums(interpret.albums);
    }
}

void SaveToFile() {
    int index = 0;
    char specialSymbol = 92;
    std::string filename;

    std::cout << "Select name for the file" << std::endl;
    filename = checkInputs();
    filename = filename + ".m3u";

    std::ofstream fileToBeSaved(filename, std::ios::out);
    fileToBeSaved << "#EXTM3U" << std::endl;
    for (auto song : playlist)
    {
        index++;
        std::cout << index << specialSymbol << song.songName << ".mp3" << std::endl;
        fileToBeSaved << index << specialSymbol << song.songName << ".mp3" << std::endl;
    }
    fileToBeSaved.close();
}

void LoadFromFile() {
    std::string filename;
    std::cout << "What's the name of the file you are trying to load?" << std::endl;
    filename = checkInputs();
    filename += ".m3u";

    char specialChar = 92;
    int index;

    std::string currentLine, modifiedString;

    std::ifstream fileToRead;
    fileToRead.open(filename);
    while (getline (fileToRead, currentLine)) {

        if(currentLine != "#EXTM3U") {
            for (index = 0; index < currentLine.length(); index++) {
                if (currentLine[index] == specialChar){
                    break;
                }
            }
            if (index < currentLine.length() - 1) {
                modifiedString = currentLine.substr(index + 1, currentLine.length() - (index + 1));
                std::cout << modifiedString.substr(0, modifiedString.find(".", 0)) << std::endl;
                Song tempSong;
                tempSong.songName = modifiedString.substr(0, modifiedString.find(".", 0));
                playlist.push_back(tempSong);
            }
        }
    }
}

void AddToPlaylist() {
    playlist.push_back(getSong());
}

void DisplayPlaylist() {
    for (auto song : playlist)
    {
        std::cout << song.songName  << std::endl;
    }
}

void SaveInterpretsToFile() {
    int index = 0;
    char specialSymbol = 92;
    std::string filename;

    std::cout << "Select name for the file" << std::endl;
    filename = checkInputs();
    filename = filename + ".txt";

    std::ofstream fileToBeSaved(filename, std::ios::out | std::ios::binary);
    std::string name="John Doell";
    int n = name.length();


    for (int i = 0; i <= n; i++)
    {
        // convert each char to
        // ASCII value
        int val = int(name[i]);

        // Convert ASCII value to binary
        std::string bin = "";
        while (val > 0)
        {
            (val % 2)? bin.push_back('1') :
            bin.push_back('0');
            val /= 2;
        }
        reverse(bin.begin(), bin.end());

        fileToBeSaved << bin << " ";
    }
    fileToBeSaved.close();
}

int main() {
    col =  GetStdHandle(STD_OUTPUT_HANDLE);
    bool working = true;

    std::cout << "Welcome to the Musik Library" << std::endl;

    while(working) {
        printOptions();
        std::string menuInput = "";
        menuInput = checkInputs();

        separate();

        if(menuInput == "ADD" || menuInput == "add") {
            AddInterpret();
        }

        if(menuInput == "LIST" || menuInput == "list") {
            if(interprets.size() > 0) {
                ListInterprets(interprets);
            } else {
                SetConsoleTextAttribute(col, 12);
                std::cout << "List is empty, add interprets first!" << std::endl;
                SetConsoleTextAttribute(col, 7);
            }

        }

        if(menuInput == "ADDPLAYLIST" || menuInput == "addplaylist") {
            AddToPlaylist();
        }

        if(menuInput == "PLAYLIST" || menuInput == "playlist") {
            DisplayPlaylist();
        }

        if(menuInput == "NEWPLAYLIST" || menuInput == "newplaylist") {
            playlist.clear();
        }

        if(menuInput == "SAVE" || menuInput == "save") {
            SaveToFile();
        }

        if(menuInput == "LOAD" || menuInput == "load") {
            LoadFromFile();
        }

        if(menuInput == "SAVEINTERPRETS" || menuInput == "saveinterprets") {
            SaveInterpretsToFile();
        }

        if(menuInput == "LOADINTERPRETS" || menuInput == "loadinterprets") {

        }

        if(menuInput == "END" || menuInput == "end") {
            working = false;
        }
    }

    return 0;
}
