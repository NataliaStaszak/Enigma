#include "Rotor.h"
#include "App.h"
#include <random>
//konstruktor
Rotor::Rotor() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 25);
	currentPosition = distr(gen);//generowanie losowego ustawienia wirnika
	std::vector<char> chars = App::alphabet;
	int firstIndex, secondIndex;
	char first, second;
	int i = 0;
	while (i < 13) {
		std::uniform_int_distribution<> distr(0, chars.size() - 1);
		firstIndex = distr(gen);
		first = chars[firstIndex];
		chars.erase(chars.begin() + firstIndex);


		std::uniform_int_distribution<> distr2(0, chars.size() - 1);
		secondIndex = distr2(gen);
		second = chars[secondIndex];
		chars.erase(chars.begin() + secondIndex);


		std::pair<char, char> connection1 = std::make_pair(first, second);
		std::pair<char, char> connection2 = std::make_pair(second, first);
		internalConnections1.insert(connection1);
		internalConnections2.insert(connection2);

		i++;
	}
}
//konstruktor
Rotor::Rotor(const Rotor& object)
{
	this->currentPosition = object.currentPosition;
	this->internalConnections1 = object.internalConnections1;
	this->internalConnections2 = object.internalConnections2;
}
//konstruktor
Rotor::Rotor(std::string connectionsStr, int position) 
{
	this->currentPosition = position;
	std::vector<std::string> connectionVector = App::splitString(connectionsStr, ';');
	int quantity = 0;
	for (std::string& connectionStr : connectionVector)
	{
		if (connectionStr.size() != 3) continue;
		char inputChar = connectionStr[0];
		char outputChar = connectionStr[2];

		std::pair<char, char> newConnection1 = std::make_pair(inputChar, outputChar);
		std::pair<char, char> newConnection2 = std::make_pair(outputChar, inputChar);
		internalConnections1.insert(newConnection1);
		internalConnections2.insert(newConnection2);
		quantity++;
	}
}
// funkcja szukajaca w mapie
char Rotor::getOutputChar(char incomingChar)
{
	if (internalConnections1.find(incomingChar) == internalConnections1.end()) return internalConnections2.find(incomingChar)->second;
	return internalConnections1.find(incomingChar)->second;

}
//przeciazenie operatora
std::ostream& operator<<(std::ostream& stream, Rotor& object)
{
	for (auto& connectionPair : object.internalConnections1) {
		stream << connectionPair.first << "-" << connectionPair.second;
		stream << ";";
	}
	stream << std::endl;
	stream << object.currentPosition << std::endl;
	return stream;
}
