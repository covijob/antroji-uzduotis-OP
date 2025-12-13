## Projekto paskirtis

Ši programa skirta apdoroti didelius studentų įrašų kiekius ir suskirstyti juos į dvi kategorijas:

- Vargšiukai: studentai, kurių galutinis balas < 5  
- Kietiakiai: studentai, kurių galutinis balas ≥ 5  

Naudojami du skirtingi konteineriai:

- `std::vector<Studentas>`
- `std::list<Studentas>`

Trys skaidymo strategijos:

1. `partition_copy`
2. `remove_if`
3. `partition`

Programa gali veikti:

- **Interaktyviu režimu**
- **Benchmark režimu** (automatiniai testai visiems failams)


## Sistemos informacija
- Procesorius: 12th gen Intel i7-12650H
- Operatyvioji atmintis (RAM): 16GB
- Diskas: SSD
- Operacinė sistema:  Windows 11, 64-bit
*Nuadojama Visual Studio 2022*


## Kalbos standartas

C++20 Standart

## v2.0 patch notes

– Parengta projekto dokumentacija naudojant Doxygen ir įkelta į repozitoriją kaip atskiras HTML katalogas.
– Įgyvendinti unit testai naudojant Catch2 C++ testavimo framework’ą, skirti pagrindinių klasių ir funkcijų funkcionalumo patikrinimui.
– Testai integruoti kaip projekto dalis, demonstruojant testavimo paskirtį ir naudą programos patikimumui užtikrinti.

## v1.5 patch notes

- Sukurta bazinė abstrakti klasė Zmogus, aprašanti bendrus žmogaus duomenis (vardą ir pavardę).
- Zmogus turi gryną virtualų metodą, todėl negalima sukurti jo objekto.
- Klasė Studentas dabar paveldi iš Zmogus ir įgyvendina paveldėtą spausdinti() metodą.
- Visa skaičiavimo, rikiavimo, failų skaitymo ir išvedimo logika nepakito – programa veikia taip pat kaip ankstesnė v1.2 versija.
- Kodas sutvarkytas taip, kad studentų duomenų apdorojimas remiasi OOP paveldėjimu, o struktūra tapo aiškesnė ir lengviau plečiama.
- Atnaujinti susiję moduliai (ivestis, formatas, skaiciavimas, v03_api), kad dirbtų su paveldėjimu ir nauju api.
- patikrinta, ar programa išlaiko identišką v1.2 veikimą su tais pačiais failais, ar tinkamai išveda rezultatus.

*Zmogus.hpp* struktūra:


class Zmogus {
protected:
    std::string v_;
    std::string p_;

public:
    Zmogus() = default;

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : v_(vardas), p_(pavarde) {
    }

    virtual ~Zmogus() = default;

    const std::string& vardas() const {
        return v_;
    }

    const std::string& pavarde() const {
        return p_;
    }

    virtual void spausdinti(std::ostream& os) const = 0;
};



## v1.2 patch notes

- Realizuota *Rule of three* pagal OOP principus bei realizuoti įvesties/išvesties operatoriai.
- Grąžintas rankinis duomenų įvedimas bei galimybį išvesti rezultatus į konsolę.
- Atliktas naujas bench_mark testas_

## v1.1 patch notes

– Refaktorizuota programa, pereinant nuo struct pagrįstos realizacijos prie Studentas klasės, atlikti atitinkami pakeitimai visame kode.
– Įgyvendintas našumo palyginimas tarp ankstesnės (struct) ir dabartinės (class) realizacijos, naudojant tą patį konteinerį (std::vector) ir vienodą skaidymo strategiją.
– Atlikta eksperimentinė analizė su skirtingais kompiliatoriaus optimizavimo lygiais (-O1, -O2, -O3).

## Diegimo (build) instrukcija – CMake

### 1. Atsidarykite terminalą projekto šakniniame kataloge
Tai katalogas, kuriame yra `CMakeLists.txt`.


### 2. (Rekomenduojama) Ištrinkite seną build katalogą

Powershell:
Remove-Item -Recurse -Force build

### 3. Sugeneruokite CMake build failus

cmake -S . -B build

### 4. Sukompiliuokite projekt1 Release režimu

cmake --build build --config Release

### 5. Įsitikinkite, kad turite:

- .\build\Release\Pirmoji_uzduotis.exe   
- .\build\Release\Pirmoji_uzduotis_tests.exe


## Naudojimas

# FAILŲ GENERAVIMAS:
1. Paleisti programą.
2. UI pasirinkti 'Įprastą režimą'
3. Generuoti naujus failus.

# DARBAS SU FAILAIS:
1. Paleisti programą.
2. Pasirinkti režimą:
   - **1** – normalus režimas
   - **2** – benchmark režimas
