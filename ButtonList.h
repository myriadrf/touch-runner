#ifndef BUTTON_LIST_H
#define BUTTON_LIST_H

#include <QList>
#include <Button.h>

class ButtonList
{
public:
    ButtonList();
    QList<Button> *buttonList();

    void add(Button &button);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void save();
    void load();

    int len();

private:
    QList<Button> mButtonList;
};

#endif // BUTTON_LIST_H
