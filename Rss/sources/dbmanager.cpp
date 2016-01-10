#include "Rss/headers/dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMutex>

DbManager::DbManager(const QString& path)
{
    rssDb = QSqlDatabase::addDatabase("QSQLITE");
    rssDb.setDatabaseName(path);

    if (!rssDb.open())
    {
        qDebug() << "Error: cannot connect to sqlite";
    }
    else
    {
        qDebug() << "Success: connection established";
    }
}

void DbManager::createDatabase()
{
    QString CREATE_CHANNEL = "CREATE TABLE IF NOT EXISTS Channel ("
                             "id integer primary key autoincrement, "
                             "title text, "
                             "link text, "
                             "description text, "
                             "copyright text, "
                             "iconUrl text, "
                             "rssLink text"
                             ");";

    QString CREATE_ITEM = "CREATE TABLE IF NOT EXISTS Item ("
                          "id integer primary key autoincrement, "
                          "channelId integer, "
                          "title text, "
                          "description text, "
                          "link text, "
                          "pubDate text,"
                          "read integer default 0"
                          ");";

    QSqlQuery createTable;
    createTable.exec(CREATE_CHANNEL);
    createTable.exec(CREATE_ITEM);
}

DbManager* DbManager::dbmagager = NULL;
const QString DbManager::PATH = "RSSREADER.db";

DbManager* DbManager::getDbmanager()
{
    if (dbmagager == NULL)
    {
        QMutex mutex;
        mutex.lock();
        dbmagager = new DbManager(PATH);
        mutex.unlock();
    }
    return dbmagager;
}

int DbManager::insertChannel(const Channel& channel)
{
    QSqlQuery query;
    query.prepare(getInsertChannelSQL());
    query.bindValue(":title", channel.getTitle());
    query.bindValue(":link", channel.getLink());
    query.bindValue(":description", channel.getDescription());
    query.bindValue(":copyright", channel.getCopyright());
    query.bindValue(":iconUrl", channel.getIconUrl());
    query.bindValue(":rssLink", channel.getRssLink());
    if (query.exec())
    {
        qDebug() << "insertChannel finished";
    }
    else
    {
        qDebug() << "insertChannel error: " << query.lastError();
    }
    return query.lastInsertId().toInt();
}

bool DbManager::insertItem(const Item &item)
{
    bool result = false;
    QSqlQuery query;
    query.prepare(getInsertItemSQL());
    query.bindValue(":channelId", item.getChannelId());
    query.bindValue(":title", item.getTitle());
    query.bindValue(":description", item.getDescription());
    query.bindValue(":link", item.getLink());
    query.bindValue(":pubDate", item.getPubDate());
    if (query.exec())
    {
        result = true;
        qDebug() << "insertItem finished";
    }
    else
    {
        qDebug() << "insertItem error: " << query.lastError();
    }
    return result;
}

bool DbManager::updateItemRead(const Item &item)
{
    bool result = false;
    QSqlQuery query;
    query.prepare(getUpdateItemReadSQL());
    query.bindValue(":read", item.getRead());
    query.bindValue(":id", item.getId());
    if (query.exec())
    {
        result = true;
    }
    else
    {
        qDebug() << "updateItemRead error: " << query.lastError();
    }
    return result;
}

QList<Item> DbManager::getAllItemsOfChannel(const int channelId)
{
    QList<Item> items;
    QSqlQuery getAllItemsQuery;
    getAllItemsQuery.prepare(getAllItemsOfChannelSQL());
    getAllItemsQuery.bindValue(":channelId", channelId);

    if (getAllItemsQuery.exec())
    {
        qDebug() << "Getting all items...";
        while (getAllItemsQuery.next())
        {
            Item item = createItem(getAllItemsQuery);
            items.append(item);
        }
    }
    return items;
}

Item DbManager::getItemByTitle(const QString &title)
{
    Item item;
    QSqlQuery getItemQuery;
    getItemQuery.prepare(getItemByTitleSQL());
    getItemQuery.bindValue(":title", title);
    if (getItemQuery.exec() && getItemQuery.next())
    {
        item = createItem(getItemQuery);
    }
    return item;
}

Channel DbManager::getChannelById(const int channelId)
{
    Channel channel;
    QSqlQuery getChannelQuery;
    getChannelQuery.prepare(getChannelByIdSQL());
    getChannelQuery.bindValue(":channelId", channelId);
    if (getChannelQuery.exec() && getChannelQuery.next())
    {
        channel = createChannel(getChannelQuery);
    }
    return channel;
}

QList<Channel> DbManager::getAllChannels()
{
    QList<Channel> channels;
    QSqlQuery getAllChannels;
    getAllChannels.prepare(getAllChannelsSQL());
    if (getAllChannels.exec())
    {
        qDebug() << "Getting all channel;";
        while (getAllChannels.next())
        {
            Channel channel = createChannel(getAllChannels);
            channels.append(channel);
        }
    }
    return channels;
}

Item DbManager::createItem(const QSqlQuery& query)
{
    Item item;
    item.setId(query.value(0).toInt());
    item.setChannelId(query.value(1).toInt());
    item.setTitle(query.value(2).toString());
    item.setDescription(query.value(3).toString());
    item.setLink(query.value(4).toString());
    item.setPubDate(query.value(5).toString());
    item.setRead(query.value(6).toInt());
    return item;
}

Channel DbManager::createChannel(const QSqlQuery &query)
{
    Channel channel;
    channel.setId(query.value(0).toInt());
    channel.setTitle(query.value(1).toString());
    channel.setLink(query.value(2).toString());
    channel.setDescription(query.value(3).toString());
    channel.setCopyright(query.value(4).toString());
    channel.setIconUrl(query.value(5).toString());
    channel.setRssLink(query.value(6).toString());
    return channel;
}

QString DbManager::getInsertChannelSQL()
{
    return "INSERT INTO Channel (title, link, description, copyright, iconUrl, rssLink) "
           "VALUES (:title, :link, :description, :copyright, :iconUrl, :rssLink)";
}

QString DbManager::getInsertItemSQL()
{
    return "INSERT INTO Item (channelId, title, description, link, pubDate) "
           "VALUES (:channelId, :title, :description, :link, :pubDate)";
}

QString DbManager::getUpdateItemReadSQL()
{
    return "UPDATE Item SET read = :read WHERE id = :id";
}

QString DbManager::getAllItemsOfChannelSQL()
{
    return "SELECT * FROM Item WHERE channelId = :channelId";
}

QString DbManager::getItemByTitleSQL()
{
    return "SELECT * FROM Item WHERE title = :title LIMIT 1";
}

QString DbManager::getChannelByIdSQL()
{
    return "SELECT * FROM Channel WHERE id = :channelId LIMIT 1";
}

QString DbManager::getAllChannelsSQL()
{
    return "SELECT * FROM Channel";
}