3. Benchmark režimas automatiškai ištestuos visus įmanomus scenarijus, o 'normalus režimas' -> 'esamo failo naudojimas' leis dirbti su failais po vieną. 

# RANKA ĮVEDAMI DUOMENYS
1. Paleisti programą.
2. Pasirinkti įvedimo ranka ražimą.

*Papildomai galima visus rezultatus išvesti į konsolę*

# Unit testai

1. Paleisti programą.
2. Pasirinkti režimą:
   - **4** – Unit tests

### UŽDUOTIES ĮYVENDINIMO STRATEGIJOS

## `partition_copy` streategija 1

`partition_copy` nekeičia originalaus konteinerio.

Ji pereina per visus elementus ir kiekvieną nukopijuoja į vieną iš dviejų
naujų konteinerių — **vargšiukus** ir **kietiakius**.

Tai saugus metodas, nes originalūs duomenys lieka nepakitę, tačiau strategijai
reikia papildomos atminties. Praktikoje ji labai greita su `std::vector`,
nes rašo nuosekliai į du ištisinius masyvus.


## `remove_if` strateija 2

`remove_if` modifikuoja originalų konteinerį.

Ji pašalina visus elementus, kurie neturi likti, ir palieka tik vieną
grupę. Šis metodas iš esmės nėra tikras skaidymas į dvi dalis — jis
tiesiog “išmeta” vieną iš kategorijų.

Strategija taupi atminčiai, bet nepraktiška, kai reikia **abiejų**
grupių. Dideliuose failuose dažnai veikia lėčiau nei kiti metodai.


## `partition` strategija 3

`partition` taip pat keičia originalų konteinerį, tačiau nieko
neištrina — tik pertvarko elementus.

Po operacijos konteineryje pirmoje pusėje atsiduria visi elementai,
tenkinantys predikatą, antroje — visi kiti. Ribos iteratorius leidžia
šį vieną konteinerį logiškai padalinti į dvi dalis.

Šiai strategijai beveik nereikia papildomos atminties. Su `std::list`
ji ypač greita, nes perrišamos tik mazgų rodyklės, o ne kopijuojami
duomenys.


Visuose testuose fiksuojamas tik **bendras programos veikimo laikas (ms)**.

### 1.2 Benchmark rezultatai:

## Rezultatai: std::vector

| Failas                | Įrašų sk.  | Strategija 1 `partition_copy` (ms) | Strategija 2 `remove_if` (ms) | Strategija 3 `partition` (ms) |
|-----------------------|-----------:|------------------------------------:|-------------------------------:|-------------------------------:|
| studentai_100_K6      |        100 | 26                                 | 1                              | 0                              |
| studentai_1000_K6     |      1 000 | 16                                 | 5                              | 9                              |
| studentai_10000_K6    |     10 000 | 68                                 | 47                             | 52                             |
| studentai_100000_K6   |    100 000 | 506                                | 481                            | 501                            |
| studentai_1000000_K6  |  1 000 000 | 5531                               | 4957                           | 5178                           |
| studentai_10000000_K6 | 10 000 000 | 54337                              | 52876                          | 55578                          |


## Rezultatai: std::list

| Failas                | Įrašų sk.  | Strategija 1 `partition_copy` (ms) | Strategija 2 `remove_if` (ms) | Strategija 3 `partition` (ms) |
|-----------------------|-----------:|------------------------------------:|-------------------------------:|-------------------------------:|
| studentai_100_K6      |        100 | 0                                  | 0                              | 1                              |
| studentai_1000_K6     |      1 000 | 9                                  | 4                              | 17                             |
| studentai_10000_K6    |     10 000 | 56                                 | 41                             | 59                             |
| studentai_100000_K6   |    100 000 | 386                                | 399                            | 401                            |
| studentai_1000000_K6  |  1 000 000 | 4051                               | 4672                           | 4114                           |
| studentai_10000000_K6 | 10 000 000 | 42300                              | 41108                          | 43717                          |


*vector rezultatai suprasteje, bet list paspartejo*

### v1.1  Rezultatai:


## STRUCT

# std::vector — Strategijų palyginimas

| Failas | Strat 1 (ms) | Strat 2 (ms) | Strat 3 (ms) |
|--------|--------------|--------------|--------------|
| 10 000 000 |   46 606 |       53 738 | 51 970 |
| 1 000 000  |    4 465 |        5 340 |  5 540 |
| 100 000    |      552 |          781 |    574 |
| 10 000     |       67 |           53 |     44 |
| 1 000 K6   |       25 |           10 |     18 |
| 1 000 K7   |       20 |           11 |     17 |


