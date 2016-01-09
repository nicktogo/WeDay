#include "Rss/headers/channel.h"

Channel::Channel()
{
}

QString Channel::getLink() const
{
    return link;
}

void Channel::setLink(const QString &value)
{
    link = value;
}

int Channel::getId() const
{
    return id;
}

void Channel::setId(int value)
{
    id = value;
}

QString Channel::getTitle() const
{
    return title;
}

void Channel::setTitle(const QString &value)
{
    title = value;
}

QString Channel::getDescription() const
{
    return description;
}

void Channel::setDescription(const QString &value)
{
    description = value;
}

QString Channel::getCopyright() const
{
    return copyright;
}

void Channel::setCopyright(const QString &value)
{
    copyright = value;
}

QString Channel::getIconUrl() const
{
    return iconUrl;
}

void Channel::setIconUrl(const QString &value)
{
    iconUrl = value;
}

