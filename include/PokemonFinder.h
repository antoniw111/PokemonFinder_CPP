#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "AssetManager.h"

class PokemonFinder : public QWidget {
    Q_OBJECT

public:
    // Konstruktor przyjmuje wskaźnik do asset managera
    explicit PokemonFinder(AssetManager *manager, QWidget *parent = nullptr);

private slots:
    // Slot wywoływany po kliknięciu przycisku
    void onSearchClicked();
    
    // Slot wywoływany, gdy AssetManager zwróci dane
    void onPokemonLoaded(const QString &name, const QPixmap &image);
    
    // Slot do obsługi błędów
    void onError(const QString &msg);

private:
    void setupUi();
    void setupStyle();

    AssetManager *assetManager;

    // Elementy interfejsu (wskaźniki)
    QLabel *titleLabel;
    QLineEdit *pokemonInput;
    QPushButton *searchButton;
    QLabel *pokemonImageLabel;
    QLabel *nameLabel;
    QVBoxLayout *mainLayout;
};