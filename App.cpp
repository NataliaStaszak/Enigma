#include "App.h"

std::vector<char>App::alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

// Wyświetla dostepne opcje
void App::displayMenu() {
    std::cout << "Enigma machine" << (path == "" ? "" : " (Configuration Path: " + path + ")") << std::endl;
    std::cout << "**************" << std::endl;
    std::cout << "1. Create configuration" << std::endl;
    std::cout << "2. Load configuration" << std::endl;
    std::cout << "3. Encrypt Message" << std::endl;
    std::cout << "4. Decrypt Message" << std::endl;
    std::cout << "Type exit to quit the program" << std::endl;
}

//Funkcje pomocnicze proszą o odpowiednie dane
int App::promptInt(std::string promptText) {
    int userAnswer;
    std::cout << promptText << std::endl << "> ";
    std::cin >> userAnswer;
    return userAnswer;
}
std::string App::promptStr(std::string promptText) {
    std::string userAnswer;
    std::cout << promptText << std::endl << "> ";
    std::cin >> userAnswer;
    return userAnswer;
}
//czysci konsole
void App::clear() {
    system("cls");
}


//glowna petla
void App::mainLoop() {
    std::string userAnswer;
    while (true) {
        displayMenu();
        userAnswer = promptStr("Select corresponding option number");
        if (userAnswer == "1") {
            generateConfig();
            system("pause");
            clear();
            continue;
        }
        if (userAnswer == "2") {
            loadConfig();
            system("pause");
            clear();
            continue;
        }
        if (userAnswer == "3") {
            convert(true);
            system("pause");
            clear();
            continue;
        }
        if (userAnswer == "4") {
            convert(false);
            system("pause");
            clear();
            continue;
        }
        if (userAnswer == "exit" || userAnswer == "EXIT") {
            clear();
            return;
        }
        while (userAnswer != "1" && userAnswer != "2" && userAnswer != "3" && userAnswer != "4" && userAnswer != "exit" && userAnswer != "EXIT") {
            userAnswer = promptStr("Please select correct option");
            if (userAnswer == "1") {
                generateConfig();
                system("pause");
                clear();
                continue;
            }
            if (userAnswer == "2") {
                loadConfig();
                system("pause");
                clear();
                continue;
            }
            if (userAnswer == "3") {
                convert(true);
                system("pause");
                clear();
                continue;
            }
            if (userAnswer == "4") {
                convert(false);
                system("pause");
                clear();
                continue;
            }
            if (userAnswer == "exit" || userAnswer == "EXIT") {
                clear();
                return;
            }
        }
        clear();
    }
    
    
}

