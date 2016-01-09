#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <Rss/headers/channel.h>
#include <Rss/headers/item.h>
#include <QtNetwork>
#include <QList>

class DbManager
{
public:
    DbManager(const QString& path);
    void createDatabase();

    static DbManager* getDbmanager();


    int insertChannel(const Channel& channel);
    bool insertItem(const Item& item);
    QList<Item> getAllItemsOfChannel(const int channelId);
    QList<Channel> getAllChannels();
    bool updateItemRead(const Item& item);
    Item getItemByTitle(const QString& title);
    Item createItem(const QSqlQuery& query);
    Channel getChannelById(const int channelId);
    Channel createChannel(const QSqlQuery& query);

    QString getInsertChannelSQL();
    QString getInsertItemSQL();
    QString getAllItemsOfChannelSQL();
    QString getAllChannelsSQL();
    QString getUpdateItemReadSQL();
    QString getItemByTitleSQL();
    QString getChannelByIdSQL();
private:
    QSqlDatabase rssDb;
    static DbManager* dbmagager;
    static const QString PATH;
};

#endif // DBMANAGER_H
