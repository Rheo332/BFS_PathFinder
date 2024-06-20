#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include "tile.h"

#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QResizeEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void resetTiles();
    void start();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void resizeSignal(int width, int height);

private:
    void setupTiles();
    void setupSideBar();

    Tile *tiles[Config::fieldSize][Config::fieldSize];
    QPushButton *resetButton;
    QPushButton *startButton;
    Tile::Color paintMode;
    bool mousePressed;
    int tileWidth = 0;
    int tileHeight = 0;
};
#endif // MAINWINDOW_H
