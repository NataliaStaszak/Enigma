#include "Plugboard.h"
#include "App.h"

//generator wtyczek losowych bez powtorzen- bierze litere z wektora a nastepnie przyporzodkowuje do pary i usuwa by zapowiec sytuacji typu A-B i B-F
void Plugboard::generateRandom()
{
	int desiredNumber = App::promptInt("Enter the desired quantity of plugs: ");
	desiredNumber = (desiredNumber > 13 ? 13 : desiredNumber);//jesli wieksze od 13 zmien na 13
	std::vector<char> chars = App::alphabet;
	int firstIndex, secondIndex;
	char first, second;
	std::random_device rd;
	std::mt19937 gen(rd()); // ziarno
	int i = 0;
	while (i < desiredNumber && i <= 13) {
		std::uniform_int_distribution<> distr(0, chars.size() - 1);
		firstIndex = distr(gen);
		first = chars[firstIndex];
		chars.erase(chars.begin() + firstIndex);

		std::uniform_int_distribution<> distr2(0, chars.size() - 1);
		secondIndex = distr2(gen);
		second = chars[secondIndex];
		chars.erase(chars.begin() + secondIndex);

		std::pair<char, char> plug1 = std::make_pair(first, second);
		std::pair<char, char> plug2 = std::make_pair(second, first);
		plugMap1.insert(plug1);
		plugMap2.insert(plug2);

		i++;
	}
	
}

void Plugboard::generateUserSpecified() //funkcja pozwala uzytkownikowi wprowadzic wlasne dane
{
	int currentNumber = 0;
	while (true) {
		App::clear();
		char firstEnd, secondEnd, decision;
		std::cout << "Enter the starting letter: " << std::endl << "> ";
		std::cin >> firstEnd;
		std::cout << "Enter the ending letter: " << std::endl << "> ";
		std::cin >> secondEnd;

		std::pair<char, char> newPlug1 = std::make_pair(firstEnd, secondEnd);
		plugMap1.insert(newPlug1);
		std::pair<char, char> newPlug2 = std::make_pair(secondEnd, firstEnd);
		plugMap2.insert(newPlug2);

		currentNumber++;
		std::cout << "Do you want to add another plug? (y/n)" << std::endl << "> ";
		std::cin >> decision;
		if (decision != 'y' && decision != 'Y') break;
	}
	numberOfPlugs = plugMap1.size();
}

void Plugboard::printPlugs()
{
	std::cout << "Plugs: " << std::endl;
	int number = 1;
	for (auto& plug : plugMap1) {
		std::cout << number << ". " << plug.first << " -> " << plug.second << std::endl;
		number++;
	}
}
Plugboard::Plugboard(const Plugboard& object)
{
	this->numberOfPlugs = object.numberOfPlugs;
	this->plugMap1 = object.plugMap1;
	this->plugMap2 = object.plugMap2;
}

Plugboard::Plugboard(std::string initString) 
{
	std::vector<std::string> plugVector = App::splitString(initString, ';');
	int quantity = 0;
	for (std::string& plugStr : plugVector) 
	{
		if (plugStr.size() != 3) continue;
		char inputChar = plugStr[0];
		char outputChar = plugStr[plugStr.size() - 1];
		std::pair<char, char> newPlug1 = std::make_pair(inputChar, outputChar);
		std::pair<char, char> newPlug2 = std::make_pair(outputChar, inputChar);
		plugMap1.insert(newPlug1);
		plugMap2.insert(newPlug2);
		quantity++;
	}
	numberOfPlugs = quantity;
}

Plugboard::Plugboard()
{
	numberOfPlugs = 0;
}

//funkcja wyszukuje jakiemu charowi odpowiada dany char
char Plugboard::transform(char input)
{
	if (plugMap1.find(input) != plugMap1.end()) return plugMap1.find(input)->second;
	if (plugMap2.find(input) != plugMap2.end()) return plugMap2.find(input)->second;
	return input;
}
//przeciazenie operatora
std::ostream& operator<<(std::ostream& stream, Plugboard& object)
{
	for (std::pair<char, char> plugPair : object.plugMap1) {
		stream << plugPair.first << "-" << plugPair.second << ";";
	}
	return stream;
}
