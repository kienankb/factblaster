#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

typedef std::vector<std::pair<std::string,std::string> > PeopleType;
typedef std::vector<std::string> FactType;

void		ParseConfig	(std::ifstream &inconfig);
PeopleType	GetPeople	(std::ifstream &inpeople);
FactType	GetFacts	(std::ifstream &infacts);

int main(int argc, char *argv[])
{
	std::ifstream inconfig("factblaster.config");

	if (inconfig==NULL)
	{
		std::cout<<"ERROR: Missing config file!\n";
		exit(1);
	}
	else
	{
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
		if (inconfig.eof()) {break;}
	}
	return;
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