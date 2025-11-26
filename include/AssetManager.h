#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QDir>
#include <QStandardPaths>

// WAŻNE: 'public QObject' naprawia błąd kompilacji
class AssetManager : public QObject {
    Q_OBJECT 

public:
    explicit AssetManager(QObject *parent = nullptr);
    
    // Główna funkcja do szukania
    void requestPokemon(const QString &pokemonName);
    
    // Nowa funkcja: Ustawia stan początkowy (Ditto)
    void loadInitialState();

signals:
    void pokemonLoaded(const QString &name, const QPixmap &image);
    void errorOccurred(const QString &message);

private slots:
    void onPokemonDataReceived(QNetworkReply *reply);
    void onImageDownloaded(QNetworkReply *reply);

private:
    QNetworkAccessManager *netManager;
    QDir cacheDir;
    QString currentPokemonName;

    void ensureCacheExists();
    QString getCachePath(const QString &filename);
    
    // Pomocnicza do pobrania Ditto, jeśli nie ma go na dysku
    void downloadAndEmitPlaceholder();
};