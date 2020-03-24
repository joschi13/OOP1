# Assignment 1 - Deliverable 1

Im Deliverable 1 werden die notwendigen Klassen erstellt, um das Spiel spielen zu können.

Die allgemeine Spielbeschreibung ist unter [README.md](../README.md) nachzulesen.



<mark>**! Es MUSS jede Klasse im Oop-Namespace enthalten sein !**</mark>



**! Die zur Verfügung gestellte Printfunktion erfordert, dass zumindest alle Getter-Methoden das Objekt nicht verändern (const) !**



## Klasse Game

Die Klasse `Game` lädt das Config-File, startet, verwaltet und beendet das Spiel.

### Attribute

- `io_`
  - Eine Referenz auf die Instanz des verwendeten Interfaces als Oop::Interface&.

### Konstruktoren

- `Game(Oop::Interface &io)`
  - setzt das Attribut
    - `io_` auf `io`

### Methoden

- `loadConfig(std::string config_file)`

    - config_file gibt den Pfad zum Config-File an

    - Liest die Konfigurationsdatei und überprüft, ob sie gültig ist

    - Rückgabewert: 

        - Config-File ist gültig: true
        - Config-File ist ungültig oder wurde nicht gefunden: false

    - Wird das Config-File nicht gefunden oder ist das Config-File ungültig, soll folgende Fehlermeldung innerhalb der Funktion (über das Interface) ausgegeben werden

        ```
        [ERROR] Invalid config file!\n
        ```

- `run()`

    - startet das Spiel und lässt es laufen, bis das Spiel zu Ende ist, oder es durch `quit` abgebrochen wird
    - kein Rückgabewert

## Klasse Player

`Player` beschreibt einen Spieler des Spiels, dessen Lebenspunkte, Mana und Karten.

### Attribute

- `name_`
    - Name des Spielers als String

- `life_points_`
    - Lebenspunkte des Spielers als Integer
    - zu Beginn des Spieles haben beide Spieler 30 Lebenspunkte

- `mana_points_`
    - aktuelle Mana des Spielers als Integer
    - Zu Beginn des Spieles haben beide Spieler 0 Mana

