#ifndef OPENGMP_H
#define OPENGMP_H

#include <QMainWindow>

namespace Ui {
    class OpenGMP;
}

class OpenGMP : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenGMP(QWidget *parent = nullptr);
    ~OpenGMP();

private:
    Ui::OpenGMP *ui;
};

#endif // OPENGMP_H
