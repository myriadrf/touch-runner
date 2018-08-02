//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#include "Button.h"

Button::Button(QString defaultName)
{
    mName = defaultName;
    mActive = false;
    mLocking = true;
}

Button::Button()
{
    mActive = false;
}

QString Button::name() const
{
    return mName;
}

bool Button::locking() const
{
    return mLocking;
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
    mLocking = json["locking"].toBool();
    mStartCommand = json["startCommand"].toString();
    mStopCommand = json["stopCommand"].toString();
}

void Button::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["locking"] = mLocking;
    json["startCommand"] = mStartCommand;
    json["stopCommand"] = mStopCommand;
}
