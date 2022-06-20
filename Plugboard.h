#pragma once

#include <map>
#include <string>
#include <vector>
#include <random>
#include <iostream>

class Plugboard
{
	int numberOfPlugs;//liczba wtyczek
	std::map<char, char> plugMap1; // 1 kierunek A -> B
	std::map<char, char> plugMap2; // 2 kierunek B -> A

public:
	void generateRandom();//generator liczb losowych
	void generateUserSpecified();//generator ustawien wlasnych
	void printPlugs();// drukuj wtyczki
	Plugboard(const Plugboard& object);
	Plugboard(std::string initString);
	Plugboard();
	friend std::ostream& operator<<(std::ostream& stream, Plugboard& object);//przeciazony operator
	char transform(char input);// szukanie odpowiadajacym charom w parach

};

