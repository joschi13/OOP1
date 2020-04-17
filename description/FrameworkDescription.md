# Framework



### Git Repository clonen

Achtung: **reponame** muss durch den Namens eures Repository ersetzt werden!

```
git clone git@gitlab.tugraz.at:oop1-2020/<reponame>.git
```



### Git Upstream Repository hinzufügen

Sollten nachträglich kleine Änderungen in der Angabe oder im Framework vorgenommen werden, werden diese im allgemeinen Upstream Repository durchgeführt. Um immer den aktuellen Stand zu erhalten, muss daher das Upstream Repository einmalig hinzugefügt werden.


Füge das Upstream Repository einmalig hinzu:

```
git remote add upstream https://gitlab.tugraz.at/oop1-2020/assignment
```



**Wir empfehlen euch täglich vor Arbeitsbeginn vom Upstream zu pullen**

```
git pull upstream master 
```



## Aufbau des Repositories

```
config/     (Stellt die ConfigFiles für das Spiel bereit)
	config01.json
	config08_bonus.json
description/  (Die Spielanleitung aufgeteilt auf mehrere .md File zur besseren Übersicht)
	Ass1_D1.md
	Ass1_D2.md
	Ass1_D3.md
	Assignments.md
	ErrorDescription.md
	FrameworkDescription.md
	GameField.md
	SpellCardDescription.md
rapidjson/   (RapidJson Framework für das Einlesen des ConfigFiles)
    ...
Interface.cpp
Interface.hpp
main.cpp
Makefile
Random.cpp
Random.hpp
README.md
```

Das bereitgestellte Framework (`Interface.hpp`, `Interface.cpp`, `Random.hpp`, `Random.cpp`, <mark>**`main.cpp`**</mark> ) soll **unverändert** bleiben.



### Interface Klasse

Folgende Funktionen existieren:

- `Interface()`
  - Konstruktor für Interface
- `std::string in()`
  - Übernimmt das Lesen der User-Eingabe. Soll statt `std::cin` benutzt werden.
  - Rückgabewert
    - Der eingegebene Text des Users
- `void out(const OutputType type, const std::string msg)`
  - Gibt eine Nachricht aus. Soll statt `std::cout` benutzt werden.
  - Parameter:
    - `type`: Gibt Typ der Nachricht an (`DEBUG`, `ERROR`, `WARNING` oder `INFO`)
    - `msg`: Die Nachricht. Nutzt `std::strings` in `Interface`.
- `void out(const Player* current_player, const Player* opponent_player)`
  - Gibt das Spielfeld aus.
  - Parameter:
    - `current_player`: Pointer auf aktuellen Spieler
    - `opponent_player`: Pointer auf anderen Spieler
- `std::string readPlayerName(bool player)`
  - Fragt den Spieler nach seinen Namen.
  - Parameter:
    - `player`: Die Spieler ID (Spieler 0  oder 1)
  - Rückgabewert:
    - Der gewählte Name
- `std::string askPlayer(const std::string msg)`
  - Stellt dem Spieler eine Frage und gibt die Antwort zurück.
  - Parameter:
    - `msg`: Die Frage
  - Rückgabewert:
    - Die Antwort
- `void printCommandPrompt(const std::string player_name)`
  - Gibt den Command Prompt aus.
  - Parameter:
    - `player_name`: Name des aktuellen Spielers
- `void log(const std::string msg)`
  - Kann genutzt werden um mitzuloggen was passiert (nützlich für Fehlersuche).
  - Parameter:
    - `msg`: Die Nachricht die geloggt wird
- `void error(const std::string msg)`
  - Soll nur vor dem Beenden des Spiels aufgrund eines Fehlers aufgerufen werden.
  - Parameter:
    - `msg`: Die Nachricht



### Random Klasse

Die Random Klasse dient zur Generierung von Zufallszahlen, um eine unvorhersehbare Reihenfolge der Karten im Abhebestapel zu erstellen. Diese Klasse ist als [Singleton](https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Entwurfsmuster:_Singleton) implementiert. Das bedeutet, es kann nur eine Instanz der Klasse erstellt werden. Mittels `Oop::Random::getInstance()`  kann auf die Klasse zugegriffen werden.



Folgende Funktionen existieren:

- `Random& getInstance()` 
  - gibt die Referenz auf die Instanz der Klasse Random zurück

- `unsigned int getSeed()`
  - Wird nur im Konstruktor von Random genutzt und erstellt eine Zufallszahl
- `shufflePickupstack(std::vector<Card*>& pick_up_stack)`
  - Nimmt als Parameter eine Referenz auf den Vector aus Karten und mischt diesen Vector mithilfe der Zufallszahl
  - Parameter:
    - `pick_up_stack`: Der Abhebestapel eines Spielers





## Makefile

Zum Kompilieren und Ausführen kann das bereitgestellte Makefile verwendet werden:

#### make

- Kompiliert das Programm

#### make clean

- Entfernt alle temporären Dateien (inklusive executable).

#### make run

- Führt das Programm aus und verwendet das Config-File *config/config01.json*

#### make bonus

- Führt das Programm aus und verwendet das Bonus-Task-Config-File *config/config08_bonus.json*

