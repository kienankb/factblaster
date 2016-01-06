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

void		SayHello	();
PeopleType	GetPeople	(std::string peoplefile);
FactType	GetFacts	(std::string factsfile);
void		FireMessage	(std::string message, std::string address);
int			GetOption	();
void		PlayFact	(std::string fact);
void		SingleShot	(FactType &facts, PeopleType &people, int random);
void		ListPeople	(PeopleType &people);
void		ListFacts	(FactType &facts);
void		Schedule	(PeopleType &people, FactType &facts);
void		WriteData	(PeopleType &people, FactType &facts);

int main(int argc, char *argv[])
{
	srand(time(NULL));									// Set up randomization, people, facts, etc.
	PeopleType people;
	FactType facts;
	SayHello();
	facts = GetFacts("facts.txt");
	people = GetPeople("people.txt");
	int choice, random;
	int fsize = facts.size();
	while (1)											// Main loop w/choices
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
				WriteData(people, facts);
				exit(0);
			default:
				std::cout<<"What?\n";
		}
	}
	return 0;
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
	std::cout<<"Version 0.2 BETAAAA\n";
	std::cout<<"Developed partly during HACK(RPI); Fall 2014 as a whimsical but vengeful project.\n";
	std::cout<<"Developed mostly after HACK(RPI); Fall 2014 as an equally vengeful project.  Tad less whimsical, maybe.\n";
	std::cout<<"Code by Kienan Knight-Boehm (kienankb.com), ASCII art by http://patorjk.com/software/taag/\n";
	std::cout<<"Special thanks to Josh Goldberg for testing.\n\n";
}

//
// FUNCTION:
//	Load in the list of people and numbers/address from the
//	given file, returning the proper container.
//
PeopleType GetPeople(std::string peoplefile)
{
	std::cout<<"Looking for people file "<<peoplefile<<"...";
	std::ifstream inpeople(peoplefile.c_str());
	if (inpeople == NULL) {
		std::cerr<<"\nSAM JACKSON CAN'T FIND YOUR MUTHAF**KIN' PEOPLE FILE!\n";
		exit(1);
	}
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
	std::cout<<result.size()<<" people found.\n";
	inpeople.close();
	return result;
}

//
// FUNCTION:
//	Load in the list of facts from the given file, returning
//	the proper container.
//
FactType GetFacts(std::string factsfile)
{
	std::cout<<"Looking for facts file "<<factsfile<<"...";
	std::ifstream infacts(factsfile.c_str());
	if (infacts == NULL) {
		std::cerr<<"\nFind your facts file, Yoda can not.\n";
		exit(1);
	}
	FactType result;
	std::string tmp;
	while (true)
	{
		if (infacts.eof()) break;
		std::getline(infacts,tmp);
		if (tmp != "") {
			result.push_back(tmp);
		}
		tmp.clear();
	}
	std::cout<<result.size()<<" facts found.\n";
	infacts.close();
	return result;
}

//
// FUNCTION:
//	Does the dirty work of actually firing off a message.
//
void FireMessage(std::string message, std::string address)
{
	std::string commandstring = "echo \"Did you know? "+message+" Reply STOP to cancel.\" | mail -a \"From: FunFactsHomeEdition\" "+address;
	system(commandstring.c_str());
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

//
// FUNCTION:
//	Really specific TTS stuff, I'll probably wipe this out
//	at some point
//
void PlayFact(std::string fact)
{
	std::string command = "echo \"Did you know? "+fact+" \" | festival --tts";
	system(command.c_str());
	std::cout<<fact<<std::endl;
	return;
}

//
// FUNCTION:
//	Fire a one-time shot to a victim.
//
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
	else { std::cout<<"Nevermind, cancelled.\n"; }
}

void ListPeople(PeopleType &people)
{
	std::cout<<"\tHere be yer targets, cap'n:\n\n";
	for(size_t i = 0; i < people.size(); i++) { std::cout<<i<<":\t"<<people[i].first<<": "<<people[i].second<<"\n"; }
}


void ListFacts(FactType &facts)
{
	std::cout<<"\tHere's your ammunition, cap'n:\n\n";
	for(size_t i = 0; i < facts.size(); i++) { std::cout<<facts[i]<<"\n"; }
}

//
// FUNCTION:
//	More advanced scheduling for fact blasting.
//
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
	if (confirm != 'y') { return; }
	std::cout<<"Here we go!\n";
	int msgnum = 0;
	while (msgnum<max)
	{
		FireMessage(facts[rand()%facts.size()],people[targetchoice].second);
		std::cout<<"Sent message "<<msgnum+1<<" of "<<max<<".  Now waiting for "<<interval<<" minutes.\n";
		msgnum++;
		if (msgnum==max) {
			break;
		}
		sleep(60*interval);
	}
}

void WriteData(PeopleType &people, FactType &facts)
{
	std::cout<<"Rewriting fact and target files...\n";
	std::ofstream outpeople("people.txt");
	std::ofstream outfacts("facts.txt");
	if (outpeople == 0 || outfacts == NULL) {
		std::cerr<<"Error writing data files!\n";
		exit(1);
	}
	for (size_t i = 0; i < people.size(); i++) {
		outpeople<<people[i].first<<"\n";
		outpeople<<people[i].second<<"\n";
	}
	outpeople.close();
	for (size_t i = 0; i < facts.size(); i++) {
		outfacts<<facts[i]<<"\n";
	}
	outfacts.close();
}
