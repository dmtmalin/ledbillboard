#include <QDebug>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutableListIterator>
#include "model/mediacontent.h"
#include "playlist.h"

Playlist::Playlist(QObject *parent) : QObject(parent)
{
    this->mediaContent = new QList<MediaContent *>();
    this->iMediaContent = new QMutableListIterator<MediaContent *>(
                *this->mediaContent);
}

Playlist *Playlist::fromJson(QJsonObject &obj, QObject *parent)
{
    int id = obj["baseId"].toInt();
    QString command = obj["schedule"].toObject()
            ["cron"].toString();
    QString description = obj["schedule"].toObject()
            ["description"].toString();
    QString company = obj["company"].toString();
    Playlist *playlist = new Playlist(parent);
    playlist->setId(id);
    playlist->setCronCommand(command);
    playlist->setCronDescription(description);
    playlist->setCompany(company);
    QJsonArray mediaArr = obj["media"].toArray();
    if (mediaArr.isEmpty()) {
        qWarning() << QString("Playlist %1 not have media item.").arg(id);
    }
    else {
        foreach (const QJsonValue &item, mediaArr) {
            QJsonObject obj = item.toObject();
            MediaContent *media = MediaContent::fromJson(obj, playlist);
            playlist->addMedia(media);
        }
    }
    return playlist;
}

/*
 * SETTERS
*/

void Playlist::setId(int &id)
{
    this->id = id;
}

void Playlist::setCronCommand(QString &command)
{
    this->cronCommand = command;
}

void Playlist::setCronDescription(QString &desc)
{
    this->cronDescription = desc;
}

void Playlist::setCompany(QString &name)
{
    this->company = name;
}

/*
 * GETTERS
*/

int Playlist::getId()
{
    return this->id;
}

QString Playlist::getCronCommand()
{
    return this->cronCommand;
}

QString Playlist::getCronDescription()
{
    return this->cronDescription;
}

QString Playlist::getCompany()
{
    return this->company;
}

QList<MediaContent *> *Playlist::getMediaContent()
{
    return this->mediaContent;
}

MediaContent *Playlist::getMedia(int index)
{
    return this->mediaContent->at(index);
}

MediaContent *Playlist::nextMedia()
{
    if(!this->iMediaContent->hasNext())
        this->iMediaContent->toFront();    
    return this->iMediaContent->next();
}

void Playlist::addMedia(MediaContent *media)
{
    this->iMediaContent->insert(media);
}

Playlist::~Playlist()
{
    delete this->iMediaContent;
    qDeleteAll(this->mediaContent->begin(), this->mediaContent->end());
    delete this->mediaContent;
}
