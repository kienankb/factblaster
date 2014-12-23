#FactBlaster

**Because you have too many friends.  Let's fix that.**

Ever heard of CatFacts?  No?  It's a service that sends out regular facts about cats via SMS.  Sounds harmless, right?  Sign your friends up for it and see if they have the same answer.  FactBlaster's goal is to bring the joy of CatFacts home and expand it to facts about everything, written by you and of questionable veracity!

FactBlaster, originally designed for the RasPi and started as a Hack(RPI); Fall 2014 project, is designed to run on a Linux computer that has SSMTP (and optionally Festival TTS) installed.  It utilizes the email-to-SMS gateways that most, if not all, carriers have.

#Gateways

As stated above, most carriers have an email-to-SMS gateway.  In other words, if you send an email to a specific address, it is delivered as an SMS to the person.  Often these are of the form `<number>@<carrier-specific suffix>`.  I'm looking into ways for the program to automatically determine carrier based on number, but since most APIs are either broken, inaccurate, or expensive, you're on your own for the moment and will have to use free websites.  There are tons, don't worry.

#Installation

I recommend installing and configuring SSMTP on whatever computer you're using, but if you can find something else that works that's great.  It sends texts by piping an echoed string to the command `mail <address>`, so if you have something that fits that, you're good to go.

You'll need to do a little config work as well--not much, and I'll probably make things easier in future releases.  To build the program, run `make` (you'll need g++ obviously).  Create the file `factblaster.config` in the same directory; it will be of the structure:
```
factfile:facts.txt
namesfile:names.txt
```

where facts.txt is just a text file with a fact on each line and names.text has a name on a line and the address below.  For example:

```
Jane Doe
0123456789@vtext.com
John Smith
9876543210@txt.att.net
```
As I said, in future releases the program will do much more for you; I'm considering storing things with JSON, creating command-line argument options, etc.  But for now:

Have fun.  And don't be a jerk.
