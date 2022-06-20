#pragma once

#include <map>
#include <string>

class Rotor
{
	std::map<char, char> internalConnections1;//mapa polaczen miedzy wtyczkami
	std::map<char, char> internalConnections2;//odwrocona mapa polaczen miedzy wtyczkami
	int currentPosition; //0-25

public:
	Rotor();
	Rotor(const Rotor& object);
	Rotor(std::string connectionsStr, int position);
	char getOutputChar(char incomingChar);// funkcja szukajaca w mapie
	friend std::ostream& operator<<(std::ostream& stream, Rotor& object);//przeciazenie operatora

};

