//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS


#ifndef BUTTON_INFO_H
#define BUTTON_INFO_H



#include <QJsonObject>
#include <QString>
#include <QVector>

class Button
{
public:
    Button(QString defaultName);
    Button();

    QString name() const;
    QString startCommand() const;
    QString stopCommand() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;


private:
    QString mName = "default button name";
    QString mStartCommand = "default button start command";
    QString mStopCommand = "default button stop command";
    bool mActive;

};

#endif // BUTTON_INFO_H
