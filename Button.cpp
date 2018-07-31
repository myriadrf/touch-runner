#include "Button.h"

Button::Button(QString defaultName)
{
    mName = defaultName;
    mActive = false;
}

Button::Button()
{
    mActive = false;
}

QString Button::name() const
{
    return mName;
}

QString Button::startCommand() const
{
    return mStartCommand;
}

QString Button::stopCommand() const
{
    return mStopCommand;

}


void Button::read(const QJsonObject &json)
{
    mName = json["name"].toString();
    mStartCommand = json["startCommand"].toString();
    mStopCommand = json["stopCommand"].toString();

}

void Button::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["startCommand"] = mStartCommand;
    json["stopCommand"] = mStopCommand;
}
