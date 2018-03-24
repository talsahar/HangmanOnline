
## Introduction
#### Hangman online is a C++ console multiplayer UDP game. One player thinks of a word, phrase or Sentence and the other tries to guess it by suggesting [[Letters(alphabet)| or numbers, within a certain number of guesses.
## The Server
Hangman runs on a generic TCP server platform framework I created. Responsible for users authentication, store their score on database and as a third party to connect users each other. 
It allow users to:
1. Register and login.
2. Ask for the online user list.
3. Choose who they want to connect with.
4. Connection invitation, acception, rejection.
5. Auto-matching (The server will make the auto match between 2 automatchers).
6. Ask for list of the top 10 users with the highest score.

#### Its server platform can run any program that support the platform's protocol, only by using the client's API and inherit its abstract interface which supply the delegates for the different callback situations. In our case out Hangman library use this API.