- `game_field_`
    - Das Spielfeld des Spielers
    - Ein Spieler kann max. 7 Kreaturen am Spielfeld besitzen (zu jeder Zeit im Spiel)
    - Ein Array aus [Kreaturkarten](#Klasse CreatureCard)-Pointern mit einer fixen Größe von 7. 

- `pick_up_stack_`
    - Der Abhebestapel des Spielers
    - Ein Vector aus [Karten](#Klasse Card)-Pointern  (Kreaturen oder Zaubersprüchen)

- `hand_`
    - Die Handkarten des Spielers
    - Ein Spieler kann max. 7 Handkarten besitzen (zu jeder Zeit im Spiel)
    - Ein Vector aus [Karten](#Klasse Card)-Pointern (Kreaturen oder Zaubersprüche)

- `graveyard_`
    - Der Friedhof des Spielers mit beliebiger Größe
    - Ein Vector aus [Kreaturkarten](#Klasse CreatureCard)-Pointern (da Zaubersprüche beim Spielen zerstört werden und nicht auf den Friedhof gelegt werden)

Wichtig ist, dass `game_field_`, `pick_up_stack_`, `hand_` und `graveyard_` genau die vorgegebenen Datenstrukturen sind, ansonsten funktioniert die zur Verfügung gestellte Spielfeldausgabe nicht wie gewünscht. Das wiederum hat zur Folge, dass Test Cases nicht bestanden werden!

### Konstruktoren

- `Player(std::string name)`
    - setzt Attribute
        - `name_` auf `name`
        - `life_points_` auf `30`
        - `mana_points_` auf `0`
    - führt etwaige notwendige Schritte für die Datenstrukturen `game_field_`, `pick_up_stack_`, `hand_` und `graveyard_` durch (abhängig von der Datenstruktur)

- Player()
    - setzt Attribute
        - `name_` auf `""`
        - `life_points_` auf `30`
        - `mana_points_` auf `0`
    - führt etwaige notwendige Schritte für die Datenstrukturen `game_field_`, `pick_up_stack_`, `hand_` und `graveyard_` durch (abhängig von der Datenstruktur)

### Methoden

- `getName()`
    - Rückgabewert: String
    - gibt das Attribut `name_` zurück
- `getLifePoints()`
    - Rückgabewert: Integer
    - gibt das Attribut `life_points_` zurück
- `addLifePoints(int points)`
    - Rückgabewert: void
    - erhöht das Attribut `life_points_` um points
    - Es gibt keine Obergrenze für Lebenspunkte
- `getManaPoints()`
    - Rückgabewert: Integer
    - gibt das Attribut `mana_points_` zurück
- `addMana(int mana)`
    - Rückgabewert: void
    - erhöht das Attribut `mana_points_` um mana
    - Es ist nicht möglich, mehr als 15 Mana zu haben
- `reduceMana(int mana)`
    - Rückgabewert: void
    - verringert das Attribut `mana_points_` um mana
    - Es ist nicht möglich, weniger als 0 Mana zu haben
- `getHandCards()`
    - Rückgabewert: const std::vector<Card*>
    - gibt das Attribut `hand_` zurück
- `getHandSize()`
    - Rückgabewert: int
    - gibt die Länge des Vectors `hand_` zurück
- `getGameField()`
	- <mark>Rückgabewert: const CreatureCard* const*</mark>
	- <mark>gibt das Attribut `game_field_` als const CreatureCard* const* zurück</mark>


## Klasse Card

Die Klasse `Card` repräsentiert eine Karte. Sie ist die Basisklasse der beiden abgeleiteten Klassen CreatureCard und SpellCard.

Es gibt also 2 Arten von Karten - Kreaturkarten und Zauberkarten. Jede Karte ist entweder eine Kreaturkarte oder eine Zauberkarte.

Innerhalb der Klasse soll folgendes enum verwendet werden:

```
enum CardType {CREATURE, SPELL};
```

### Attribute

- `name_`
    
    - Name der Karte aus dem Configfile als String mit max. 8 Zeichen
- `mana_cost_`
    - Manakosten der Karte als Integer

    - Wertebereich von 1 bis einschließlich 15

    - <mark>Dieses Attribut kann nach der Initialisierung geändert werden </mark> 

      ​		<mark>Änderung: 22.03. David K</mark>
- `type_`
    
    - Der Typ der Karte als CardType

### Konstruktoren

- `Card(std::string name, int mana_cost, CardType type)`
    - setzt die Attribute
        - `name_` auf `name`
        - `mana_cost_` auf `mana_cost`
        - `type_` auf `type`

### Methoden

- `getName()`
    - Rückgabewert: String
    - gibt das Attribut `name_` zurück
- `getType()`
    - Rückgabewert: CardType
    - gibt das Attribut `type_` zurück
- `getManaCost()`
    - Rückgabewert: int
    - gibt das Attribut `mana_cost_` zurück



## Klasse CreatureCard

`CreatureCard` ist eine Kreaturkarte und abgeleitet von `Card`. Kreaturkarten werden durch das [Config-File](#Ass1_D2.md) definiert (Deliverable 2).

### Attribute

- `damage_points_`
    - Schadenspunkte, die diese Kreatur bei Angriff zufügt
    - Integer mit Wertebereich von 0 bis einschließlich 9
    - Dieses Attribut soll nach Initialisierung nicht mehr geändert werden können
- `life_points_`
    - Gesamte Lebenspunkte der Kreatur beim Ausspielen der Karte
    - Integer mit Wertebereich von 1 bis einschließlich 9
    - Dieses Attribut soll nach Initialisierung nicht mehr geändert werden können
- `current_life_points_`
    - Aktuelle Lebenspunkte der Kreatur (bei jedem Angriff auf diese Kreatur verringert sich dieser Wert)
    - Sind current_life_points_ == 0, stirbt die Kreatur und wird auf den Friedhof gelegt
    - Integer mit Wertebereich von 0 bis einschließlich 9
- `shield_`
    - Gibt an, ob eine Kreatur die Schild-Eigenschaft besitzt
    - Boolean (TRUE oder FALSE)
    - Dieses Attribut soll nach Initialisierung nicht mehr geändert werden können
- `mana_drain_`
    - Gibt an, ob eine Kreatur bei Angriff den Manavorrat des Gegners leert
    - Nur wenn eine Kreatur mit Mana Drain den Gegner direkt angreift und dieser keine Schild-Kreatur besitzt, verliert der Gegner seinen gesamten Manavorrat
    - Boolean (TRUE oder FALSE)
- `ready_to_fight_`
    - Jede Kreatur hat eine Beschwörungszeit beim Ausspielen der Karte. Sie kann nicht gespielt werden und sofort angreifen. Erst in der nächsten Runde darf der Spieler mit dieser Karte angreifen (Attribut wird dann TRUE).
    - Boolean (TRUE oder FALSE)
- `already_attacked_`
    - Jede Kreatur darf nur einmal pro Runde angreifen. Wenn die Kreatur angreift, wird dieses Attribut auf TRUE gesetzt und erst am Anfang der nächste Runde wird es wieder auf FALSE gesetzt.
    - Boolean (TRUE oder FALSE)
- `speedy_`
    - **Funktionalität nur mit [Bonustask](Ass1_D3.md#bonus)**
      - solange der Bonustask nicht implementiert wurde, muss `speedy_` auf FALSE gesetzt werden
    - Dieses Attribut ermöglicht Kreaturen, schon in der Runde des Ausspielens anzugreifen.
    - Boolean (TRUE oder FALSE)

### Konstruktoren

- `CreatureCard(std::string name, int mana_cost, int damage_points, int life_points, bool shield, bool mana_drain, bool speedy)`
    - setzt die Attribute
        - `name_` (von Card) auf `name`
        - `mana_cost_` (von Card) auf `mana_cost`
        - `type_` (von Card) auf `CREATURE`
        - `damage_points_` auf `damage_points`
        - `life_points_` auf `life_points`
        - `shield_` auf `shield`
        - `mana_drain_` auf `mana_drain`
        - `speedy_` auf `speedy`
        - `ready_to_fight_` auf `false`
        - `already_attacked_` auf `false`

### Methoden

- `getLifePoints()`
    - Rückgabewert: int
    - gibt das Attribut `life_points_` zurück
- `getDamagePoints()`
    - Rückgabewert: int
    - gibt das Attribut `damage_points_` zurück
- `getManaDrain()`
    - Rückgabewert: bool
    - gibt das Attribut `mana_drain_` zurück
- `getShield()`
    - Rückgabewert: bool
    - gibt das Attribut `shield_` zurück
- `getCurrentLifePoints()`
    - Rückgabewert: int
    - gibt das Attribut `current_life_points_` zurück
- `getReadyToFight()`
    - Rückgabewert: bool
    - gibt das Attribut `ready_to_fight_` zurück
- `getAlreadyAttacked()`
    - Rückgabewert: bool
    - gibt das Attribut `already_attacked_` zurück
- `getSpeedy()`
    - Rückgabewert: bool
    - gibt das Attribut `speedy_` zurück (wird nur für Bonustask benötigt)


## Klasse SpellCard

`SpellCard` ist eine Zauberkarte und abgeleitet von `Card`. Zauberkarten werden nach dem Ausführen zerstört und landen nicht auf dem Friedhof.

Im Gegensatz zu Kreaturkarten, welche beliebige Namen und Kombinationen von Werten haben können, sind die Zauberkarten durch die Übungsangabe definiert. Im [Config-File](Ass1_D2.md) wird nur der Name angegeben.

Es gibt 4 Zauberkarten; Der Name in den eckigen Klammern gibt an, wie die entsprechende Karte im [Config-File](Ass1_D2.md) heißt.

- [`HEALER`] Heile alle deine Kreaturen +1 Lebenspunkt (bis zu 9 Lebenspunkte). 5 Manakosten
- [`RELIEF`] Ziehe 3 Karten vom Abhebestapel. 3 Manakosten
- [`REBIRTH`] Belebe die zuletzt gestorbene Kreatur vom Friedhof wieder. 5 Manakosten
- [`DRACULA`] -2 Lebenspunkte für den Gegner, +2 Lebenspunkte für den ausspielenden Spieler. 2 Manakosten

Die Art der Zauberkarte ist als **enum** zu implementieren.
```
enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA};
```

Nähere Beschreibungen zu den Zauberkarten sind unter [SpellCardDescription](SpellCardDescription.md) zu finden.

**Bonus:** Unter [SpellCardDescription](SpellCardDescription.md) ist ein weiterer Zauberspruch `TRAITOR` definiert, der für Bonuspunkte implementiert werden kann.

### Attribute

- `spell_type_`
    - Der Typ der Zauberkarte als SpellType

### Konstruktoren

- `SpellCard(SpellType type)`
    - setzt die Attribute
        - `name_` (von Card) auf den Namen des Zauberspruchs (zB Oop::Interface::STRING_HEALER)
        - `mana_cost_` (von Card) auf die Manakosten des Zauberspruchs
        - `type_` (von Card) auf `SPELL`
        - `spell_type_` auf `type`

### Methoden

- `action(Game& game)`
    - Rückgabewert: bool
        - TRUE wenn der Zauberspruch ausgeführt werden kann
        - FALSE, wenn der Zauberspruch nicht ausgeführt werden kann
    - überprüft den `spell_type_` des Zauberspruchs und führt den Zauberspruch aus.
    - Die Implementierung der Zaubersprüche erfolgt in Assignment 1 Deliverable 3. 
    Bis dahin ist es ausreichend, den Rückgabewert auf FALSE zu setzen.





#  Spezifikation

-  nur geforderte Ausgaben
-  Es **MUSS** jede Klasse im Oop-Namespace enthalten sein.

##  Erlaubte Bibliotheken

-  alle Bibliotheken der C++ Standard Library

## Abgabe

- siehe [Assignment Description](Assignments.md)