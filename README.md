# Allgemeines zur KU

Die Konstruktionsübung OOP1 besteht aus 2 Assignments. Das erste Assignment ist in 3 Deliverables aufgeteilt.

Assignment 1:

- [Deliverable 1](description/Ass1_D1.md)
- [Deliverable 2](description/Ass1_D2.md)
- [Deliverable 3](description/Ass1_D3.md)

Assignment 2:

- in progress ...


# Allgemeine Spielbeschreibung


In Assignment 1 ist ein Spiel zu programmieren, welches hier allgemein beschrieben wird. Details zur Implementierung gibt es in den Angaben zu den drei Deliverables von Assignment 1 im Ordner description/

[Bewertung - Assignments - Deliverables - Zeitplan - Übersicht](description/Assignments.md)


## [Framework](description/FrameworkDescription.md)

Es wird ein Framework zur Verfügung gestellt, welches bereits Ein- und Ausgabefunktionen sowie ein Makefile enthält. Details in der  [Framework Description](description/FrameworkDescription.md).




# Spiel

Dieses Jahr soll ein Kartenspiel ähnlich wie [Hearthstone](https://playhearthstone.com) oder [Gwent](https://playgwent.com) erstellt werden. Zwei Kontrahenten können hierbei Karten ausspielen, um Kreaturen auf dem Spielfeld zu beschwören oder Zauber auszuführen. Die eigenen Kreaturen können von einem Spieler genutzt werden, um den Gegner direkt anzugreifen oder die gegnerischen Kreaturen zu zerstören.

Das Spiel wird gespielt, indem man eine Instanz des Spiels startet und abwechselnd beide Spieler steuern kann. Näheres unter [Spielablauf](#Spielablauf).


Jeder Spieler erhält zu Beginn des Spiels 30 Lebenspunkte und einen Kartenstapel, welcher durch ein [Config-File](description/Ass1_D2.md#configfile) definiert ist. Die Spieler sind abwechselnd am Zug. Zwei Züge (d.h. ein Zug von Spieler 1 gefolgt von einem Zug von Spieler 2) sind eine Runde.

### Tod

Falls ein Spieler weniger als einen Lebenspunkt hat, hat er das Spiel verloren. Kreaturen kommen bei weniger als einem Lebenspunkt auf einen eigenen Stapel, den [Friedhof](#Friedhof-Stapel).

## Datenstrukturen eines Spielers

### Abhebestapel

Der Abhebestapel stellt das gesamte Deck eines Spielers dar. Dieses wird durch das [Config-File](description/Ass1_D2.md#configfile) definiert und besteht aus Kreatur- und Zauberkarten. Zu Spielbeginn werden die ersten 3 Karten vom Abhebestapel abgehoben und auf die Hand genommen (Handkarten). Danach wird zu Beginn des Spielzugs immer eine Karte abgehoben (automatisch, es gibt keinen Command dafür).

### Handkarten

Jeder Spieler kann bis zu 7 Handkarten halten. Die Karten sind von 1 bis 7 durchnummeriert. Wenn eine Karte ausgespielt wird, rücken alle Karten mit einer höheren Nummer nach. Haben wir also **X** Karten auf der Hand, sind immer genau die Nummern 1 bis X  für die Karten genutzt. (Das ist für die Ausgabe des Spielfeldes wichtig.)

Handkarten können mit bestimmten Commands ausgespielt werden (siehe  [Deliverable 3](description/Ass1_D3.md)). Wird eine Handkarte ausgespielt, wird sie vom Handkarten-Stapel gelöscht. Handelt es sich um eine Kreatur, wird die Karte auf das eigene [Spielfeld](#Spielfeld) gelegt, handelt es sich um einen Zauber, wird der Zauber ausgeführt und die Karte wird zerstört (**ACHTUNG**: Zauberkarten werden nicht auf den [Friedhof](#Friedhof-Stapel)  gelegt!)

Es ist außerdem möglich, Handkarten zu opfern. Das Opfern einer Handkarte erhöht die Lebenspunkte des opfernden Spielers um 1. Für Näheres dazu siehe sacrifice-Command in [Deliverable 3](description/Ass1_D3.md).

### Friedhof-Stapel

Der Friedhof ist ein eigener Stapel, auf welchen zerstörte Kreaturen oben aufgelegt werden. Zauberkarten kommen **nicht** auf den Friedhof und werden stattdessen zerstört. Eine Kreatur kann auf den Friedhof gelangen, wenn sie zerstört wurde, oder wenn sie vom Spieler geopfert wurde (siehe sacrifice-Command in [Deliverable 3](description/Ass1_D3.md)).

### Spielfeld

Das Spielfeld besteht pro Spieler aus 7 Positionen für Kreaturen und einer Position für den Spieler selbst. Der Spieler besitzt Position 0 (als Identifikationsnummer für Angriffe), während die Kreaturen auf Positionen von 1 bis 7 ansprechbar sind. Beim set-Command (siehe [Deliverable 3](description/Ass1_D3.md)) muss angegeben werden, auf welche Position am Spielfeld die Kreatur gelegt werden soll.

Eine Printfunktion für das Spielfeld wird vom [Framework](description/FrameworkDescription.md) bereitgestellt (siehe [GameField](description/GameField.md)).

## Karten

Es gibt Kreatur- und Zauberkarten. Kreaturkarten werden auf dem [Spielfeld](#spielfeld) platziert, während Zauberkarten einmalig ausgespielt werden können und einen genau definiert Effekt bewirken.

### Zauber

Zauberkarten können einmalig ausgespielt werden und werden danach direkt zerstört. Für Näheres zu Zaubersprüchen siehe [Deliverable 1](description/Ass1_D1.md).

### Kreaturen & Angriff

Kreaturen haben einen Schadenswert und Lebenspunkte. Bei einem Angriff wird dem Ziel, welches entweder der Gegner direkt oder eine Kreatur ist, der Schadenswert von den Lebenspunkten abgezogen. Diese Lebenspunkte werden nicht wieder aufgefüllt und eine Kreatur stirbt, wenn die Lebenspunkte unter 1 fallen.

#### Beispiel: Zwei Angriffe von zwei Kreaturen Rex 4/5 auf Kreatur Troll 3/7
 - Nach 1. Angriff hat Kreatur Troll nur noch 3/7 (7 Lebenspunkte - 4 Schadenswert = 3 Lebenspunkte)
 - Nach 2. Angriff stirbt Kreatur Troll (3-4 < 0).
 - Beachte: Die angegriffene Kreatur fügt dem Angreifer keinen Schaden zu - Rex hat nach beiden Angriffen immer noch 5 Lebenspunkte (vorausgesetzt keine Kreatur hat ihn angegriffen).

Eine Kreatur kann innerhalb eines Zuges nur 1 Mal angreifen. Es können jedoch mehrere eigene Kreaturen im gleichen Zug einen Angriff ausführen. Dadurch kann eine gegnerische Kreatur (bzw. der Gegner selbst) in einem Zug mehrfach angegriffen werden.

#### Schild

Es gibt eine Eigenschaft `Schild` welche Kreaturen besitzen können. `Schild`-Kreaturen schützen den Spieler und andere Kreaturen, diese müssen somit zuerst eliminiert werden, bevor der Spieler oder Kreaturen ohne `Schild`-Eigenschaft angreifbar sind.

Passiert ein Angriff auf den Gegner oder eine Nicht-Schild-Kreatur des Gegners, obwohl noch eine Schild-Kreatur auf dem Spielfeld des Gegners liegt, wird eine [Fehlermeldung](description/ErrorDescription.md) ausgegeben.

#### Beschwörung

Gerade beschworene Kreaturen benötigen eine Runde, um sich zu festigen und können somit nicht direkt für einen Angriff genutzt werden; erst im nächsten Zug kann ein Angriff ausgeführt werden. Außerdem sind sie im folgenden Gegner-Zug noch nicht als Ziel auswählbar.

Die Beschwörung von [Schildern](#Schild) verläuft jedoch anders. `Schild` Kreaturen können zwar ebenfalls in der Runde der Beschwörung noch nicht angreifen, sind jedoch im folgenden Gegner-Zug bereits angreifbar und erfüllen somit schon ihre Funktion als `Schild`.

#### Mana Entzug / mana drain

Es gibt auch die Eigenschaft `Mana Entzug`, welche Kreaturen besitzen können. Wenn eine Kreatur mit `Mana Entzug` einen Spieler direkt angreift, verliert dieser all sein aktuell gesammeltes [`Mana`](#mana). Ansonsten verhält sich eine Kreatur mit `Mana Entzug` ident zu einer normalen Kreatur.

#### Beispiel

Werfen wir einen Blick auf eine Beispiel-Kreaturkarte:

```
Name:         "Link"
Manakosten:   7
Schaden:      9
Lebenspunkte: 3
Schild:       Ja
Mana Entzug:  Nein
```

Für Details zum Aufbau einer Kreaturkarte siehe [Deliverable 1](description/Ass1_D1.md).

Die Kreaturen werden über ein [Config-File](description/Ass1_D2.md#configfile) eingelesen.

## Spielablauf

### Spielstart

Zum Kompilieren und Ausführen kann das bereitgestellte Makefile verwendet werden. Möchte man nur das Spiel starten, so kann man `./game [Config-File]` aufrufen. Der Spielstart wird im [Deliverable 2](description/Ass1_D2.md) implementiert.

### Spielzug

Ein Spielzug beginnt mit dem [Abheben](#abheben) einer Karte und Erhalten von [Mana](#mana).

Beim Start eines Spieles heben beide Spieler 3 Karten ab.

Jetzt kann der Spieler seine Karten ausspielen, um Kreaturen auf seiner Spielfeldseite zu positionieren oder Zauber zu bewirken. Außerdem kann er seine bereits beschworenen Kreaturen nutzen, um die Kreaturen des Gegners oder den Gegner direkt anzugreifen.

### Mana

Jeder Spieler bekommt zu Beginn seines Zuges **X** Mana, wobei **X** im ersten Zug 1 ist und danach immer verdoppelt wird bis maximal 8. Ein Spieler behält nicht verbrauchtes Mana für den nächsten Zug.

Ein Spieler kann maximal 15 Mana besitzen; mehr erhaltenes Mana wird verworfen. Da Mana immer zu Beginn des Zuges vergeben wird, könnte es sich für einen Spieler als sinnvoll erweisen, am Ende eines Zuges nicht mehr als 7 Mana auf Vorrat zu halten, da sonst das Manapotenzial nicht maximal ausgeschöpft werden kann (7 Mana + 8 Mana zu Beginn der nächsten Runde = 15 Mana insgesamt).

#### Manabeispiel eines Spielers

| Runde | Mana erhalten | Manavorrat Zugbeginn | verbraucht in diesem Zug | Manavorrat Zugende |
| ----- | ------------- | -------------------- | ------------------------ | ------------------ |
| Start |               |                      |                          | 0                  |
| 0.    | 1             | 1                    | 0                        | 1                  |
| 1.    | 2             | 3                    | 0                        | 3                  |
| 2.    | 4             | 7                    | 3                        | 4                  |
| 3.    | 8             | 12                   | 5                        | 7                  |
| 4.    | 8             | 15                   | 3                        | 12                 |
| 5.    | 8             | 15 (wegen Maximum)   | 2                        | 13                 |
| 6.    | 8             | 15 (wegen Maximum)   | 13                       | 2                  |

Zauber- und Kreatur-Karten haben Manakosten im Bereich 0-15. <mark>Der Rundenzähler beginnt bei 0</mark>

### Abheben

Ist das Ziehen einer Karte aus irgendeinem Grund nicht möglich, zum Beispiel weil der [Abhebestapel](#Abhebestapel) leer ist oder die Hand bereits mit 7 Karten befüllt ist, so erhält der Spieler keine Karte und verliert stattdessen einen Lebenspunkt.


## Spielfeldausgabe

Das Spielfeld wird zu Beginn jedes Zuges ausgegeben. Außerdem kann man mit dem Befehl `state` das Spielfeld ausgeben lassen. Die Printfunktion für die Ausgabe des Spielfelds wird vom [Framework](description/FrameworkDescription.md)  bereitgestellt.

Eine Erklärung und Darstellung des Spielfeldes ist unter [GameField](description/GameField.md) zu finden.


## Fehlermeldungen

Details zu den [Fehlermeldungen](description/ErrorDescription.md)

## Bonuspunkte

Details unter Bonus im [Deliverable 3](description/Ass1_D3.md)

## Beispielausgabe

Ein spektakulärer Wettkampf unter [Beispielausgabe](description/GameplayExample.md)

## GUI

Infos für die GUI unter [GUI](description/GUI.md)