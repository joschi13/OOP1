# Assignment 1 - Deliverable 3

Im Deliverable 3 soll die gesamte Spiellogik implementiert werden. Ist das Config-File eingelesen, kann das Spiel starten. Um jedoch spielen zu können, benötigt man Commands, die über das CLI eingegeben werden können. Diese Commands sollen nun im D3 implementiert werden.

Die allgemeine Spielbeschreibung ist unter [README.md](../README.md) nachzulesen.





# Benutzereingabe

### Standardprompt

Siehe [Deliverable 2](Ass1_D2.md) unter Spielstart.



### Befehle

**Allgemein gilt:**

- Hat man für einen Befehl <mark>(set oder cast)</mark> nicht genügend Mana, soll folgende Fehlermeldung ausgegeben werden:

  ```
  [INFO] Not enough mana for this move!\n
  ```

- Treffen mehrere Fehlermeldungen bei einem Command gleichzeitig zu, ist nur jene mit der höchsten Priorität auszugeben. Die Priorität entspricht der Reihenfolge in [Fehlermeldungen](ErrorDescription.md).

- Alle Befehle sind case-insensitive, das heißt Groß- und Kleinschreibung wird nicht beachtet.

- <mark>Es können mehrfach Leerzeichen vor, zwischen und nach den Befehlen vorkommen. Der Befehl bleibt dadurch gültig. z.B. "    set      3               to    1      "   (Hinzugefügt David K. 4.4.)</mark> 

- In eckige Klammern geschriebene Buchstaben [X] [Y] sind die Parameter dieser zu implementierenden Funktion.

