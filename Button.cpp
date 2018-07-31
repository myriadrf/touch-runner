#include "Button.h"

Button::Button(QString defaultName)
{
    mName = defaultName;
}

Button::Button()
{

}

QString Button::name() const
{
    return mName;
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
