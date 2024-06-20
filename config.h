#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
constexpr int fieldSize = 30;
constexpr int windowWidth = 700;
constexpr int windowHeight = 600;

#define buttonStyle \
    "QPushButton {" \
    "  background-color: #333333;" \
    "  border: 1px solid #555555;" \
    "  color: white;" \
    "  margin: 1px;" \
    "  padding: 0;" \
    "  border-radius: 0;" \
    "}" \
    "QPushButton:hover {" \
    "  background-color: #444444;" \
    "}" \
    "QPushButton:pressed {" \
    "  background-color: #222222;" \
    "}"
}

#endif // CONFIG_H
