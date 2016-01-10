#include "Rss/headers/rssreader.h"
#include "ui_rssreader.h"
#include <QStandardItemModel>
#include <QListView>
#include <Rss/headers/dbmanager.h>
#include <QInputDialog>
#include <QDebug>
#include <QDir>
#include <Qt>
#include <QXmlStreamReader>
#include <QVBoxLayout>
#include <QWebView>
#include <QSplitter>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QImageReader>

RssReader::RssReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RssReader)
{
    ui->setupUi(this);

    dbManager = DbManager::getDbmanager();
    dbManager->createDatabase();

    getChannelsFromDB();

}

RssReader::~RssReader()
{
    delete ui;
}

void RssReader::on_rssList_clicked(const QModelIndex &index)
{
    QStandardItemModel *itemModel = (QStandardItemModel*)index.model();
    QStandardItem *clickedStandardItem = itemModel->itemFromIndex(index);
    clickedStandardItem->setBackground(QBrush(QColor(255,255,255)));
    QString title = clickedStandardItem->text();
    Item clickItem = dbManager->getItemByTitle(title);
    clickItem.setRead(Item::READED);
    dbManager->updateItemRead(clickItem);
    QWebView *currentWebView = ui->rssTab->currentWidget()->findChild<QWebView *>();
    if (currentWebView != 0)
    {
        currentWebView->setHtml(clickItem.getDescription());
    }
    else
    {
        qDebug() << "cannot find webview";
    }
}


void RssReader::on_actionAdd_Rss_triggered()
{
    bool ok;
    QString rssSourceUrl = QInputDialog::getText(this, tr("Add new Rss source"), tr("Rss address:                                                                 "), QLineEdit::Normal, "", &ok);
    if (ok && !rssSourceUrl.isEmpty())
    {
        qDebug() << rssSourceUrl;
        get_rss_xml(rssSourceUrl);
    }
}

void RssReader::get_rss_xml(QString url)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
    rssLink = url;
}

void RssReader::replyFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug() << "Network Reply error: " << reply->errorString();
    }
    else
    {
        QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();

        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toString();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        if (contentType == "text/xml")
        {
            reader.addData(reply->readAll());

            while(!reader.atEnd())
            {
                reader.readNext();
                qDebug()<< "reader is start element? " << reader.isStartElement()
                        << " reader is now at: " << reader.name();
                if (reader.isStartElement() && reader.name() == "channel")
                {
                    this->parseChannel();
                }
            }
        }
        else if (contentType == "image/gif")
        {
            tabIcon = new QIcon;
            QImage img;
            img.loadFromData(reply->readAll());
            if (img.save("Icon.gif"))
            {
                qDebug() << "Saved";
            }
            else
            {
                qDebug() << "Failed";
            }
            tabIcon->addFile("Icon.gif");

            ui->rssTab->currentWidget()->setWindowIcon(*tabIcon);
        }
    }
}

int RssReader::parseChannel()
{
    int channelId = -1;
    Channel channel;
    while (!reader.atEnd())
    {
        reader.readNext();
        qDebug()<< "reader is start element? " << reader.isStartElement()
                << " reader is now at: " << reader.name();
        if (reader.isStartElement())
        {
            QString name = reader.name().toString();
            QString text = "";
            if (name != "item" && name != "image")
            {
                text = reader.readElementText();
            }
            if (name == "title")
            {
                channel.setTitle(text);
            }
            else if (name == "link")
            {
                channel.setLink(text);
            }
            else if (name == "description")
            {
                channel.setDescription(text);
            }
            else if (name == "copyright")
            {
                channel.setCopyright(text);
            }
            else if (name == "image")
            {
                while (true)
                {
                    reader.readNext();
                    if (reader.isEndElement() && reader.name() == "image")
                    {
                        break;
                    }
                    else if (reader.isStartElement())
                    {
                        if (reader.name() == "title")
                        {
                            //do nothing
                        }
                        else if (reader.name() == "link")
                        {
                            //do nothing
                        }
                        else if (reader.name() == "url")
                        {
                            channel.setIconUrl(reader.readElementText());
                        }
                    }
                }
            }
            else if (name == "item")
            {
                channel.setRssLink(rssLink);
                channelId = dbManager->insertChannel(channel);
                parseItem(channelId);
            }
        }
        if (reader.hasError())
        {
            qDebug() << reader.errorString();
        }
    }
    return channelId;
}

void RssReader::parseItem(int channelId)
{
    Item item;
    item.setChannelId(channelId);
    while (!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            QString name = reader.name().toString();
            QString text = "";
            if (name != "item")
            {
                text = reader.readElementText();
            }

            if (name == "title")
            {
                item.setTitle(text);
            }
            else if (name == "description")
            {
                item.setDescription(text);
            }
            else if (name == "link")
            {
                item.setLink(text);
            }
            else if (name == "pubDate")
            {
                item.setPubDate(text);
            }
        }
        else if (reader.isEndElement() && reader.name() == "item")
        {
            dbManager->insertItem(item);
        }
        else if (reader.isEndElement() && reader.name() == "channel")
        {
            qDebug() << "getting items......";
            getItems(channelId);
            break;
        }
    }
}

// add new rss tab and fill items
void RssReader::getItems(int channelId)
{
    QStandardItemModel *itemModel = new QStandardItemModel();
    QList<Item> items = dbManager->getAllItemsOfChannel(channelId);
    foreach (Item item, items) {
        QStandardItem* i = new QStandardItem(QIcon(":/icons/images/feed-icon-14x14.png"), item.getTitle());
        i->setBackground(item.getRead() == Item::UNREAD ? QBrush(QColor(0, 255, 0)) : QBrush(QColor(255, 255, 255)));
        itemModel->appendRow(i);
    }

    QSplitter *qSplitter = new QSplitter;
    qSplitter->setOrientation(Qt::Horizontal);

    QListView *rssList = new QListView;
    rssList->setModel(itemModel);
    connect(rssList, SIGNAL(clicked(QModelIndex)), this, SLOT(on_rssList_clicked(QModelIndex)));
    QWebView *content = new QWebView;
    qSplitter->addWidget(rssList);
    qSplitter->addWidget(content);

    QVBoxLayout *qvBoxLayout = new QVBoxLayout;
    qvBoxLayout->addWidget(qSplitter);

    QWidget *qWidget = new QWidget;
    qWidget->setLayout(qvBoxLayout);

    Channel channel = dbManager->getChannelById(channelId);
    tabIcon = new QIcon;
    QString iconUrl = channel.getIconUrl();
    if (!iconUrl.isEmpty())
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
        manager->get(QNetworkRequest(QUrl(iconUrl)));
    }
    else
    {
        tabIcon->addFile(":/icons/images/feed-icon-14x14.png");
    }
    ui->rssTab->addTab(qWidget, *tabIcon, channel.getTitle());
}

void RssReader::getChannelsFromDB()
{
    QList<Channel> channels = dbManager->getAllChannels();
    foreach (Channel channel, channels)
    {
        getItems(channel.getId());
    }
}

void RssReader::on_actionRefresh_triggered()
{
    QWidget *currentWidget = ui->rssTab->currentWidget();
    QListView *currentListView = currentWidget->findChild<QListView *>();
}