# std::list — Strategijų palyginimas

| Failas | Strat 1 (ms) | Strat 2 (ms) | Strat 3 (ms) |
|--------|--------------|--------------|--------------|
| 10 000 000 |  50 180  | 53 145       | 49 747 |
| 1 000 000  |  5 503   |  5 289       |  4 892 |
| 100 000    |    501   |    518       |    521 |
| 10 000     |     51   |     59       |     51 |
| 1 000 K6   |     16   |     10       |     19 |
| 1 000 K7   |     16   |     10       |     14 |


### CLASS 

# std::vector — Strategijų palyginimas

| Failas | Strategija 1 (ms) | Strategija 2 (ms) | Strategija 3 (ms) |
|--------|--------------------|--------------------|--------------------|
| 10 000 000 | 51 361         | 54 228             | 61 690 |
| 1 000 000  |  5 289         |  5 269             |  5 185 |
| 100 000    |    603         |    493             |   536 |
| 10 000     |     55         |     58             |     57 |
| 1 000 K6   |     30         |     14             |     10 |
| 1 000 K7   |      9         |      9             |      8 |
| 100        |     13 |     11|      0             |      0


# std::list — Strategijų palyginimas

| Failas | Strategija 1 (ms) | Strategija 2 (ms) | Strategija 3 (ms) |
|--------|--------------------|--------------------|--------------------|
| 10 000 000 | 105 541        | 91 570             | 47 549 |
| 1 000 000  |   4 696        |  4 714             |  4 757 |
| 100 000    |     470        |    462             |    462 |
| 10 000     |      61        |     57             |     54 |
| 1 000 K6   |      10        |     13             |     14 |
| 1 000 K7   |      13        |      7             |     16 |
| 100        |       0        |      0             |      0 |





### SKIRTINGŲ OPTIMIZACIJU REZULTATAI

## O1 optimizacijos rezultatai (/O1)

### std::vector

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 54929        | 50345        | 50164        |
| 1 000 000 K6        | 345901       | 3591         | 6400         |
| 100 000 K6          | 1034         | 1156         | 1246         |
| 10 000 K6           | 104          | 109          | 121          |
| 1 000 K6            | 13           | 15           | 15           |
| 1 000 K7            | 14           | 11           | 10           |
| 100 K6              | 6            | 2            | 1            |

### std::list

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 45781        | 42867        | 46698        |
| 1 000 000 K6        | 12848        | 13916        | 13781        |
| 100 000 K6          | 1117         | 883          | 889          |
| 10 000 K6           | 101          | 118          | 106          |
| 1 000 K6            | 21           | 12           | 15           |
| 1 000 K7            | 14           | 10           | 14           |
| 100 K6              | 1            | 2            | 2            |


## O2 optimizacijos rezultatai (/O2)

### std::vector

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 57197        | 57150        | 49950        |
| 1 000 000 K6        | 8973         | 4759         | 4912         |
| 100 000 K6          | 479          | 475          | 500          |
| 10 000 K6           | 55           | 50           | 50           |
| 1 000 K6            | 7            | 10           | 12           |
| 1 000 K7            | 14           | 14           | 8            |
| 100 K6              | 14           | 13           | 0            |

### std::list

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 45683        | 43222        | 81995        |
| 1 000 000 K6        | 4469         | 4334         | 4640         |
| 100 000 K6          | 444          | 428          | 449          |
| 10 000 K6           | 53           | 53           | 53           |
| 1 000 K6            | 12           | 14           | 9            |
| 1 000 K7            | 9            | 12           | 14           |
| 100 K6              | 0            | 0            | 0            |


## O3 optimizacijos rezultatai (/Ox ≈ O3)

### std::vector

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 47677        | 47455        | 48920        |
| 1 000 000 K6        | 4781         | 4879         | 4754         |
| 100 000 K6          | 467          | 473          | 485          |
| 10 000 K6           | 44           | 47           | 64           |
| 1 000 K6            | 7            | 30           | 6            |
| 1 000 K7            | 7            | 12           | 7            |
| 100 K6              | 0            | 0            | 0            |

### std::list

| Failas              | Strategija 1 | Strategija 2 | Strategija 3 |
|---------------------|--------------|--------------|--------------|
| 10 000 000 K6       | 44566        | 43120        | 46315        |
| 1 000 000 K6        | 4411         | 4138         | 4360         |
| 100 000 K6          | 440          | 435          | 433          |
| 10 000 K6           | 49           | 49           | 49           |
| 1 000 K6            | 11           | 4            | 6            |
| 1 000 K7            | 8            | 11           | 6            |
| 100 K6              | 0            | 0            | 0            |
