#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{
public:
    Item();

    int getId() const;
    void setId(int value);

    int getChannelId() const;
    void setChannelId(int value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getLink() const;
    void setLink(const QString &value);

    QString getPubDate() const;
    void setPubDate(const QString &value);

    int getRead() const;
    void setRead(int value);

    static const int UNREAD;
    static const int READED;

private:
    int id;
    int channelId;
    QString title;
    QString description;
    QString link;
    QString pubDate;
    int read;
};

#endif // ITEM_H
