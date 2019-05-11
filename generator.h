#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>

#include "board.h"

namespace Ui {
class Generator;
}

class Generator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = nullptr);
    ~Generator();


private:
    Ui::Generator *ui;
    QGraphicsScene scene;
    Board board;
};

#endif // GENERATOR_H
