#include "hexbinchareditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

//Erstellt das GUI und verbindet Signale mit Slots
HexBinCharEditor::HexBinCharEditor(QWidget *parent) : QMainWindow(parent), tableWidget(new QTableWidget(this)), updatingTable(false) {
    // Setzt das Fensterlayout und die Titelzeile mit Versionsnummer
    setWindowTitle("HEX/BIN/CHAR Datei-Editor v" VERSION);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Layout für die linke Seite mit Buttons
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    // Erstellt die Buttons zum Öffnen und Speichern von Dateien
    loadButton = new QPushButton("Datei öffnen", this);
    saveButton = new QPushButton("Datei speichern", this);
    loadButton->setFixedWidth(SIDE_PANEL_WIDTH);
    saveButton->setFixedWidth(SIDE_PANEL_WIDTH);

    leftLayout->addWidget(loadButton);
    leftLayout->addWidget(saveButton);
    leftLayout->addStretch();

    // Erstellt die Tabelle zur Anzeige der Datei-Inhalte
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Hex" << "Binär" << "Char");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setVisible(false);

    // Fügt Layouts zum Hauptlayout hinzu
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(tableWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Erstellt die Statuszeile unten im Fenster
    statusLabel = new QLabel("Bereit", this);
    statusBar()->addWidget(statusLabel);

    // Verbindet die Buttons mit den entsprechenden Funktionen
    connect(tableWidget, &QTableWidget::itemChanged, this, &HexBinCharEditor::updateTable);
    connect(loadButton, &QPushButton::clicked, this, &HexBinCharEditor::openFile);
    connect(saveButton, &QPushButton::clicked, this, &HexBinCharEditor::saveFileDialog);
}

// Öffnet eine Datei über einen Datei-Dialog
void HexBinCharEditor::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Datei öffnen", "", "Alle Dateien (*.*)");
    if (!filePath.isEmpty()) {
        loadFile(filePath);
    }
}

// Öffnet einen Dialog zum Speichern der Datei
void HexBinCharEditor::saveFileDialog() {
    QString filePath = QFileDialog::getSaveFileName(this, "Datei speichern", "", "Alle Dateien (*.*)");
    if (!filePath.isEmpty()) {
        saveFile(filePath);
    }
}

// Lädt eine Datei und speichert die Inhalte in einem QByteArray
void HexBinCharEditor::loadFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Fehler", "Datei konnte nicht geöffnet werden!");
        return;
    }

    fileData = file.readAll();
    file.close();

    if (fileData.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Die Datei ist leer oder konnte nicht gelesen werden.");
        return;
    }

    updateView();
    statusLabel->setText("Datei geladen: " + filePath);
}

// Speichert die Datei aus dem Speicher
void HexBinCharEditor::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Fehler", "Datei konnte nicht gespeichert werden!");
        return;
    }

    file.write(fileData);
    file.close();
    statusLabel->setText("Datei gespeichert: " + filePath);
}

// Aktualisiert die Tabelle mit den geladenen Daten
void HexBinCharEditor::updateView() {
    updatingTable = true;
    tableWidget->clearContents();
    tableWidget->setRowCount(fileData.size());

    for (int i = 0; i < fileData.size(); ++i) {
        char byte = fileData.at(i);

        // Erstellt neue Tabellen-Items mit den entsprechenden Darstellungen
        QTableWidgetItem *hexItem = new QTableWidgetItem(QString::number((unsigned char)byte, 16).toUpper());
        QTableWidgetItem *binItem = new QTableWidgetItem(QString::number((unsigned char)byte, 2).rightJustified(8, '0'));
        QTableWidgetItem *charItem = new QTableWidgetItem(QChar(byte));

        // Setzt die Werte in die Tabelle
        tableWidget->setItem(i, 0, hexItem);
        tableWidget->setItem(i, 1, binItem);
        tableWidget->setItem(i, 2, charItem);
    }

    updatingTable = false;
}

// Verarbeitet Änderungen an Tabellenzellen und speichert die neuen Werte
void HexBinCharEditor::updateTable(QTableWidgetItem *item) {
    if (updatingTable) return;
    if (!item) return;

    int row = item->row();
    int column = item->column();

    if (row < 0 || row >= fileData.size()) return;

    bool ok;
    char newValue = 0;

    // Hexadezimal-Wert wird geändert
    if (column == 0) {
        newValue = static_cast<char>(item->text().toUInt(&ok, 16));
    }
    // Binär-Wert wird geändert
    else if (column == 1) {
        newValue = static_cast<char>(item->text().toUInt(&ok, 2));
    }
    // Zeichen-Wert wird geändert
    else if (column == 2) {
        if (!item->text().isEmpty()) {
            newValue = item->text().at(0).toLatin1();
            ok = true;
        } else {
            ok = false;
        }
    }

    if (ok) {
        fileData[row] = newValue;
        updateView();  // Tabelle neu laden
    } else {
        QMessageBox::warning(this, "Fehler", "Ungültiger Wert eingegeben!");
        updateView();  // Fehlerhafte Eingabe rückgängig machen
    }
}
