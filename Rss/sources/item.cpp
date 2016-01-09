#include "Rss/headers/item.h"

Item::Item()
{
}

int Item::getId() const
{
    return id;
}

void Item::setId(int value)
{
    id = value;
}

int Item::getChannelId() const
{
    return channelId;
}

void Item::setChannelId(int value)
{
    channelId = value;
}

QString Item::getTitle() const
{
    return title;
}

void Item::setTitle(const QString &value)
{
    title = value;
}

QString Item::getDescription() const
{
    return description;
}

void Item::setDescription(const QString &value)
{
    description = value;
}

QString Item::getLink() const
{
    return link;
}

void Item::setLink(const QString &value)
{
    link = value;
}

QString Item::getPubDate() const
{
    return pubDate;
}

void Item::setPubDate(const QString &value)
{
    pubDate = value;
}

int Item::getRead() const
{
    return read;
}

void Item::setRead(int value)
{
    read = value;
}

const int Item::READED = 1;
const int Item::UNREAD = 0;
