#include "AssetManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

AssetManager::AssetManager(QObject *parent) : QObject(parent) {
    netManager = new QNetworkAccessManager(this);
    ensureCacheExists();
}

void AssetManager::ensureCacheExists() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    cacheDir.setPath(path);
    
    if (!cacheDir.exists()) {
        if (cacheDir.mkpath(".")) {
            qDebug() << "Cache created at:" << cacheDir.absolutePath();
        }
    } else {
        qDebug() << "Cache ready at:" << cacheDir.absolutePath();
    }
}

QString AssetManager::getCachePath(const QString &filename) {
    return cacheDir.filePath(filename);
}

void AssetManager::loadInitialState() {
    QString placeholderPath = getCachePath("placeholder.png");

    if (QFile::exists(placeholderPath)) {
        QPixmap pix(placeholderPath);
        if (!pix.isNull()) {
            emit pokemonLoaded("Ditto", pix);
            return;
        }
    }
    downloadAndEmitPlaceholder();
}

void AssetManager::downloadAndEmitPlaceholder() {
    QUrl url("https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/other/official-artwork/132.png");
    QNetworkRequest request(url);
    QNetworkReply *reply = netManager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        reply->deleteLater();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QPixmap pix;
            pix.loadFromData(data);
            
            QString savePath = getCachePath("placeholder.png");
            QFile file(savePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(data);
                file.close();
            }
            emit pokemonLoaded("Ditto", pix);
        } else {
            // Tu błąd jest krytyczny - nie możemy nawet pobrać placeholdera
            emit errorOccurred("Fatal: No internet connection to download assets.");
        }
    });
}

void AssetManager::requestPokemon(const QString &pokemonName) {
    QString safeName = pokemonName.toLower().trimmed();
    
    if (safeName.isEmpty()) {
        emit errorOccurred("Please enter a name.");
        return;
    }

    QString localFile = getCachePath(safeName + ".png");
    if (QFile::exists(localFile)) {
        qDebug() << "Loaded from cache:" << localFile;
        emit pokemonLoaded(safeName, QPixmap(localFile));
        return;
    }

    QString urlStr = QString("https://pokeapi.co/api/v2/pokemon/%1").arg(safeName);
    QNetworkRequest request((QUrl(urlStr)));
    QNetworkReply *reply = netManager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply](){
        this->onPokemonDataReceived(reply);
    });
}

void AssetManager::onPokemonDataReceived(QNetworkReply *reply) {
    reply->deleteLater();

    // PROFESJONALNA OBSŁUGA BŁĘDÓW SIECIOWYCH
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg;
        
        // Sprawdzamy konkretny kod błędu
        switch (reply->error()) {
            case QNetworkReply::ContentNotFoundError: // Kod 404
                errorMsg = "Pokemon not found! Check spelling.";
                break;
            case QNetworkReply::ConnectionRefusedError:
            case QNetworkReply::HostNotFoundError:
            case QNetworkReply::TimeoutError:
                errorMsg = "No Internet Connection!";
                break;
            case QNetworkReply::InternalServerError:
            case QNetworkReply::ServiceUnavailableError: // Kod 500/503
                errorMsg = "PokeAPI server is down.";
                break;
            default:
                // Inne błędy (np. SSL, Protocol error)
                errorMsg = "Network Error: " + reply->errorString();
        }
        
        emit errorOccurred(errorMsg);
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString name = obj["forms"].toArray()[0].toObject()["name"].toString();
    this->currentPokemonName = name;

    QString picUrl = obj["sprites"].toObject()["other"].toObject()
                        ["official-artwork"].toObject()["front_default"].toString();

    QNetworkRequest request((QUrl(picUrl)));
    QNetworkReply *imgReply = netManager->get(request);

    connect(imgReply, &QNetworkReply::finished, [this, imgReply](){
        this->onImageDownloaded(imgReply);
    });
}

void AssetManager::onImageDownloaded(QNetworkReply *reply) {
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        // Jeśli dane przyszły, a obrazek nie - to dziwne, ale możliwe
        emit errorOccurred("Could not download image.");
        return;
    }

    QByteArray imageData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(imageData);

    QString savePath = getCachePath(currentPokemonName + ".png");
    QFile file(savePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(imageData);
        file.close();
    }

    emit pokemonLoaded(currentPokemonName, pixmap);
}