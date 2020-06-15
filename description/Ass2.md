# Nach Assignment 1

## Die möglichen Wege

Nach Assignment 1 haben Sie - genügend Punkte vorausgesetzt - die Wahl zwischen
 - dem Ausbesserungsbeispiel,
 - Assignment 2 (a.k.a. Aufbaubeispiel) und
 - dem Ende der KU mit den bisherigen Punkten von Assignment 1.

Voraussetzung für diese drei möglichen Wege sind:
 - für das **Ausbesserungsbeispiel** mindestens **20** erreichte Punkte bei Assignment 1.
 - für **Assignment 2** mindestens **40** erreichte Punkte bei Assignment 1.
 - für das Ende der KU mit positiver Beurteilung mindestens **50** erreichte Punkte bei Assignment 1.

Das heißt, im Fall von >=50 erreichten Punkten bei Assignment 1 ist das Ausbesserungsbeispiel/Assignment 2 optional.

Es können nicht *sowohl* Ausbesserungsbeispiel *als auch* Aufbaubeispiel gewählt werden.

Die Gruppen sollten, wenn möglich, gemeinsam als Team weiterarbeiten. Ist das nicht möglich (weil ein Gruppenmitglied weniger als die oben geforderten Punkte erreicht hat oder bereits mit den aktuellen Punkten zufrieden ist), so kann man auch getrennt weiterarbeiten. Es gibt aber keine neue Gruppenameldung bzw. Gruppenzusammenlegung.

Beispiel: 2 von 3 Gruppenmitgliedern haben (beispielsweise) 45 Punkte erreicht und dürfen daher mit Assignment 2 beginnen. Das 3. Mitglied hat 35 Punkte erreicht und muss daher Assignment 1 im Zuge des Ausbesserungsbeispiels verbessern. Natürlich ist es in diesem Beispiel auch möglich, dass die zwei Teammitglieder mit 45 Punkten auf Assignment 2 verzichten und stattdessen mit dem dritten Teammitglied gemeinsam die Ausbesserung machen.

## Ausbesserungsbeispiel

### Vorraussetzungen

mind. *20* erreichte Punkte bei Assignment 1 

### Beschreibung

Im Rahmen des Ausbesserungsbeispiels wird die Lösung für Assignment 1 ([D1](Ass1_D1.md), [D2](Ass1_D2.md), [D3](Ass1_D3.md)) überarbeitet. Hierfür haben Sie zwei weitere Wochen Zeit, um die im Abgabegespräch erläuterten Fehler von Assignment 1 zu korrigieren. Die hierbei erreichten Punkte **ersetzen** die bei Assignment 1 erreichten Punkte.

Es gilt dabei die selbe Aufgabenstellung für Assignment 1.

### Spezifikation

- Es **MUSS** jede Klasse im Oop-Namespace enthalten sein.

#### Erlaubte Bibliotheken

-  alle Bibliotheken der C++ Standard Library

#### Abgabe
 - 14. Juni um 23:59 (in Österreich gültige Zeit)
 - in diesem Git-Repository am Branch `ausbesserung` (der letzte Commit vor der Deadline wird bewertet)



## Assignment 2 (=Aufbaubeispiel)

### Vorraussetzungen

mind. *40* erreichte Punkte bei Assignment 1

### Beschreibung

Im Aufbaubeispiel wird Ihre aktuell existierende Lösung um einen Computerspieler erweitert. 

Sobald der Befehl `play` eingegeben wird, soll eine KI (künstliche Intelligenz) einspringen und die Eingabe für einen Spielzug übernehmen.
Hierzu ist eine einfache KI zu entwickeln, welche die Entscheidungen für Aktionen trifft. 
Die KI berechnet, welche Karte(n) ausgespielt werden soll(en), welche Karte(n) angegriffen werden soll(en), etc.

Es wird ohne Bonus-Task Karten gespielt.

#### Befehle

- Alle Befehle sind case-insensitive, das heißt Groß- und Kleinschreibung wird nicht beachtet.

##### play

```
play
```

Der Befehl `play` führt einen Zug des aktuellen Spielers aus. Dabei kann der Zug aus einer beliebigen Aneinanderreihung der bisher implementierten Commands (help, state, attack, set, cast, sacrifice, quit) bestehen.

Beachten Sie, dass der `play` Befehl den Zug **komplett** ausführt, das heißt von jeder aktuellen Lage bis zum Spielerwechsel oder Spielende (je nachdem welches Ereignis zuerst eintritt). Der von der KI ausgeführte Zug beendet also auch den aktuellen Zug mit `finish`, sofern der Zug nicht das Spiel selbst beendet (also der Spieler gewinnt oder verliert).

In anderen Worten: `play` erstellt eine Reihe von Befehlen, welche ausgeführt werden sollen. Diese beenden den aktuellen Zug - entweder weil der Spieler mit den Zügen gewinnt (oder verliert)
oder durch `finish`, wobei `finish` definitiv der letzte Befehl sein muss und nur einmal vorkommen darf. **Achtung:** Wenn ein Befehl zum Spielende führt, dürfen danach keine weiteren Befehle ausgegeben werden.

Jeder erfolgreich ausgeführte Befehl im Zuge des `play`-Befehls muss in folgender Form aufgelistet werden:

```
[INFO] Command: [ausgeführter Befehl]
```

