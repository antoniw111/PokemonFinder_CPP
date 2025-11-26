#include <QApplication>
#include "PokemonFinder.h"
#include "AssetManager.h"

int main(int argc, char *argv[]) {
    // Inicjalizacja biblioteki Qt
    QApplication app(argc, argv);

    // Tworzenie logiki biznesowej
    AssetManager assets;

    // Tworzenie GUI i wstrzyknięcie logiki (Dependency Injection)
    PokemonFinder window(&assets);
    window.show();

    // Uruchomienie pętli zdarzeń (Event Loop)
    return app.exec();
}