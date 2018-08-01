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

    /// todo: get font size from json config
    int getFontSize();

private:
    QList<Button> mButtonList;
    QList<bool> buttonsActive;
    int mFontSize;

};

#endif // BUTTON_LIST_H
