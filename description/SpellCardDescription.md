# SpellCard
### HEALER

- Kosten: 5 Mana
`HEALER` versorgt alle Kreaturen auf dem Spielfeld des ziehenden Spielers mit +1 Lebenspunkt. Die maximale Anzahl von 9 Lebenspunkten darf dabei jedoch nicht überschritten werden. Hat eine Kreatur bereits 9 Lebenspunkte, bleiben die Lebenspunkte bei 9.

### RELIEF

- Kosten: 3 Mana

Spielt ein Spieler die Zauberkarte ``RELIEF`` aus, zieht er 3 Karten von seinem Abhebestapel. Sind nicht genügend Karten am Abhebestapel, kostet den ziehenden Spieler jede Karte, die er vergeblich versucht abzuheben, einen Lebenspunkt.

Hat der ziehende Spieler also z.B. nur noch eine Karte am Abhebestapel, erhält er diese Karte auf die Hand und verliert 2 Lebenspunkte. Hat er keine Karte mehr am Abhebestapel, verliert er 3 Lebenspunkte.

Wurde die maximale Anzahl an Handkarten (7) erreicht, kann man keine weitere Karte auf die Hand nehmen. Für jede Karte, die man vergeblich versucht, auf die Hand zu nehmen, verliert man einen Lebenspunkt (bei 7 Handkarten vor dem Ausspielen von `Relief` also -2 Lebenspunkte).

##### Beispiel

- Handkartenanzahl: 7
- Abhebestapelgröße: 2
- Relief wird gespielt, daher nur noch 6 Handkarten.
  - 1. Karte kann ich abheben und auf die Hand nehmen. Nur noch 1 Karte am Abhebestapel
  - 2. Karte könnte ich zwar abheben, jedoch nicht auf die Hand nehmen, weil ich bereits 7 Handkarten habe --> minus 1 Lebenspunkt und die Karte bleibt auf dem Abhebestapel
  - 3. Karte gleich wie bei der 2. Karte --> minus 1 Lebenspunkt und die Karte bleibt auf dem Abhebestapel
- Ich verliere bei diesem Beispiel also 2 Lebenspunkte und habe noch eine Karte auf dem Abhebestapel.



### REBIRTH

- Kosten: 5 Mana

`REBIRTH` belebt die **oberste** Kreatur am eigenen Friedhof wieder und legt sie zurück ins eigene Spielfeld. Ist der Friedhof des ziehenden Spielers leer oder die Spielfeldhälfte des ziehenden Spielers voll mit Kreaturen, wird keine Kreatur wiederbelebt. Die Karte gilt dennoch als ausgespielt und folgende Fehlermeldung soll ausgegeben werden:

```
[INFO] Rebirth unsuccessful\n
```

Die beschworene Kreatur landet auf deiner Spielfeldhälfte auf der Position mit der niedrigsten Nummer und hat wieder dieselben Eigenschaften, als wäre die Karte frisch von der Hand gespielt worden (volle Lebenspunkte, Angriffspunkte, ...). Die wiederbelebte Kreatur darf in dieser Runde noch nicht angreifen und nicht angegriffen werden ([Beschwörungszeit](../README.md)), außer die Kreatur hat die speedy-Eigenschaft (speedy-Eigenschaft ist ein Bonustask).



### DRACULA

- Kosten: 2 Mana

`DRACULA`  zieht dem Gegner 2 Lebenspunkte ab und gibt dem ziehenden Spieler 2 Lebenspunkte. Die Lebenspunkte dürfen auch über die Startlebenspunkte von 30 ansteigen. Hat der Gegner nach dem Ausspielen von `DRACULA` weniger als einen Lebenspunkt, so hat der ziehende Spieler gewonnen.

##### Beispiel

- Du: 24 Lebenspunkte
- Gegner: 15 Lebenspunkte
- `DRACULA` wird gespielt
  - Du hast nun 26 LP und
  - der Gegner hat 13 LP





## Bonus

Es gibt 2 Bonusaufgaben. [Traitor](#TRAITOR) und Speedy (unter [Ass1_D3.md](Ass1_D3.md))

### TRAITOR

- Kosten: 9 Mana

Als Bonustask kann ein zusätzlicher Zauberspruch `TRAITOR` implementiert werden.

Mit `TRAITOR` kann man eine Kreatur auf dem Spielfeld des Gegners unter Kontrolle bringen und aufs eigene Spielfeld legen. Die Eigenschaften der Kreatur sollen dabei unverändert bleiben (Schild, Beschwörungszeit, Mana Entzug, ..).

Hat man für diesen Zauber genügend Mana, soll folgende Meldung erscheinen:

```
Please enter the target creature: 
```

Nach Eingabe der Zielkreatur am gegnerischen Spielfeld soll dann diese Meldungen erscheinen:

```
Please enter where you would like to set the creature: 
```

 **Achtung: Leerzeichen nach dem Doppelpunkt  bei beiden Abfragen!**

Sind beide Werte gültig, wird die Karte ausgespielt und ausgeführt.

#### Fehlermeldungen

Tritt ein Fehler auf, so gilt die Karte als nicht ausgespielt. Sie ist also weiterhin auf der Hand und man hat keine Mana dafür verwendet.

Sobald ein Fehler erkannt wird, soll folgende Fehlermeldung ausgegeben werden

```
[INFO] Execution not possible!
```

**Mögliche Fehler:**

- Kein Integer-Wert oder außerhalb des Ranges (hier wird von `std::stoi` eine Exception geworfen)
  - sobald diese Exception geworfen wird erscheint sofort `[INFO] Execution not possible!`
  - bei allen anderen Fehlern werden zuerst immer beide Abfragen ausgegeben und danach überprüft
- außerhalb des Zahlenbereichs für Spielfelder 1-7
- keine Kreatur an dieser Stelle am Spielfeld des Gegners
- Platz am eigenen Spielfeld ist belegt



#### Beispiele

Handkarte 3 ist die Zauberkarte `TRAITOR`

- Alles ok

```
playername > cast 3
Please enter the target creature: 4
Please enter where you would like to set the creature: 2
playername > 
```



- Gegner besitzt keine Kreatur auf Position 4

```
playername > cast 3
Please enter the target creature: 4
Please enter where you would like to set the creature: 2
[INFO] Execution not possible!
playername > 
```



- Am eigenen Spielfeld auf Position 2 liegt bereits eine Kreatur 

```
playername > cast 3
Please enter the target creature: 4
Please enter where you would like to set the creature: 2
[INFO] Execution not possible!
playername > 
```

- Zahl ist außerhalb des Zahlenbereichs für Spielfelder

```
playername > cast 3
Please enter the target creature: 0
Please enter where you would like to set the creature: 2
[INFO] Execution not possible!
playername > 
```

- Zahl ist "ouf of range" von Integer (std::out_of_range Exception)

```
playername > cast 3
Please enter the target creature: 98519587139857875897097987598275981375817508175810571035
[INFO] Execution not possible!
playername > 
```



- Zahl ist kein Integer (std::invalid_argument Exception)

```
playername > cast 3
Please enter the target creature: a
[INFO] Execution not possible!
playername > 
```

