#include "ButtonList.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QApplication>
#include <QDebug>
ButtonList::ButtonList()
{

}

QList<Button> ButtonList::buttonList() const
{
    return mButtonList;
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
        QJsonObject buttonObject = buttonArray[buttonIndex].toObject();
        Button button;
        button.read(buttonObject);
        mButtonList.append(button);
    }
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

}

void ButtonList::save()
{
    QFile configFile("config.json");
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
    QFile configFile("config.json");
    if(!configFile.open(QIODevice::ReadOnly)){
        QTextStream(stdout) << "Could not load configuration, exiting.";
        qApp->exit();
    }
    QByteArray configData = configFile.readAll();
    QJsonDocument configDocument(QJsonDocument::fromJson(configData));
    read(configDocument.object());
    //qDebug() << configDocument.object();
}

int ButtonList::len()
{
    return mButtonList.length();
}



