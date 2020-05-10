# Verwendung der GUI

## Java

Um die GUI zu verwenden wird ein Java Runtime Enviroment benötigt.

Um dieses zu installieren müssen für Debian/Ubuntu basierte Systeme folgende Befehle ausgeführt werden:

```
sudo apt update
sudo apt upgrade
sudo apt install openjdk-11-jre
```

sudo passwort für die VM: `12345678`

## Ausführen der GUI

Zum Starten der GUI muss folgender Befehl in ein Terminal eingegeben werden:
```
java -jar OOPStoneGUI/OOPStoneGUI.jar ./game config/config01.json
```

Hier steht `OOPStoneGUI/OOPStoneGUI.jar` für den Speicherort des .jar Files `./game` für die executable des Spiels und `config/config01.json` für das config File das verwendet werden sollte. 
Die Pfadangaben müssen relativ zum aktuellen Pfad des Terminals sein. Der Befehl oben ist also gültig wenn ein Terminal im root des Projektordners geöffnet wird.

## Platformen

Die GUI sollte an sich auf Linux, MacOS und Windows funktionieren. Jedoch wurde Sie nur auf Linux und MacOS getestet. 

Für die Windows Subsystem for Linux Nutzer Ihr müsst zuerst einstellen dass grafische Programme ausgeführt werden können. 

[Link zu einem Tutorial dazu](https://virtualizationreview.com/articles/2017/02/08/graphical-programs-on-windows-subsystem-on-linux.aspx)
