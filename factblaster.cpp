#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

typedef std::vector<std::pair<std::string,std::string> > PeopleType;
typedef std::vector<std::string> FactType;

void		ParseConfig	(std::ifstream &inconfig);
void		SayHello	();
PeopleType	GetPeople	(std::ifstream &inpeople);
FactType	GetFacts	(std::ifstream &infacts);
void		FireMessage	(std::string message, std::string address);

int main(int argc, char *argv[])
{
	std::ifstream inconfig("factblaster.config");
	SayHello();
	std::cout<<"Looking for config file..."
	if (inconfig==NULL)
	{
		std::cout<<"ERROR: Missing config file!\n";
		exit(1);
	}
	else
	{
		std::cout<<"done!\n";
		ParseConfig(inconfig);
	}
	return 0;
}

void ParseConfig(std::ifstream &inconfig)
{
	std::string tmp;
	while (true)
	{
		std::getline(inconfig,tmp);
		if (tmp.substr(0,8)=="factfile")
		{
			std::cout<<"Looking for facts file...";
			std::ifstream infacts(tmp.substr(9,std::string::npos));
			if (infacts==NULL)
			{
				std::cout<<"Error finding file!\n";
				exit(1);
			}
			else
			{
				GetFacts(infacts);
			}
		}
		else if (tmp.substr(0,)=="namesfile")
		{

		}
		else
		{

		}
		if (inconfig.eof()) {break;}
	}
	return;
}

void SayHello()
{
	std::cout<<"      ___      ___          ___                                         ___          ___                 ___          ___     \n";
	std::cout<<"     /  /\\    /  /\\        /  /\\        ___    _____                   /  /\\        /  /\\        ___    /  /\\        /  /\\    \n";
	std::cout<<"    /  /:/_  /  /::\\      /  /:/       /  /\\  /  /::\\                 /  /::\\      /  /:/_      /  /\\  /  /:/_      /  /::\\   \n";
	std::cout<<"   /  /:/ /\\/  /:/\\:\\    /  /:/       /  /:/ /  /:/\\:\\  ___     ___  /  /:/\\:\\    /  /:/ /\\    /  /:/ /  /:/ /\\    /  /:/\\:\\  \n";
	std::cout<<"  /  /:/ /:/  /:/~/::\\  /  /:/  ___  /  /:/ /  /:/~/::\\/__/\\   /  /\\/  /:/~/::\\  /  /:/ /::\\  /  /:/ /  /:/ /:/_  /  /:/~/:/  \n";
	std::cout<<" /__/:/ /:/__/:/ /:/\\:\\/__/:/  /  /\\/  /::\\/__/:/ /:/\\:\\  \\:\\ /  /:/__/:/ /:/\\:\\/__/:/ /:/\\:\\/  /::\\/__/:/ /:/ /\\/__/:/ /:/___\n";
	std::cout<<" \\  \\:\\/:/\\  \\:\\/:/__\\/\\  \\:\\ /  /:/__/:/\\:\\  \\:\\/:/~/:/\\  \\:\\  /:/\\  \\:\\/:/__\\/\\  \\:\\/:/~/:/__/:/\\:\\  \\:\\/:/ /:/\\  \\:\\/:::::/\n";
	std::cout<<"  \\  \\::/  \\  \\::/      \\  \\:\\  /:/\\__\\/  \\:\\  \\::/ /:/  \\  \\:\\/:/  \\  \\::/      \\  \\::/ /:/\\__\\/  \\:\\  \\::/ /:/  \\  \\::/~~~~ \n";
	std::cout<<"   \\  \\:\\   \\  \\:\\       \\  \\:\\/:/      \\  \\:\\  \\:\\/:/    \\  \\::/    \\  \\:\\       \\__\\/ /:/      \\  \\:\\  \\:\\/:/    \\  \\:\\     \n";
	std::cout<<"    \\  \\:\\   \\  \\:\\       \\  \\::/        \\__\\/\\  \\::/      \\__\\/      \\  \\:\\        /__/:/        \\__\\/\\  \\::/      \\  \\:\\    \n";
	std::cout<<"     \\__\\/    \\__\\/        \\__\\/               \\__\\/                   \\__\\/        \\__\\/               \\__\\/        \\__\\/    \n";
	std::cout<<"Developed mostly during HACK(RPI); Fall 2014 as a whimsical project.\n";
	std::cout<<"Code by Kienan Knight-Boehm (kienankb.com), ASCII art by an awesome website I can't remember right now.\n";
}

PeopleType GetPeople(std::ifstream &inpeople)
{
	PeopleType result;
	std::string tmp, tmpname, tmpaddress;
	while (true)
	{
		std::getline(inpeople,tmp);
		if (inpeople.eof()) break;
		tmpname = tmp;
		std::getline(inpeople,tmp);
		tmpaddress = tmp;
		result.push_back(std::make_pair(tmpname,tmpaddress));
	}
	return result;
}

FactType GetFacts(std::ifstream &infacts)
{
	FactType result;
	std::string tmp;
	while (true)
	{
		if (infacts.eof()) break;
		std::getline(infacts,tmp);
		result.push_back(tmp);
		tmp.clear();
	}
	return result;
}

void FireMessage(std::string message, std::string address)
{
	std::string fact = "Did you know? "+message+" Reply STOP to cancel.";
	std::string commandstring = "echo \"Did you know? "+message+" Reply STOP to cancel.\" | mail "+address;
	system(commandstring.c_str());
	system(("echo "+fact+" | festival --tts"));
}