- Das Spielfeld soll nicht nach jedem Befehl ausgegeben werden, sondern nur zu Beginn des Spielzuges und nach Eingabe des Befehls [`state`](#state)



#### help

```
help 
```

gibt den String unter `Oop::Interface::INFO_HELP_MSGS` aus.



#### state

```
state
```

gibt das aktuelle Spielfeld aus.



#### attack [X] with [Y]

Die Kreatur an der Position Y am eigenen Spielfeld greift die Kreatur an der Position X des Spielfeldes des Gegners an. Eine Kreatur kann nur 1 Mal pro Runde angreifen.

```
attack X with Y
```

###### Parameter

- **X**: Falls der Wert X in der Menge {1, 2, ..., 7} ist, so gibt X die Position der Kreatur am gegnerischen Spielfeld an, die angegriffen werden soll. Wenn X gleich 0 ist, soll der Gegner direkt angegriffen werden.
    - Mögliche Werte: 0 bis 7

- **Y**: Position auf dem (eigenen) Spielfeld jener Kreatur, die angreifen soll.
    - Mögliche Werte: 1 bis 7
    - 0 ist kein möglicher Wert, da 0 der Index des eigenen Spielers ist. Spieler können jedoch nicht selbst angreifen; nur Kreaturen können angreifen.

###### Fehler

Ist einer der Parameter außerhalb des vorgegebenen Wertebereichs, soll folgende Fehlermeldung ausgegeben werden: 

```
[INFO] Invalid command parameter!\n
```

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```

Sind beide Parameter innerhalb des vorgegebenen Wertebereichs und kann der Befehl nicht ausgeführt werden, weil z.B.

- die Position am eigenen Spielfeld leer ist oder
- die Position auf dem gegnerischen Spielfeld leer ist oder
- die Kreatur in dieser Runde schon angriffen hat,

 soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Execution not possible!\n
```

Wird versucht, den Gegner direkt oder eine Kreatur ohne Schild anzugreifen, obwohl der Gegner über eine Schild-Kreatur verfügt, so ist der Angriff nicht möglich und es soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Destroy all shields first!\n
```



#### set [X] to [Y]

Setzt die Kreatur an Position X auf der Hand des ziehenden Spielers an die Position Y seines Spielfelds. Mit dem set-Command können nur Kreaturen ausgespielt werden. Für Zauberkarten ist der cast-Command zu implementieren.

```
set X to Y
```

###### Parameter

- **X**: Position der Kreatur auf der Hand (Handkarten) des ziehenden Spielers
    - Mögliche Werte: 1 bis 7
    - 0 ist kein möglicher Wert, da die erste Handkarte die Position 1 hat.

- **Y**: freie Position am eigenen Spielfeld, auf die die Kreatur gelegt werden soll
    - Mögliche Werte: 1 bis 7 (die Position muss außerdem frei sein!)
    - 0 ist kein möglicher Wert, da sich an dieser Position bereits der eigene Spieler befindet.

Die Kreaturen können beliebig auf das Spielfeld gelegt werden, es ist also nicht notwendig, zuerst die Positionen von 1 bis (X-1) mit Kreaturen zu füllen.

###### Aufgaben

- wird eine Karte ausgespielt, müssen die dahinterliegenden Karten nachrücken, sodass bei  **X** Karten auf der Hand immer genau die Nummern 1 bis X für die Karten genutzt werden.
- Kreaturen werden beim Ausspielen [beschworen](../README.md#Beschwörung), das heißt sie schlafen eine Runde. Das heißt sie können im Zug ihres Ausspielens (mit `set`) noch nicht für einen Angriff genutzt werden.

###### Fehler

Ist einer der Parameter außerhalb des vorgegebenen Wertebereichs, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Invalid command parameter!\n
```

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```

Sind beide Parameter innerhalb des vorgegebenen Wertebereichs und kann der Befehl nicht ausgeführt werden, weil z.B.

- die Position am Spielfeld belegt ist oder
- die Position auf der Hand keine Kreaturenkarte ist,

 soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Execution not possible!\n
```

#### cast [X]

Führt den [Zauber](SpellCardDescription.md) an der Position X auf der Hand des ziehenden Spielers aus.

```
cast X
```

###### Parameter

- **X**: Position der Zauberkarte auf der Hand (Handkarten) des ziehenden Spielers
    - Mögliche Werte: 1 bis 7

###### Fehler

Ist der Parameter außerhalb des vorgegebenen Wertebereichs, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Invalid command parameter!\n
```

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```

Ist der Parameter innerhalb des vorgegebenen Wertebereichs und kann der Befehl nicht ausgeführt werden, weil z.B.

- die Position auf der Hand keine Zauberkarte ist

 soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Execution not possible!\n
```

#### sacrifice [X]

Opfert die Karte an Position X auf der Hand des ziehenden Spielers UND erhöht seine Lebenspunkte +1. Man kann Kreaturen und Zauberkarten opfern. Kreaturenkarten werden auf den Friedhof gelegt; Zauberkarten verschwinden.

```
sacrifice X
```

###### Parameter

- **X**: Position der Karte auf der Hand (Handkarten) des ziehenden Spielers
    - Mögliche Werte: 1 bis 7

###### Fehler

Ist der Parameter außerhalb des vorgegebenen Wertebereichs soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Invalid command parameter!\n
```

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```

Ist der Parameter innerhalb des vorgegebenen Wertebereichs und kann der Befehl nicht ausgeführt werden, weil z.B.

- die Position auf der Hand leer ist (keine Karte),

 soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Execution not possible!\n
```



#### finish

```
finish
```

Beendet deinen eigenen Spielzug und signalisiert dem Gegner, wieder dran zu sein.


###### Fehler

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```



#### quit

```
quit
```

Der aktuelle Spieler gibt auf. Es folgt die Ausgabe:

```
[INFO] Game ended. Player X won!\n
```

Wobei **`X`** für den Namen des Gegners steht. Das Programm beendet mit Rückgabewert 0.


###### Fehler

Wird der Befehl mit zu vielen Parametern aufgerufen, soll folgende Fehlermeldung ausgegeben werden:

```
[INFO] Wrong parameter count!\n
```



### Spielende

Wenn ein Spieler weniger als einen Lebenspunkt hat, hat er das Spiel verloren. Es folgt die Ausgabe, welcher Spieler das Spiel gewonnen hat:

```
[INFO] Game ended. Player X won!\n
```

Wobei **`X`** für den Namen des Spielers steht. Das Programm beendet mit Rückgabewert 0.



## Bonus

2 Zusatzfeatures können als Bonuspunkte implementiert werden:

#### Traitor

`Traitor` ist ein zusätzlicher Zauberspruch. Details unter [SpellCardDescription](SpellCardDescription.md)

#### Speedy

Kreaturen können die Eigenschaft `speedy` haben, welche im [Config-File](Ass1_D2.md) mitgegeben wird (einfach ein zusätzliches Attribut das akzeptiert wird. Dieses Attribut muss dann bei allen Kreaturen im Config-File vorhanden sein). Wenn Kreaturen diese Eigenschaft besitzen, kann die Kreatur sofort nach dem Ausspielen angreifen (und angegriffen werden). Das bedeutet die [Beschwörungszeit](../README.md) fällt weg. 

Siehe [Bonus Config-File](../config/config08_bonus.json)



# Spezifikation

-  nur geforderte Ausgaben
-  Es **MUSS** jede Klasse im Oop-Namespace enthalten sein.

##  Erlaubte Bibliotheken

-  alle Bibliotheken der C++ Standard Library

## Abgabe

- siehe  [Assignment Description](Assignments.md)

