#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <QResizeEvent>
#include <QWidget>

class Tile : public QWidget
{
    Q_OBJECT

public:
    enum Color { NotVisited = 0, Visited, Wall, Start, End, Path };
    Q_ENUM(Color)

    explicit Tile(int row, int col, QWidget *parent = nullptr);
    ~Tile();
    Color getColor() const;
    void setColor(const Color c);
    int m_col;
    int m_row;

public slots:
    void resizeSlot(int width, int height);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    static const QMap<Color, QString> colorToStringMap;
    QLabel *m_label = new QLabel(this);
    Color m_color;
};

#endif // TILE_H
