# Spielfeld

Die Ausgabefunktion des Spielfeldes wird im [Framework](FrameworkDescription.md) von uns zur Verfügung gestellt, damit sich keine unnötigen Leerzeichen-Fehler oder ähnliche Gründe für Punkteabzüge einschleichen können.

Das Spielfeld kann mittels folgender Funktion ausgegeben werden:

```
Oop::Interface::out(const Player* current_player, const Player* opponent_player) 
```



## Karte

```
mm____MS     mm_____S     mm_____
|      |     |      |     |      |
ZAUBERER     GNOM         Florian
|  ==  |     |  zz  |     |  zz  |
|      |     |      |     |      |
x______x     DD____LL     DD____LL
```

Die Ausgabefunktion greift dabei auf folgende Attribute zu:

- `ZAUBERER` bzw. `GNOM`: name_

- `mm`: mana_cost_

- `DD`: damage_points_

- `LL`: current_life_points_

- Optional vorhanden oben rechts:

  - `M`  mana_drain_
  
  - `S`  shield_

  - `A`  speedy_ (Bonus Task)

- Optional vorhanden unter dem Namen:
  
  - `==` wenn `already_attacked_ == true`
  
    Kreatur hat in dieser Runde schon angegriffen
  
  - `zz` wenn`ready_to_fight_ == false`
  
    Karte wurde gerade ausgespielt und damit beschworen (Die Kreatur schläft noch bis zur nächsten Runde)





## Spielfeldausgabe

```
Katrin > state

==================================================================================

     ______     ______     ______     ______     ______                           
H   |      |   |      |   |      |   |      |   |      |                         H
A   |      |   |      |   |      |   |      |   |      |                         A
N   |      |   |      |   |      |   |      |   |      |                         N
D   |      |   |      |   |      |   |      |   |      |                         D
    |______|   |______|   |______|   |______|   |______|                          

============================= LP : 30 | MANA :  1/15 =============================

     ______S                                                                      
G   |      |                                                                     G
A   Bluthund                                                                     A
M   |      |                                                                     M
E   |      |                                                                     E
    04____05                                                                      

~~~~~~ 01 ~~~~~~~ 02 ~~~~~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~

                ______                           ______S               ______S    
G              |      |                         |      |              |      |   G
A              Elf                              Thomas                Miniwall   A
M              |  ==  |                         |      |              |  zz  |   M
E              |      |                         |      |              |      |   E
               03____04                         00____05              00____04    

============================= LP : 30 | MANA :  7/15 =============================

    08_____S   02_____    07_____    07_____                                      
H   |      |   |      |   |      |   |      |                                    H
A   Aleks      Dracula    Katrin     Bigfoot                                     A
N   |      |   |      |   |      |   |      |                                    N
D   |      |   |      |   |      |   |      |                                    D
    03____09   x______x   05____06   09____03                                     

==================================================================================

Katrin >
```



### Anmerkungen

- `Dracula` ist eine Zauberkarte und hat daher keine Angriffs- oder Lebenspunkte.
- Mit `Elf` wurde in dieser Runde bereits angegriffen.
- `Miniwall` wurde soeben ausgespielt und ist noch in der Beschwörungszeit.
- Da `Bluthund` ein Schild ist, muss diese Kreatur zuerst zerstört werden, bevor man den Gegner oder andere Kreaturen angreifen kann (in diesem Beispiel gibt es keine anderen gegnerischen Kreaturen).

