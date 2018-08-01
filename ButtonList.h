//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#ifndef BUTTON_LIST_H
#define BUTTON_LIST_H

#include <QList>
#include <Button.h>
#include <QPushButton>

class ButtonList
{
public:
    ButtonList();
    QList<Button> *buttonList();

    void add(Button &button);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void save();
    // Loads configuration from config.json file
    void load();
    int len();

    bool active(int index);
    void setActive(int index, bool status);

private:
    QList<Button> mButtonList;
    QList<bool> buttonsActive;

};

#endif // BUTTON_LIST_H
