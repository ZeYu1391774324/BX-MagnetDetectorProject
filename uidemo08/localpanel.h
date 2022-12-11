#ifndef LOCALPANEL_H
#define LOCALPANEL_H

#include <QWidget>

namespace Ui {
class LocalPanel;
}

class LocalPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LocalPanel(QWidget *parent = nullptr);
    ~LocalPanel();

private:
    Ui::LocalPanel *ui;
};

#endif // LOCALPANEL_H
