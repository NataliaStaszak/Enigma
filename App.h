#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Plugboard.h"
#include "Rotor.h"

class App
{
    std::string cfgPath, inputPath, outputPath;
    std::vector<Rotor> rotors;
    Plugboard plugboard;
    std::string path;
    bool cfgLoaded;

    void displayMenu();//wyswietl menu
    void mainLoop();//glowna petla
    void generateConfig();//generuje konfiguracje
    void loadConfig();//odczyt konf
    void convert(bool encrypt); // encrypt = true dla szyfracji, dla deszyfracji = false
    std::string readText(std::string path);//odczyt
    void saveText(std::string path, std::string text);//zapis


public:
    static std::vector<char> alphabet;//wektor liter alfabetu

    static void clear();
    static std::vector<std::string> splitString(const std::string& line, char separator);
    static int promptInt(std::string promptText);
    static std::string promptStr(std::string promptTexts);

    App();
};