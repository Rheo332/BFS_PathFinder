#include "tile.h"

Tile::Tile(int x, int y, QWidget *parent)
    : QWidget(parent)
    , m_col(x)
    , m_row(y)
    , m_color(Color::NotVisited)
{
    setColor(m_color);
}

Tile::~Tile()
{
    delete m_label;
}

Tile::Color Tile::getColor() const
{
    return m_color;
}

void Tile::setColor(const Color c)
{
    if (m_color == Color::Start || m_color == Color::End)
        return;

    m_label->setStyleSheet(colorToStringMap[c]);
    m_color = c;
}

void Tile::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_label->setFixedSize(event->size());
}

const QMap<Tile::Color, QString> Tile::colorToStringMap = {
    {Tile::NotVisited, "background-color: #AAAAAA;"},
    {Tile::Visited, "background-color: #b5a518;"},
    {Tile::Wall, "background-color: #444444;"},
    {Tile::Start, "background-color: #0000FF;"},
    {Tile::End, "background-color: #000000;"},
    {Tile::Path, "background-color: #00FF00;"},
};

void Tile::resizeSlot(int width, int height)
{
    setGeometry(m_col * width, m_row * height, width - 1, height - 1);
}
