#ifndef HEXBINCHAREDITOR_H
#define HEXBINCHAREDITOR_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>

#define VERSION "1.0.2"
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800
#define SIDE_PANEL_WIDTH 150

// Hauptklasse für den Hex/Bin/Char-Editor
class HexBinCharEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit HexBinCharEditor(QWidget *parent = nullptr);

private slots:
    void updateTable(QTableWidgetItem *item); // Aktualisiert die Datei-Inhalte bei Änderungen
    void openFile();  // Öffnet den Datei-Dialog zum Laden einer Datei
    void saveFileDialog();  // Öffnet den Datei-Dialog zum Speichern

private:
    QTableWidget *tableWidget; // Tabelle für die Dateidaten
    QPushButton *loadButton; // Button zum Laden einer Datei
    QPushButton *saveButton; // Button zum Speichern einer Datei
    QLabel *statusLabel; // Statuszeile für Meldungen
    QByteArray fileData; // Speichert die Datei-Inhalte
    bool updatingTable; // Verhindert ungewollte Rekursionen

    void loadFile(const QString &filePath); // Lädt eine Datei in den Speicher
    void saveFile(const QString &filePath); // Speichert die Datei aus dem Speicher
    void updateView(); // Aktualisiert die Tabellendarstellung
};

#endif // HEXBINCHAREDITOR_H
