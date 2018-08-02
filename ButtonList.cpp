//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#include "ButtonList.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QApplication>
#include <QDebug>
#include <QFile>

ButtonList::ButtonList()
{

}

QList<Button> *ButtonList::buttonList()
{
    return &mButtonList;
}

void ButtonList::add(Button &button)
{
    mButtonList.append(button);
}

void ButtonList::read(const QJsonObject &json)
{
    mButtonList.clear();
    QJsonArray buttonArray;
    buttonArray = json["Buttons"].toArray();
    for (int buttonIndex = 0; buttonIndex < buttonArray.size(); ++buttonIndex) {
        QJsonObject buttonObject = buttonArray[buttonIndex].toObject(); //take one button object out of json array
        Button button; //new button
        button.read(buttonObject); //read json to button config
        mButtonList.append(button); //append new button to list
    }
    mFontSize = json["Font size"].toInt();

}

void ButtonList::write(QJsonObject &json) const
{
    QJsonArray buttonArray;
    foreach(const Button button, mButtonList){
        QJsonObject buttonObject;
        button.write(buttonObject);
        buttonArray.append(buttonObject);
    }

    json["Buttons"] = buttonArray;
    json["Font size"] = mFontSize;

}

void ButtonList::save()
{
    QFile configFile("/opt/TouchRunner/config/config.json");
    if(!configFile.open(QIODevice::WriteOnly)){
        QTextStream(stdout) << "Could not save configuration, exiting.";
        qApp->exit();
    }

    QJsonObject configurationObject;
    write(configurationObject);
    QJsonDocument configurationDocument(configurationObject);
    configFile.write(configurationDocument.toJson());

}



void ButtonList::load()
{
    QFile configFile("/opt/TouchRunner/config/config.json");
    if(!configFile.open(QIODevice::ReadOnly)){
        QTextStream(stdout) << "Could not load configuration, exiting.";
        qApp->exit();
    }

    QByteArray configData = configFile.readAll();
    QJsonDocument configDocument(QJsonDocument::fromJson(configData));
    read(configDocument.object());

    for(int i = 0; i < ButtonList::len(); i++){
        buttonsActive.append(new bool);
        buttonsActive[i] = false;
    }
}

int ButtonList::len()
{
    return mButtonList.length();
}


bool ButtonList::active(int index)
{
    return buttonsActive[index];
}

bool ButtonList::locking(int index)
{
    return buttonList()->at(index).locking();
}

void ButtonList::setActive(int index, bool status)
{
    buttonsActive[index] = status;
}

int ButtonList::getFontSize()
{
    return mFontSize;
}
