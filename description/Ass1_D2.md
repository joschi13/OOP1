# Assignment 1 - Deliverable 2

Die allgemeine Spielbeschreibung ist unter [README.md](../README.md) nachzulesen.



Im Deliverable 2 soll das Config-File eingelesen und verarbeitet werden. 

Das Config-File ist eine JSON-Datei, welche mit der vom Framework mitgegebenen [`RapidJSON`](https://rapidjson.org/) Bibliothek geparsed werden kann und somit ein leichtes Erstellen der Karten ermöglichen soll.

Die Bibliothek kann über `#include "rapidjson/document.h" ` verwenden werden. [Je nachdem welche Befehle der rapidjson Library verwendet werden, müssen ggf. andere Bibliotheken eingebunden werden. (z.B.: `#include "rapidjson/istreamwrapper.h" `, ...)] Nähere Informationen zur Verwendung von [`RapidJSON`](https://rapidjson.org/) sind unter [`rapidjson.org`](https://rapidjson.org/) zu finden.

Sie können natürlich auch Ihren eigenen JSON-Parser schreiben, um die Config-Files einzulesen.

Ein valides Config-File wird unter [`config/`](../config/config01.json) bereitgestellt.


## Config-File

### Bedingungen für ein gültiges Config-File

- Insgesamt mindestens 10 Karten

- Alle Namen sind case-sensitive (d.h. Groß- und Kleinschreibung wird beachtet) 
  (z.B.: Monster mit Attribut "Name" statt "name" ist ungültig)

- Das Config-File muss in 2 Teile eingeteilt sein: `Creatures` und `Spells`.

  - `Creatures` ist ein Array aus Kreaturen - hier dürfen nur Kreaturkarten vorkommen
  - `Spells` ist ein Array aus Zaubersprüchen - hier dürfen nur Zaubersprüche vorkommen

- Kreaturenkarten sind JSON-Objekte und erfüllen folgende Bedingungen:

  - Schadenswert (`damage_points`) ist eine Ganzzahl im Bereich 0-9
  - Lebenspunkte (`life_points`) ist eine Ganzzahl im Bereich 1-9.
  - Kreaturen haben einen eindeutigen Namen mit einer maximalen Länge von 8 Zeichen.
  - <mark>`mana_cost` ist eine Ganzzahl im Bereich 1-15.</mark>

  - `shield` und `mana_drain` sind Wahrheitswerte
  - Es müssen alle 6 Attribute vorhanden sein (die Reihenfolge ist dabei egal): 
    - `name`
    - `mana_cost`
    - `damage_points`
    - `life_points`
    - `shield`
    - `mana_drain`

- Zaubersprüche sind JSON-Objekte und erfüllen folgende Bedingungen:

  - Zaubersprüche haben nur einen eindeutigen Namen.

    - Es darf kein zusätzliches Attribut vorhanden sein

  - `name` muss exakt einer der folgenden 4  sein und dem enum SpellType zuordenbar:

    - ```
      enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA}
      ```
      
    - name: "Healer" => `SpellType.HEALER`

    - name: "Relief" => `SpellType.RELIEF`

    - name: "Rebirth" => `SpellType.REBIRTH`

    - name: "Dracula" => `SpellType.DRACULA`

    - wobei der name im Config-File gleich dem Variablennamen im Framework sein muss
      zB Oop::Interface::STRING_HEALER
    
      - Achtung: case sensitive: der Name im Config-File muss mit einem Großbuchstaben beginnen (Siehe [Beispiel-Config-File](#Beispiel-Config-File)).
      - Stimmt der Name **nicht** mit einem Namen im Framework überein, ist das Config-File ungültig
    
  - Es müssen nicht alle Zaubersprüche aus dem enum im Config-File vorkommen

- Karten **dürfen** öfter vorkommen, jedoch:

  - Kreaturenkarten mit **gleichen** Namen haben **gleiche Attributwerte** (Lebenspunkte, Schaden...) 
    (case sensitiv: Monster mit den Namen "Fee" und "feE" werden nicht als gleich angesehen))

Trifft eine dieser Bedingungen **NICHT** zu, so ist das Config-File ungültig und das Programm soll mit **-3** beenden (`Oop::RETURN_ERROR_BAD_CONFIG`).




### Beispiel-Config-File

```
{
  "Creatures" : [
    {
      "name": "Big Wall",
      "mana_cost": 7,
      "damage_points": 2,
      "life_points": 9,
      "shield": true,
      "mana_drain": false
    },
    {
      "shield": false,
      "damage_points": 9,
      "life_points": 3,
      "mana_cost": 7,
      "name": "Bigfoot",
      "mana_drain": false
    },
    {
      "name": "Goblin",
      "mana_cost": 2,
      "damage_points": 3,
      "life_points": 2,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Cristian",
      "mana_cost": 14,
      "damage_points": 9,
      "life_points": 9,
      "shield": false,
      "mana_drain": true
    },
    {
      "name": "Aleks",
      "mana_cost": 8,
      "damage_points": 3,
      "life_points": 9,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "Simone",
      "mana_cost": 2,
      "damage_points": 1,
      "life_points": 2,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Katrin",
      "mana_cost": 7,
      "damage_points": 5,
      "life_points": 6,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Matthias",
      "mana_cost": 4,
      "damage_points": 4,
      "life_points": 4,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Kevin",
      "mana_cost": 2,
      "damage_points": 4,
      "life_points": 1,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Florian",
      "mana_cost": 6,
      "damage_points": 1,
      "life_points": 8,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "Florian",
      "mana_cost": 6,
      "damage_points": 1,
      "life_points": 8,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "David A",
      "mana_cost": 8,
      "damage_points": 8,
      "life_points": 7,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Michael",
      "mana_cost": 6,
      "damage_points": 5,
      "life_points": 6,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Clemens",
      "mana_cost": 8,
      "damage_points": 5,
      "life_points": 9,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Thomas",
      "mana_cost": 3,
      "damage_points": 0,
      "life_points": 5,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "David K",
      "mana_cost": 4,
      "damage_points": 2,
      "life_points": 5,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Troll",
      "mana_cost": 8,
      "damage_points": 8,
      "life_points": 1,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Einhorn",
      "mana_cost": 2,
      "damage_points": 2,
      "life_points": 2,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Bluthund",
      "mana_cost": 6,
      "damage_points": 4,
      "life_points": 8,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "Kankra",
      "mana_cost": 4,
      "damage_points": 4,
      "life_points": 3,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Smaug",
      "mana_cost": 13,
      "damage_points": 8,
      "life_points": 8,
      "shield": false,
      "mana_drain": true
    },
    {
      "name": "Golem",
      "mana_cost": 8,
      "damage_points": 7,
      "life_points": 8,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Fee",
      "mana_cost": 1,
      "damage_points": 1,
      "life_points": 1,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Mini Ork",
      "mana_cost": 2,
      "damage_points": 2,
      "life_points": 1,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Miniwall",
      "mana_cost": 1,
      "damage_points": 0,
      "life_points": 4,
      "shield": true,
      "mana_drain": false
    },
    {
      "name": "Elf",
      "mana_cost": 4,
      "damage_points": 3,
      "life_points": 4,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Geist",
      "mana_cost": 5,
      "damage_points": 2,
      "life_points": 6,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Kobold",
      "mana_cost": 6,
      "damage_points": 8,
      "life_points": 1,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Greif",
      "mana_cost": 5,
      "damage_points": 5,
      "life_points": 6,
      "shield": false,
      "mana_drain": false
    },
    {
      "name": "Werwolf",
      "mana_cost": 13,
      "damage_points": 9,
      "life_points": 6,
      "shield": false,
      "mana_drain": false
    }
  ],
  "Spells" : [
    {
      "name": "Healer"
    },
    {
      "name": "Relief"
    },
    {
      "name": "Rebirth"
    },
    {
      "name": "Dracula"
    }
  ]
}

```




## Spielstart

Bei erfolgreichem Einlesen des [Config-Files](#ConfigFile) sollen die Karten gemischt und ausgeteilt werden.

Beide Spieler erhalten das selbe [Config-File](#ConfigFile) und somit auch dieselben Karten. Vor Spielbeginn (und vor dem Abheben der 3 Handkarten) **MUSS** das Deck für beide Spieler extra gemischt werden, sodass beide Spieler eine unterschiedliche Reihenfolge der Karten haben.  Es muss dafür die Funktion `Random::shufflePickupstack` aus dem [Framework](FrameworkDescription.md) verwendet werden (Details zur Nutzung dieser Funktion siehe [Framework](FrameworkDescription.md)).



<mark>Danach</mark> sollen die beiden Spielernamen eingegeben werden können. Das Framework stellt dafür die Funktion `Oop::Interface::readPlayerName()` zur Verfügung. 

**Nach dem Doppelpunkt folgt ein Leerzeichen**, danach soll der Name eingegeben werden können.

#### Spielernamen eingeben

```
[INFO] Please enter the name of player 1: 
```

Dasselbe für den 2. Spieler:

```
[INFO] Please enter the name of player 2: 
```

Die Spielernamen sollen im Attribut `name_` in Player gespeichert werden.

#### Spielrunde

Danach startet die erste Spielrunde. Zu Beginn jeder Spielrunde (Erinnerung: 1 Runde = 2 Züge) soll die aktuelle Spielrunde ausgegeben werden:

```
[INFO] Round: X
```

Wobei **`X`** für die aktuelle Runde, beginnend bei 0, steht.

#### Spielzug (pro Spieler)

Zu Beginn jedes Spielzuges soll der Name des aktuellen Spielers ausgegeben werden:

```
[INFO] Current player is X
```

Wobei **`X`** für den Namen des aktuellen Spielers steht, welcher zu Spielbeginn vergeben wurde.

Danach soll das Start-Spielfeld ausgegeben werden.

Anschließend soll der Name des ziehenden Spielers als Standardpromt ausgegeben werden:

- `christian > ` wenn `name_` des Spielers, der gerade an der Reihe ist, "christian" lautet.
- `DaViD > ` wenn `name_` des Spielers, der gerade an der Reihe ist, "DaViD" lautet.

Wird kein Befehl (nur Enter) eigegeben, so soll der Standardprompt erneut ausgegeben werden.



### Beispielstart des Spiels

**Achtung**: Zu Beginn erhalten beide Spieler 3 Handkarte. `christian` ist zuerst dran. Er hebt also gleich eine Karte vom Abhebestapel ab, daher hat er in der ersten Runde bereits 4 Handkarten.

Die Commands werden im [Deliverable 3](Ass1_D3.md) implementiert



```
./game config/config01.json
[INFO] Please enter the name of player 1: christian
[INFO] Please enter the name of player 2: DaViD
[INFO] Round: 0
[INFO] Current player is christian

==================================================================================

     ______     ______     ______                                                 
H   |      |   |      |   |      |                                               H
A   |      |   |      |   |      |                                               A
N   |      |   |      |   |      |                                               N
D   |      |   |      |   |      |                                               D
    |______|   |______|   |______|                                                

============================= LP : 30 | MANA :  0/15 =============================


G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

~~~~~~ 01 ~~~~~~~ 02 ~~~~~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~
                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

============================= LP : 30 | MANA :  1/15 =============================

    08_____    07_____    02_____    06_____S                                     
H   |      |   |      |   |      |   |      |                                    H
A   Clemens    Katrin     Dracula    Florian                                     A
N   |      |   |      |   |      |   |      |                                    N
D   |      |   |      |   |      |   |      |                                    D
    05____09   05____06   x______x   01____08                                     

==================================================================================

christian > 
christian > 
christian > 
christian > finish
[INFO] Current player is DaViD

==================================================================================

     ______     ______     ______     ______                                      
H   |      |   |      |   |      |   |      |                                    H
A   |      |   |      |   |      |   |      |                                    A
N   |      |   |      |   |      |   |      |                                    N
D   |      |   |      |   |      |   |      |                                    D
    |______|   |______|   |______|   |______|                                     

============================= LP : 30 | MANA :  1/15 =============================

                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

~~~~~~ 01 ~~~~~~~ 02 ~~~~~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~

                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

============================= LP : 30 | MANA :  1/15 =============================

    03_____S   03_____    02_____    05_____                                      
H   |      |   |      |   |      |   |      |                                    H
A   Thomas     Relief     Einhorn    Healer                                      A
N   |      |   |      |   |      |   |      |                                    N
D   |      |   |      |   |      |   |      |                                    D
    00____05   x______x   02____02   x______x                                     

==================================================================================

DaViD > 
DaViD > 
DaViD > finish
[INFO] Round: 1
[INFO] Current player is christian

==================================================================================

     ______     ______     ______     ______                                      
H   |      |   |      |   |      |   |      |                                    H
A   |      |   |      |   |      |   |      |                                    A
N   |      |   |      |   |      |   |      |                                    N
D   |      |   |      |   |      |   |      |                                    D
    |______|   |______|   |______|   |______|                                     

============================= LP : 30 | MANA :  1/15 =============================

                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

~~~~~~ 01 ~~~~~~~ 02 ~~~~~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~

                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

============================= LP : 30 | MANA :  3/15 =============================

    08_____S   06_____S   05_____    13_____M   06_____                           
H   |      |   |      |   |      |   |      |   |      |                         H
A   Aleks      Bluthund   Geist      Smaug      Michael                          A
N   |      |   |      |   |      |   |      |   |      |                         N
D   |      |   |      |   |      |   |      |   |      |                         D
    03____09   04____08   02____06   08____08   05____06                          

==================================================================================

christian > 

```



#  Spezifikation

-  nur geforderte Ausgaben
-  Es **MUSS** jede Klasse im Oop-Namespace enthalten sein.

##  Erlaubte Bibliotheken

-  alle Bibliotheken der C++ Standard Library

## Abgabe

- siehe  [Assignment Description](Assignments.md)