Es werden **zuerst** alle Befehle (ohne irgendwelche Zwischenausgaben) aufgelistet und erst danach werden sie ausgeführt.
<mark>Edit: Es ist nun auch erlaubt, *einzelne* Befehle abwechselnd auszugeben und auszuführen. Beispiel: Ausgabe von Befehl 1, Ausführung von Befehl 1, Ausgabe von Befehl 2, Ausführung von Befehl 2, und so weiter... Das macht auch die Ausnahmeregelung für den `Relief`-Zauber (siehe unten) überflüssig.</mark>

**ACHTUNG**, es ist der KI **nicht** erlaubt, die Karten des eigenen und gegnerischen Abhebestapels auszelesen! Gleiches gilt für die gegnerischen Handkarten! (Das heißt, die KI darf nicht schummeln!)
Die KI darf allerdings die Größe von Abhebestapeln abfragen. Außerdem gibt es eine Sonderregelung für den Zauber `Relief` (siehe unten).

Der `play` Befehl darf nicht mehr als 3 Sekunden Berechnungszeit benötigen.

###### Beispiel

```
player1 > play
[INFO] Command: set 1 to 3
[INFO] Command: attack 0 with 1
[INFO] Command: finish
[INFO] Current player is player2

==================================================================================

     ______     ______     ______     ______     ______     ______                
H   |      |   |      |   |      |   |      |   |      |   |      |              H
A   |      |   |      |   |      |   |      |   |      |   |      |              A
N   |      |   |      |   |      |   |      |   |      |   |      |              N
D   |      |   |      |   |      |   |      |   |      |   |      |              D
    |______|   |______|   |______|   |______|   |______|   |______|               

============================= LP : 30 | MANA :  8/15 =============================

     ______                ______                                                 
G   |      |              |      |                                               G
A   David K               Bigfoot                                                A
M   |  ==  |              |  zz  |                                               M
E   |      |              |      |                                               E
    02____05              09____03                                                

~~~~~~ 01 ~~~~~~~ 02 ~~~~~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~

                                                                                  
G                                                                                G
A                                                                                A
M                                                                                M
E                                                                                E
                                                                                  

============================= LP : 27 | MANA : 15/15 =============================

    06_____S   13_____    06_____S   08_____    07_____    02_____    02_____     
H   |      |   |      |   |      |   |      |   |      |   |      |   |      |   H
A   Florian    Werwolf    Florian    David A    Katrin     Einhorn    Simone     A
N   |      |   |      |   |      |   |      |   |      |   |      |   |      |   N
D   |      |   |      |   |      |   |      |   |      |   |      |   |      |   D
    01____08   09____06   01____08   08____07   05____06   02____02   01____02    

==================================================================================
player2 >
```

###### Behandlung des Relief-Befehls
Beim Zauber `Relief` erhält der ziehende Spieler zusätzliche Karten.
Einem menschlichen Spieler ist es möglich, nach dem Erhalt zusätzlicher Karten seine Strategie für den restlichen Teil des Zuges zu überdenken.
Nach den obigen Regeln (alle Befehle eines Zuges müssen von vornherein bestimmt werden und Betrachten der Karten am Abhebestapel ist verboten),
könnte die KI die Information über die neuen Karten nicht nutzen.
Damit eine KI die gleichen Voraussetzungen hat wie ein menschlicher Spieler, gibt es für den Zauber `Relief` die folgende Ausnahmeregel.
Wenn `Relief` ausgespielt wird, werden die Befehle, die die KI bestimmt, in zwei Blöcken ausgeben.
Im ersten Block werden die ersten Befehle des Zuges ausgegeben, wobei der letzte Befehl der `Relief`-Zauber ist.
Dann werden diese Befehle ausgeführt.
Anschließend wird ein zweiter Block an Befehlen - mit der Information über die gezogenen Karten - berechnet und ausgegeben.
Dieser Befehlsblock beschreibt die Fortsetzung des Zuges.
Der zweite Befehlsblock wird ebenfalls zur Gänze ausgegeben und erst dann ausgeführt.
Wird der `Relief`-Befehl in einem Zug nicht ausgespielt, so kommt die eben beschriebene Ausnahmeregelung nicht zum Tragen
(das heißt, in diesem Fall gibt es nur einen Befehlsblock).


##### whoami

```
whoami
```

Der Befehl gibt den Namen eures Bots in der folgenden Zeile aus:

```
[INFO] Team: [NAME]
```

Dabei ist `[NAME]` ein Platzhalter und soll durch den eigenen Teamnamen ersetzt werden. Dieser Name darf beliebig gewählt werden (max. 20 ASCII oder UTF-8 kodierte Zeichen, Kreativität ist sehr erwünscht!) und erscheint später in der Highscore-Liste. Ihr Programm soll beim whoami-Befehl immer den gleichen Teamnamen ausgeben - egal welcher der beiden Spieler den Befehl ausführt.


###### Beispiel

```
player1 > whoami\n
[INFO] Team: SuperCardMaster\n
player1 > 
```



### Spezifikation

- Es **MUSS** jede Klasse im Oop-Namespace enthalten sein.
- Triviale Lösungen (z.B. jeder Zug der KI besteht lediglich aus dem Beenden des Zuges) resultieren in **0 Punkten für Assignment 2**.

#### Erlaubte Bibliotheken

-  alle Bibliotheken der C++ Standard Library

#### Abgabe
 - 21. Juni um 23:59 (in Österreich gültige Zeit)
 - in diesem Git-Repository am Branch `assignment2` (der letzte Commit vor der Deadline wird bewertet)
