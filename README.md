# GenealogyApp

**GenealogyApp** to aplikacja desktopowa służąca do zarządzania drzewem genealogicznym, napisana w języku C++ z wykorzystaniem biblioteki Qt.

## Opis funkcjonalności

- **Dodawanie osób**  
  Aplikacja umożliwia dodawanie nowych osób do drzewa genealogicznego poprzez wypełnienie formularza z danymi osobowymi (imię, nazwisko, nazwisko panieńskie, daty i miejsca urodzenia oraz śmierci, numer telefonu, zawód, notatki).

- **Edycja i usuwanie osób**  
  Istnieje możliwość edycji oraz usuwania wybranych osób z listy.

- **Tworzenie relacji rodzinnych**  
  Program pozwala na definiowanie relacji rodzinnych pomiędzy osobami, takich jak rodzic, dziecko czy małżonek. Relacje te są przechowywane jako powiązania pomiędzy unikalnymi identyfikatorami osób.

- **Wyświetlanie listy osób**  
  Wszystkie osoby są prezentowane na liście wraz z podstawowymi informacjami (imię, nazwisko, data urodzenia, identyfikator).

- **Wyświetlanie szczegółowych informacji**  
  Podwójne kliknięcie na wybranej osobie umożliwia wyświetlenie szczegółowych danych, w tym powiązań rodzinnych.

- **Prezentacja drzewa genealogicznego**  
  Aplikacja umożliwia prezentację drzewa genealogicznego wybranej osoby w formie hierarchicznej (QTreeWidget).

- **Zapis i odczyt danych w formacie JSON**  
  Cała struktura drzewa genealogicznego może zostać zapisana do pliku JSON oraz wczytana z pliku, z zachowaniem wszystkich danych i relacji.

## Sposób użytkowania

1. **Dodawanie osoby**  
   Możliwe jest dodanie nowej osoby poprzez wybranie opcji „Dodaj osobę”, wypełnienie formularza oraz zatwierdzenie danych. Osoba zostanie dodana do listy.

2. **Edycja i usuwanie osoby**  
   Po zaznaczeniu osoby na liście dostępne są opcje edycji oraz usunięcia.

3. **Tworzenie relacji**  
   Po zaznaczeniu osoby bazowej można utworzyć relację rodziną, wybierając odpowiedni typ relacji oraz osobę powiązaną.

4. **Wyświetlanie drzewa genealogicznego**  
   Po zaznaczeniu osoby możliwe jest wyświetlenie jej drzewa genealogicznego w formie graficznej.

5. **Zapis i odczyt danych**  
   Aplikacja umożliwia zapisanie oraz wczytanie danych genealogicznych w formacie JSON.

## Struktura danych

- Każda osoba posiada unikalny identyfikator (ID).
- Relacje rodzinne (rodzice, dzieci, małżonek) przechowywane są jako listy identyfikatorów.
- Dane są serializowane do formatu JSON, co umożliwia ich łatwe przenoszenie oraz archiwizację.

## Wymagania systemowe

- Qt 6.x (aplikacja wykorzystuje Qt Widgets)
- Kompilator C++ (np. MinGW, MSVC)

## Instrukcja uruchomienia

1. Projekt można otworzyć w środowisku Qt Creator lub Visual Studio Code z odpowiednią konfiguracją Qt.
2. Należy zbudować projekt.
3. Po zakończeniu kompilacji aplikacja jest gotowa do uruchomienia.

## Pliki projektu

- `mainwindow.cpp`, `mainwindow.h` – główne okno aplikacji oraz logika działania
- `person.cpp`, `person.h` – klasa reprezentująca osobę
- `persondialog.*` – okno dialogowe do edycji i dodawania osoby
- `relationdialog.*` – okno dialogowe do definiowania relacji rodzinnych
- `mainwindow.ui` – plik interfejsu graficznego
- `README.md` – niniejszy plik

---

Aplikacja przeznaczona jest do celów edukacyjnych oraz do zarządzania domowym drzewem genealogicznym.