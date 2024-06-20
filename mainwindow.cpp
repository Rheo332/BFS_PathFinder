#include "mainwindow.h"
#include "algorithms.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("background-color: #777777;");
    setMinimumSize(Config::windowWidth, Config::windowHeight);
    setupTiles();
    setupSideBar();
}

MainWindow::~MainWindow()
{
    delete resetButton;
    delete startButton;
}

void MainWindow::setupTiles()
{
    int fieldSize = Config::fieldSize;
    tileWidth = (Config::windowWidth / fieldSize - 100) / fieldSize;
    tileHeight = Config::windowHeight / fieldSize / fieldSize;

    for (int i = 0; i < fieldSize * fieldSize; ++i) {
        int y = i / fieldSize;
        int x = i % fieldSize;
        Tile *tile = new Tile(x, y, this);
        tile->setGeometry(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
        tiles[x][y] = tile;
        connect(this, &MainWindow::resizeSignal, tile, &Tile::resizeSlot);
    }

    tiles[1][1]->setColor(Tile::Start);
    tiles[fieldSize - 2][fieldSize - 2]->setColor(Tile::End);
}

void MainWindow::setupSideBar()
{
    resetButton = new QPushButton("Reset", this);
    resetButton->setGeometry(Config::windowWidth - 100, 0, 100, 30);
    resetButton->setStyleSheet(buttonStyle);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetTiles);

    startButton = new QPushButton("Start", this);
    startButton->setGeometry(Config::windowWidth - 100, 35, 100, 30);
    startButton->setStyleSheet(buttonStyle);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::start);
}

void MainWindow::resetTiles()
{
    for (int i = 0; i < Config::fieldSize; ++i) {
        for (int j = 0; j < Config::fieldSize; ++j) {
            if (tiles[i][j]->getColor() != Tile::End && tiles[i][j]->getColor() != Tile::Start) {
                tiles[i][j]->setColor(Tile::NotVisited);
            }
        }
    }
}

void MainWindow::start()
{
    Algorithms algo;
    algo.startSearching(tiles);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    tileWidth = (event->size().width() - 100) / Config::fieldSize;
    tileHeight = event->size().height() / Config::fieldSize;
    emit resizeSignal(tileWidth, tileHeight);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    mousePressed = true;

    int fieldWidth = tileWidth * Config::fieldSize;
    int fieldHeight = tileHeight * Config::fieldSize;

    if (event->pos().x() < fieldWidth && event->pos().y() < fieldHeight) {
        int tileX = event->pos().x() / tileWidth;
        int tileY = event->pos().y() / tileHeight;
        switch (tiles[tileX][tileY]->getColor()) {
        case Tile::NotVisited:
            paintMode = Tile::Wall;
            break;
        case Tile::Wall:
            paintMode = Tile::NotVisited;
            break;
        default:
            mousePressed = false;
            break;
        }
        if (mousePressed)
            tiles[tileX][tileY]->setColor(paintMode);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMainWindow::mouseReleaseEvent(event);
    mousePressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QMainWindow::mouseMoveEvent(event);

    if (!mousePressed)
        return;

    if (event->pos().x() < 0 || event->pos().y() < 0)
        return;

    int fieldWidth = tileWidth * Config::fieldSize;
    int fieldHeight = tileHeight * Config::fieldSize;

    if (event->pos().x() < fieldWidth && event->pos().y() < fieldHeight) {
        int tileX = event->pos().x() / tileWidth;
        int tileY = event->pos().y() / tileHeight;
        tiles[tileX][tileY]->setColor(paintMode);
    }
}
