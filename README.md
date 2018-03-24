
## Introduction
#### Hangman online is a console multiplayer game, written in C++, based on TCP, UDP transport protocols. One player thinks of a word, phrase or Sentence and the other tries to guess it by suggesting [[Letters(alphabet)| or numbers, within a certain number of guesses.
## The Server
Runs on a generic TCP server platform framework in C++. Responsible for users authentication, store their score on database and as a third party which connecting users each other. 
It allows users to:
1. Register and login.
2. Ask for the online user list.
3. Choose who they want to connect and play with.
4. Game invitation, acception, rejection.
5. Auto-matching (The server will make the auto match between 2 random players).
6. Ask for top 10 highest score players.

#### Its server platform can run any program which supports the platform's protocol, only by using the client's API and inherit its abstract interface.
