#ifndef CHANNEL_H
#define CHANNEL_H
#include <QString>


class Channel
{
public:
    Channel();

    int getId() const;
    void setId(int value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getLink() const;
    void setLink(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getCopyright() const;
    void setCopyright(const QString &value);

    QString getIconUrl() const;
    void setIconUrl(const QString &value);

    QString getRssLink() const;
    void setRssLink(const QString &value);

private:
    int id;
    QString title;
    QString link;
    QString description;
    QString copyright;
    QString iconUrl;
    QString rssLink;
};

#endif // CHANNEL_H
