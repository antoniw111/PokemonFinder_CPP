#include "PokemonFinder.h"
#include <QMessageBox> // Dodajemy obsługę okien dialogowych

PokemonFinder::PokemonFinder(AssetManager *manager, QWidget *parent)
    : QWidget(parent), assetManager(manager) 
{
    setupUi();
    setupStyle();

    connect(assetManager, &AssetManager::pokemonLoaded, 
            this, &PokemonFinder::onPokemonLoaded);
            
    connect(assetManager, &AssetManager::errorOccurred,
            this, &PokemonFinder::onError);

    assetManager->loadInitialState();
}

void PokemonFinder::setupUi() {
    setWindowTitle("Pokemon Finder C++");
    resize(500, 600);

    titleLabel = new QLabel("Enter Pokemon name:", this);
    pokemonInput = new QLineEdit(this);
    searchButton = new QPushButton("Look for Pokemon", this);
    
    pokemonImageLabel = new QLabel(this);
    pokemonImageLabel->setFixedSize(475, 475);
    pokemonImageLabel->setScaledContents(true);
    
    nameLabel = new QLabel("Loading...", this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(pokemonInput);
    mainLayout->addWidget(searchButton);
    mainLayout->addWidget(pokemonImageLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(nameLabel);

    titleLabel->setAlignment(Qt::AlignCenter);
    pokemonInput->setAlignment(Qt::AlignCenter);
    nameLabel->setAlignment(Qt::AlignCenter);

    connect(searchButton, &QPushButton::clicked, this, &PokemonFinder::onSearchClicked);
    connect(pokemonInput, &QLineEdit::returnPressed, this, &PokemonFinder::onSearchClicked);
}

void PokemonFinder::setupStyle() {
    QString style = R"(
        QLabel, QPushButton {
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#title {
            font-size: 20px;
            font-style: italic;
        }
        QLineEdit {
            font-size: 20px;
            padding: 5px;
        }
        QPushButton {
            font-size: 18px;
            font-weight: bold;
            background-color: #ddd;
            padding: 10px;
        }
        QLabel#name {
            font-size: 30px;
            font-weight: bold;
        }
    )";
    
    titleLabel->setObjectName("title");
    nameLabel->setObjectName("name");
    
    this->setStyleSheet(style);
}

void PokemonFinder::onSearchClicked() {
    QString text = pokemonInput->text();
    searchButton->setDisabled(true);
    searchButton->setText("Searching...");
    nameLabel->setText("..."); 
    
    assetManager->requestPokemon(text);
}

void PokemonFinder::onPokemonLoaded(const QString &name, const QPixmap &image) {
    nameLabel->setText(name.toUpper());
    pokemonImageLabel->setPixmap(image);
    
    searchButton->setDisabled(false);
    searchButton->setText("Look for Pokemon");
}

void PokemonFinder::onError(const QString &msg) {
    searchButton->setDisabled(false);
    searchButton->setText("Look for Pokemon");
    
    // Ustawiamy tekst na czerwono, żeby było widać błąd w oknie
    nameLabel->setText("Error!");
    
    // Wyświetlamy systemowy popup z błędem
    // Warning oznacza ikonę żółtego trójkąta. Można użyć Critical dla czerwonego X.
    QMessageBox::warning(this, "Problem detected", msg);
}