2. Softwarestruktur
Die Software ist modular aufgebaut, um eine klare Trennung der Verantwortlichkeiten zu gewähr-leisten und eine einfache Erweiterbarkeit zu ermöglichen.


2.1 Hauptkomponenten
Benutzeroberfläche (GUI): Das grafische Interface basiert auf Qt und stellt die bearbeiteten Da-teien in einer tabellarischen Ansicht dar. Es erlaubt das Laden, Editieren und Speichern von Dateien sowie die Umschaltung zwischen den verschiedenen Darstellungsmodi (Hex, Binär, Zeichen).
Dateiverwaltung: Verwaltet das Laden und Speichern von Dateien. Die Daten werden in einem QByteArray gespeichert und können von dort weiterverarbeitet werden.
Datenkonvertierung: Diese Komponente ist für die Umwandlung zwischen den Formaten verant-wortlich. Sie stellt sicher, dass die Daten korrekt in Hexadezimal-, Binär- und Zeichenform ange-zeigt und verändert werden können.
Speicherverwaltung: Änderungen, die vom Benutzer in der UI vorgenommen werden, werden validiert und zurück in das Speicherarray geschrieben. Fehlerhafte Eingaben werden erkannt und entsprechend behandelt.

2.2 Modulinteraktion
Die Software folgt einer klaren Interaktionsstruktur:
Dateieingabe: Der Benutzer wählt eine Datei aus, die in den Speicher geladen wird. Dies geschieht über die Dateiöffnungs-Funktion (openFile()), die den Dateiinhalt einliest und im QByteArray fileData speichert.
Datenumwandlung und Anzeige: Die geladene Datei wird in die drei unterstützten Formate um-gewandelt (Hex, Binär, Zeichen) und in einer Qt-Tabelle dargestellt. Die Funktion updateView() ist für die korrekte Anzeige der Daten verantwortlich.
Benutzereingaben und Bearbeitung: Der Benutzer kann die Werte in der Tabelle ändern. Die updateTable()-Funktion verarbeitet diese Änderungen und schreibt sie zurück in den Speicher (fileData).
Speichern der Datei: Nach erfolgten Änderungen kann die Datei mit der saveFile()-Funktion gespeichert werden. Die aktualisierten Werte aus dem Speicherarray werden in die Datei geschrie-ben.

3. Code-Dokumentation
Der Code ist objektorientiert strukturiert und in mehrere Klassen aufgeteilt, die jeweils spezifische Aufgaben erfüllen.


3.1 Hauptklasse
HexBinCharEditor (hexbinchareditor.h / hexbinchareditor.cpp)
Die zentrale Klasse für die Bearbeitung und Anzeige der Dateiinhalte. Sie erbt von QMainWindow und verwaltet die Hauptfunktionen des Editors.
Wichtige Attribute:
QTableWidget *tableWidget: Eine Tabelle zur Anzeige und Bearbeitung der Dateiinhalte in den drei Formaten.
QPushButton *loadButton, QPushButton *saveButton: Buttons für das Laden und Speichern von Dateien.
QLabel *statusLabel: Zeigt den aktuellen Status an (z.B. Datei geladen, gespeichert, Fehler).
QByteArray fileData: Speicherbereich für die eingelesenen Dateiinhalte.
bool updatingTable: Steuerung zur Vermeidung rekursiver Updates bei Änderungen.
Wichtige Methoden:
openFile(): Öffnet einen Datei-Dialog, um eine Datei zum Bearbeiten auszuwählen.
saveFileDialog(): Öffnet einen Speichern-Dialog, um Änderungen zu speichern.
loadFile(const QString &filePath): Liest eine Datei und speichert deren Inhalt in fileData.
saveFile(const QString &filePath): Speichert die aktuellen Daten aus fileData in eine Datei.
updateView(): Aktualisiert die Anzeige der Tabelle mit den geladenen Daten. Hier werden die he-xadezimale, binäre und zeichenweise Darstellung aktualisiert.
updateTable(QTableWidgetItem *item): Reagiert auf Änderungen durch den Benutzer und speichert die neuen Werte zurück in fileData. Enthält eine Validierung zur Vermeidung fehlerhaf-ter Eingaben.

3.2 Hauptfenster: 
MainWindow (mainwindow.h / mainwindow.cpp)
Verwaltet die Hauptbenutzeroberfläche und enthält die grundlegenden UI-Elemente.
Funktionen:
MainWindow(QWidget *parent = nullptr): Erstellt die UI-Elemente und initialisiert die Benut-zeroberfläche.
~MainWindow(): Sorgt für eine ordnungsgemäße Freigabe des UI-Objekts.

3.3 Programmstart: 
main.cpp
Die main()-Funktion ist der Einstiegspunkt des Programms und startet die Anwendung.
Ablauf:
Erstellt eine QApplication-Instanz, die das Event-Handling von Qt übernimmt.
Erstellt ein HexBinCharEditor-Objekt und zeigt das Hauptfenster an.
return app.exec(); startet die Qt-Event-Schleife, um Benutzerinteraktionen zu verarbeiten.
Durch diese Strukturierung wird eine modulare und erweiterbare Architektur gewährleistet.
