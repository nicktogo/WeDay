#ifndef RSSREADER_H
#define RSSREADER_H

#include <QMainWindow>
#include <QItemSelection>
#include <QString>
#include <QtNetwork>
#include <QXmlStreamReader>
#include <Rss/headers/dbmanager.h>
#include <QStandardItemModel>
#include <QList>

namespace Ui {
class RssReader;
}

class RssReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit RssReader(QWidget *parent = 0);
    ~RssReader();

private slots:
    void on_rssList_clicked(const QModelIndex &index);

    void on_actionAdd_Rss_triggered();

    void replyFinished(QNetworkReply*);

private:
    Ui::RssReader *ui;
    DbManager* dbManager;
    QXmlStreamReader reader;
    QStandardItemModel *itemModel;
    void getChannelsFromDB();
    void getItems(int channelId);
    int parseChannel();
    void parseItem(int);
    void get_rss_xml(QString url);
};

#endif // RSSREADER_H
