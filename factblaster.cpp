#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <stdlib.h>
#include <unistd.h>

typedef std::vector<std::pair<std::string,std::string> > PeopleType;
typedef std::vector<std::string> FactType;

void		ParseConfig	(std::ifstream &inconfig, PeopleType &people, FactType &facts);
void		SayHello	();
PeopleType	GetPeople	(std::ifstream &inpeople);
FactType	GetFacts	(std::ifstream &infacts);
void		FireMessage	(std::string message, std::string address);
int			GetOption	();
void		PlayFact	(std::string fact);
void		SingleShot	(FactType &facts, PeopleType &people, int random);
void		ListPeople	(PeopleType &people);
void		ListFacts	(FactType &facts);
void		Schedule	(PeopleType &people, FactType &facts);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	PeopleType people;
	FactType facts;
	std::ifstream inconfig("factblaster.config");
	SayHello();
	std::cout<<"Looking for config file...";
	if (inconfig==NULL)
	{
		std::cout<<"ERROR: Missing config file!\n";
		exit(1);
	}
	else
	{
		std::cout<<"done!\n";
		ParseConfig(inconfig, people, facts);
	}
	inconfig.close();
	int choice, random;
	int fsize = facts.size();
	while (1)
	{
		choice = GetOption();
		random = rand()%facts.size();
		switch (choice)
		{
			case 1:
				SingleShot(facts, people, random);
				break;
			case 2:
				PlayFact(facts[random]);
				break;
			case 3:
				Schedule(people, facts);
				break;
			case 4:
				ListFacts(facts);
				break;
			case 5:
				ListPeople(people);
				break;
			case 6:
				exit(1);
			default:
				std::cout<<"What?\n";
		}
	}
	return 0;
}

void ParseConfig(std::ifstream &inconfig, PeopleType &people, FactType &facts)
{
	std::string tmp;
	while (true)
	{
		std::getline(inconfig,tmp);
		if (tmp.substr(0,8)=="factfile")
		{
			std::cout<<"Looking for facts file...";
			std::ifstream infacts(tmp.substr(9,std::string::npos).c_str());
			if (infacts==NULL)
			{
				std::cout<<"Error finding file!\n";
				exit(1);
			}
			else
			{
				std::cout<<"done!\n";
				facts = GetFacts(infacts);
			}
			infacts.close();
		}
		else if (tmp.substr(0,9)=="namesfile")
		{
			std::cout<<"Looking for people file...";
			std::ifstream inpeople(tmp.substr(10,std::string::npos).c_str());
			if (inpeople==NULL)
			{
				std::cout<<"Error finding file!\n";
				exit(1);
			}
			else
			{
				std::cout<<"done!\n";
				people = GetPeople(inpeople);
			}
			inpeople.close();
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
	std::cout<<"\n";
	std::cout<<"Version 1.0\n";
	std::cout<<"Developed mostly during HACK(RPI); Fall 2014 as a whimsical but vengeful project.\n";
	std::cout<<"Code by Kienan Knight-Boehm (kienankb.com), ASCII art by http://patorjk.com/software/taag/\n\n";
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
	//system(("echo "+fact+" | festival --tts").c_str());
	return;
}

int GetOption()
{
	int choice;
	std::cout<<"\n";
	std::cout<<"1.\tPick a one-time victim\n";
	std::cout<<"2.\tHear a fact\n";
	std::cout<<"3.\tAutopilot\n";
	std::cout<<"4.\tList facts\n";
	std::cout<<"5.\tList targets\n";
	std::cout<<"6.\tQuit\n\n";
	std::cin>>choice;
	return choice;
}

void PlayFact(std::string fact)
{
	std::string command = "echo \"Did you know? "+fact+" \" | festival --tts";
	system(command.c_str());
	std::cout<<fact<<std::endl;
	return;
}

void SingleShot(FactType &facts, PeopleType &people, int random)
{
	int targetchoice;
	char sure;
	ListPeople(people);
	std::cout<<"Choose one!\n";
	std::cin>>targetchoice;
	if (targetchoice < 0 || targetchoice >= people.size())
	{
		std::cout<<"Invalid.\n";
		return;
	}
	std::cout<<"Sending to "<<people[targetchoice].first<<".  Ya sure? (y/n)\n";
	std::cin>>sure;
	if(sure=='y')
	{
		FireMessage(facts[random],people[targetchoice].second);
		std::cout<<"Sent.\n";
	}
	else
	{
		std::cout<<"Nevermind, cancelled.\n";
	}
}

void ListPeople(PeopleType &people)
{
	std::cout<<"\tHere be yer targets, cap'n:\n\n";
	for(size_t i = 0; i < people.size(); i++)
	{
		std::cout<<i<<":\t"<<people[i].first<<": "<<people[i].second<<"\n";
	}
}


void ListFacts(FactType &facts)
{
	std::cout<<"\tHere's your ammunition, cap'n:\n\n";
	for(size_t i = 0; i < facts.size(); i++)
	{
		std::cout<<facts[i]<<"\n";
	}
}

void Schedule (PeopleType &people, FactType &facts)
{
	int targetchoice, interval, max;
	char confirm;
	std::cout<<"So you want me to do the work for you, huh?  Alright.\n";
	std::cout<<"Here are your targets.\n";
	ListPeople(people);
	std::cout<<"Choose one: ";
	std::cin>>targetchoice;
	if (targetchoice < 0 || targetchoice >= people.size())
	{
		std::cout<<"Invalid choice, knucklehead.\n";
		return;
	}
	std::cout<<"Sending facts to "<<people[targetchoice].first<<".\n";
	std::cout<<"How many minutes should elapse between blasts?";
	std::cin>>interval;
	std::cout<<"How many facts total?";
	std::cin>>max;
	std::cout<<"To recap: every "<<interval<<" minutes, send a random fact to "<<people[targetchoice].first<<" until "<<max<<" facts have been sent.\n";
	std::cout<<"Confirm? (y/n) ";
	std::cin>>confirm;
	if (confirm != 'y')
	{
		return;
	}
	std::cout<<"Here we go!\n";
	int msgnum = 0;
	while (msgnum<max)
	{
		FireMessage(facts[rand()%facts.size()],people[targetchoice].second);
		std::cout<<"Sent message "<<msgnum+1<<" of "<<max<<".  Now waiting for "<<interval<<" minutes.\n";
		msgnum++;
		sleep(60*interval);
	}
}