//generuje konfiguracje maszyny
void App::generateConfig()
{
    clear();
    std::cout << "Generating rotors..." << std::endl; // DOROBIC NASTAWIENIE NA POZYCJE
    for (int i = 0; i < 4; i++) {
        Rotor newRotor;
        rotors.push_back(newRotor);
        if (i == 3) std::cout << "Reflector successfully generated" << std::endl;
        else std::cout << "Rotor " << i + 1 << " successfully generated" << std::endl;
    }
    system("pause");
    //daje uzytkownikowi mozliwosc wygenerowania ustawienia wtyczek lub wprowadzenia ich samodzielnie
    clear();
    Plugboard newPlugboard;
    std::string choice = promptStr("Do you want to specify the plugboard connections by yourself or you want it to be automatically generated? (y/n)");
    if (choice == "y" || choice == "Y") newPlugboard.generateUserSpecified();
    else newPlugboard.generateRandom();
    std::cout << "Plugboard Generated" << std::endl;
    system("pause");

    clear();
    //prosi uzytkownika o wybor nazwy pliku do ktorego zapisze dane
    std::string filePath = promptStr("Enter the name of the file which will contain the config: ");
    std::fstream outputFile;
    outputFile.open(filePath, std::ios::out);
    for (Rotor rotor : rotors) {
        outputFile << rotor;
    }
    outputFile << newPlugboard;
    outputFile.close(); 
    std::cout << "Configuration successfully saved" << std::endl;
    path = filePath;

    cfgLoaded = true;
}
//funkcja wczytujaca wygenerowana wczesniej konfiguracje
void App::loadConfig()
{
    clear();
    path = promptStr("Enter name of the file containig machine configuration");
    std::ifstream inputFile(path);
    if (!inputFile.good()) {
        std::cout << "File containing config not found. Exiting" << std::endl;
        return;
    }
    std::cout << "File containing config found" << std::endl;

    std::string line;
    int lineNum = 0;

    int position;
    std::string rotorStr;
    while (getline(inputFile, line)) {
        if (lineNum == 0 || lineNum == 2 || lineNum == 4 || lineNum == 6) rotorStr = line;
        if (lineNum == 1 || lineNum == 3 || lineNum == 5 || lineNum == 7) {
            position = std::stoi(line);//string do int
            Rotor newRotor(rotorStr, position);
            this->rotors.push_back(newRotor);
        }
        if (lineNum == 8) {
            Plugboard newPlugboard(line);
            this->plugboard = newPlugboard;
        }
        lineNum++;
    }
    inputFile.close();
    std::cout << "Configuration file successfuly read!" << std::endl;
    cfgLoaded = true;
}
// funkcja zczytuje tekst 
std::string App::readText(std::string path)
{
    std::ifstream inputFile(path);
    if (!inputFile.good()) {
        std::cout << "File not found. Exiting" << std::endl;
        return "";
    }
    std::cout << "File found" << std::endl;

    std::string text = "";
    std::string line;
    int lineNum = 0;
    while (getline(inputFile, line)) {
        text += line;
        text += '\n';
    }
    inputFile.close();
    return text;
}
//zapis do pliku
void App::saveText(std::string path, std::string text)
{
    std::fstream outputFile;
    outputFile.open(path, std::ios::out);
    outputFile << text;
    outputFile.close();
}
//funkcja szyfrujaca
void App::convert(bool encrypt)
{
    clear();
    if (!cfgLoaded) {
        std::cout << "Configuration not loaded. Please load or create configuration before you continue" << std::endl;
        return;
    }
    std::string msg = (encrypt ? "Enter path contaning path to the file which you want to encrypt" : "Enter path contaning path to the file which you want to decrypt");
    std::string path = promptStr(msg);
    std::string text = readText(path);
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);//zamiana na duże litery

    int position;
    std::string rotorStr;   
    std::string encryptedMessage = "";
    char currLetter;

    for (const char& textLetter : text) {
        if (std::find(alphabet.begin(), alphabet.end(), textLetter) == alphabet.end()) {
            encryptedMessage += textLetter;
            continue;
        }
        // 1. Wtyczki 1
        currLetter = plugboard.transform(textLetter);
        std::cout << currLetter << std::endl;
        // 2. Rotory w lewo
        for (int i = 0; i < 3; i++) {
            currLetter = rotors[i].getOutputChar(currLetter);
            std::cout << currLetter << std::endl;
        }
        // 3. Reflektor
        currLetter = rotors[3].getOutputChar(currLetter);
        std::cout << currLetter << std::endl;
        // 4. Rotory w prawo
        for (int i = 3; i > 0; i--) {
            currLetter = rotors[i].getOutputChar(currLetter);
            std::cout << currLetter << std::endl;
        }
        // 5. Wtyczki 2
        currLetter = plugboard.transform(currLetter);
        std::cout << currLetter << std::endl;

        // Dopisz na wyjscie
        encryptedMessage += currLetter;
    }
    msg = (encrypt ? "Enter the name of the file which will contain the encrypted message" : "Enter the name of the file which will contain the decrypted message");
    path = promptStr(msg);
    saveText(path, encryptedMessage);
    std::cout << "Text successfully saved" << std::endl;

}
//funkcja rozdzielajaca string
std::vector<std::string> App::splitString(const std::string& line, char separator)
{
    std::vector<std::string> words;
    int i = 0;
    int startIndex = 0;
    int endIndex;
    int lineLength = line.length();

    while (i <= lineLength) {
        if (line[i] == separator || i == lineLength) {
            endIndex = i;
            std::string word;
            word.append(line, startIndex, endIndex - startIndex);
            words.push_back(word);
            startIndex = endIndex + 1;
        }
        i++;
    }
    return words;
}

App::App() {
    cfgLoaded = false;
    mainLoop();
}
