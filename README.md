#FactBlaster

**Because you have too many friends.  Let's fix that.**

Ever heard of CatFacts?  No?  It's a service that sends out regular facts about cats via SMS.  Sounds harmless, right?  Sign your friends up for it and see if they have the same answer.  FactBlaster's goal is to bring the joy of CatFacts home and expand it to facts about everything, written by you and of questionable veracity!

FactBlaster, originally designed for the RasPi and started as a Hack(RPI); Fall 2014 project, is designed to run on a Linux computer that has SSMTP (and optionally Festival TTS) installed.  It utilizes the email-to-SMS gateways that most, if not all, carriers have.

#Gateways

As stated above, most carriers have an email-to-SMS gateway.  In other words, if you send an email to a specific address, it is delivered as an SMS to the person.  Often these are of the form `<number>@<carrier-specific suffix>`.  I'm looking into ways for the program to automatically determine carrier based on number, but since most APIs are either broken, inaccurate, or expensive, you're on your own for the moment and will have to use free websites.  There are tons, don't worry.

#Installation

##SSMTP

First thing's first: you'll need an email account from which to send email.  I used a throwaway Gmail account.  Next, Install SSMTP on your machine.  If, after compiling FactBlaster, you get a message saying something like `mail: command not found`, install mailutils as well.  Edit the following config files:

`/etc/ssmtp/ssmtp.conf`:
```
root=<email address>
mailhub=<email ssmtp server>
hostname=<sender, I use the email address>
UseTLS=YES
UseSTARTTLS=YES
AuthUser=<email address>
AuthPass=<email password>
FromLineOverride=YES
```

And `/etc/ssmtp/revaliases`:
```
<username that can send mail>:<email address>:<email smtp server>
```
(add a line like that for each user you want to run it as)

If mail returns with an error exit code, you may have to have Gmail allow access to "less secure apps".  Buncha prudes.

##Program Setup

I've done a little bit of reworking how the program loads info, and I'll probably continue to do so.  For now, no more mucking about with config files.  Run make (with g++ installed) to build.  Make two files in the same directory: `people.txt` and `facts.txt` (the list of facts and names/addresses, respectively).  `facts.txt` should simply have one fact per line, and `names.txt` should be of the format:
```
Jane Doe
0123456789@vtext.com
John Smith
9876543210@txt.att.net
```
Name on one line, address on the next.  If you know the carrier, you can just look up the gateway email address format for it; if not you can use a free website to do the lookup for you.  I'm working on adding carrier determination to the program, but for now:

Have fun.  And don't be a jerk.
