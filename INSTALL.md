This covers for OpenSuse, other distros shall be similar.

## OFICINA SOURCE CODE ##
To checkout the code you need the git package, install it with: 

zypper in git-core

Now, clone the source code repository:

git clone https://github.com/bedi1982/Oficina.git

This will create a folder called 'Oficina'

## QtCreator ##
Install it with:

zypper in libqt5-creator

Open 'QtCreator'  from menu, in QtCreator menu select: 'File' -> 'Open File or Project' then select the file 
Oficina.pro from the 'Oficina' folder created by the git clone command.

At this point you can already build(hammer icon left down in QtCreator) and run (green play icon left down in QtCreator). 
But at this point the Oficinal application won't be much functional as it hides the functions when the database is not available.

## DATABASE ##

Oficina uses mysql, so:

zypper in  mysql

To test mysql, make sure it is started:

systemctl status mysql

If you see: "Active: inactive (dead)" the you have to start it with:

systemctl start mysql

To test, just type in a terminal as root:

mysql

This will log you in to mysql as root user, assuming your root has not a password defined (which is default).

Now in the terminal with mysql open paste the contents of the following file:
https://github.com/bedi1982/Oficina/blob/master/Oficina.sql

When this is done the application is ready to use.
