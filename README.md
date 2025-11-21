
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


### Sistemos informacija
- Procesorius: 12th gen Intel i7-12650H
- Operatyvioji atmintis (RAM): 16GB
- Diskas: SSD
- Operacinė sistema:  Windows 11, 64-bit
*Nuadojama Visual Studio 2022*

# Kalbos standartas

C++20 Standart

## Įdiegimo instrukcija (naudojant CMake)

Projektas sukurtas taip, kad veiktų bet kurioje operacinėje sistemoje naudojant *CMake* ir C++20 kompiliatorių.

### Reikalavimai

Prieš kompiliuodami įsitikinkite, kad turite:

- CMake 3.10
- C++20 suderinamą kompiliatorių:
  - *g++* (Linux)
  - *clang++* (MacOS)
  - *MSVC* (Windows, Visual Studio Build Tools)

Sukurkite build katalogą:

mkdir build
cd build

Paleiskite Cmake projektui konfigutuoti:

cmake ..

Sukompiliuokite programą:

cmake --build .



# Naudojimas

FAILŲ GENERAVIMAS:
1. Paleisti programą.
2. UI pasirinkti 'Įprastą režimą'
3. Generuoti naujus failus.

DARBAS SU FAILAIS:
1. Paleisti programą.
2. Pasirinkti režimą:
   - **1** – normalus režimas
   - **2** – benchmark režimas
3. Benchmark režimas automatiškai ištestuos visus įmanomus scenarijus, o 'normalus režimas' -> 'esamo failo naudojimas' leis dirbti su failais po vieną. 



# Benchmark režimas

Benchmark režimas automatiškai suranda visus failus kataloge, prasidedančius `studentai_` ir testuoja:

- **2 konteinerius** (`vector` ir `list`)
- **3 strategijas**
- **6 skirtingus failų dydžius**

## Studentų skaidymo strategijos

Programa realizuoja tris skirtingas studentų skaidymo strategijas:
`partition_copy`, `remove_if` ir `partition`.

Visos jos atskiria studentus į dvi grupes, tačiau veikia skirtingai tiek
logiškai, tiek našumo ir atminties požiūriu.

---

### `partition_copy`

`partition_copy` nekeičia originalaus konteinerio.

Ji pereina per visus elementus ir kiekvieną nukopijuoja į vieną iš dviejų
naujų konteinerių — **vargšiukus** ir **kietiakius**.

Tai saugus metodas, nes originalūs duomenys lieka nepakitę, tačiau strategijai
reikia papildomos atminties. Praktikoje ji labai greita su `std::vector`,
nes rašo nuosekliai į du ištisinius masyvus.


### `remove_if`

`remove_if` modifikuoja originalų konteinerį.

Ji pašalina visus elementus, kurie neturi likti, ir palieka tik vieną
grupę. Šis metodas iš esmės nėra tikras skaidymas į dvi dalis — jis
tiesiog “išmeta” vieną iš kategorijų.

Strategija taupi atminčiai, bet nepraktiška, kai reikia **abiejų**
grupių. Dideliuose failuose dažnai veikia lėčiau nei kiti metodai.


### `partition`

`partition` taip pat keičia originalų konteinerį, tačiau nieko
neištrina — tik pertvarko elementus.

Po operacijos konteineryje pirmoje pusėje atsiduria visi elementai,
tenkinantys predikatą, antroje — visi kiti. Ribos iteratorius leidžia
šį vieną konteinerį logiškai padalinti į dvi dalis.

Šiai strategijai beveik nereikia papildomos atminties. Su `std::list`
ji ypač greita, nes perrišamos tik mazgų rodyklės, o ne kopijuojami
duomenys.



Visuose testuose fiksuojamas tik **bendras programos veikimo laikas (ms)**.

Testuoti failai:

- `studentai_10000000_K6.txt`
- `studentai_1000000_K6.txt`
- `studentai_100000_K6.txt`
- `studentai_10000_K6.txt`
- `studentai_1000_K6.txt`
- `studentai_1000_K7.txt`

---

# BENDRI LAIKAI – `std::vector`

## **Strategija 1 – `partition_copy`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 46606 | = ~46 sekundėx
| studentai_1000000_K6.txt  | 1 000 000  | 4465 |
| studentai_100000_K6.txt   | 100 000    | 552 |
| studentai_10000_K6.txt    | 10 000     | 67 |
| studentai_1000_K6.txt     | 1 000      | 25 |
| studentai_1000_K7.txt     | 1 000      | 20 |

---

## **Strategija 2 – `remove_if`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 53738 |~ 53 sekundės
| studentai_1000000_K6.txt  | 1 000 000  | 5340 |
| studentai_100000_K6.txt   | 100 000    | 781 |
| studentai_10000_K6.txt    | 10 000     | 53 |
| studentai_1000_K6.txt     | 1 000      | 10 |
| studentai_1000_K7.txt     | 1 000      | 11 |

---

## **Strategija 3 – `partition`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 51970 | ~ 51 sekundė
| studentai_1000000_K6.txt  | 1 000 000  | 5540 |
| studentai_100000_K6.txt   | 100 000    | 574 |
| studentai_10000_K6.txt    | 10 000     | 44 |
| studentai_1000_K6.txt     | 1 000      | 18 |
| studentai_1000_K7.txt     | 1 000      | 17 |

---

# BENDRI LAIKAI – `std::list`

## **Strategija 1 – `partition_copy`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 50180 | ~ 50 sekundžių
| studentai_1000000_K6.txt  | 1 000 000  | 5503 |
| studentai_100000_K6.txt   | 100 000    | 501 |
| studentai_10000_K6.txt    | 10 000     | 51 |
| studentai_1000_K6.txt     | 1 000      | 16 |
| studentai_1000_K7.txt     | 1 000      | 16 |

---

## **Strategija 2 – `remove_if`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 53145 | ~ 53 sekundės
| studentai_1000000_K6.txt  | 1 000 000  | 5289 |
| studentai_100000_K6.txt   | 100 000    | 518 |
| studentai_10000_K6.txt    | 10 000     | 59 |
| studentai_1000_K6.txt     | 1 000      | 10 |
| studentai_1000_K7.txt     | 1 000      | 10 |

---

## **Strategija 3 – `partition`**

| Failas | Įrašų kiekis | Laikas (ms) |
|--------|--------------|-------------|
| studentai_10000000_K6.txt | 10 000 000 | 49747 | ~ 49 skeundės
| studentai_1000000_K6.txt  | 1 000 000  | 4892 |
| studentai_100000_K6.txt   | 100 000    | 521 |
| studentai_10000_K6.txt    | 10 000     | 51 |
| studentai_1000_K6.txt     | 1 000      | 19 |
| studentai_1000_K7.txt     | 1 000      | 14 |

---

# Išvados

### 1. Greičiausias bendras variantas (didžiausi failai)

| Konteineris | Strategija | Laikas |
|-------------|------------|--------|
| `std::vector` | **partition_copy** | **46606 ms** |
| `std::list`   | **partition** | **49747 ms** |

### 2. `std::vector` yra greitesnis už `std::list` dideliems failams
Dėl nuoseklios atminties (`cache locality`) ir spartesnio rikiavimo.

### 3. Mažiems failams strategijos nesiskiria
Kai įrašų < 10 000 — visi variantai veikia labai greitai (10–70 ms).




### VISI KONSOLES REZULTATAI PASIRINKUS BENCHMARK

Rasti failai:

- .\studentai_10000000_K6.txt
- .\studentai_1000000_K6.txt
- .\studentai_100000_K6.txt
- .\studentai_10000_K6.txt
- .\studentai_1000_K6.txt
- .\studentai_1000_K7.txt

========================================
Failas: .\studentai_10000000_K6.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 27951 ms
Skaidymas: 827 ms
Rikiavimas: 7295 ms
Rasymas: 10533 ms
Is viso: 46606 ms
Pirmo studento atminties adresas: 0000021F6FB35060

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 34176 ms
Skaidymas: 743 ms
Rikiavimas: 7996 ms
Rasymas: 10823 ms
Is viso: 53738 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 33068 ms
Skaidymas: 727 ms
Rikiavimas: 7522 ms
Rasymas: 10653 ms
Is viso: 51970 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 34079 ms
Skaidymas: 1507 ms
Rikiavimas: 3200 ms
Rasymas: 11394 ms
Is viso: 50180 ms
Pirmo studento atminties adresas: 0000021F1E4536D0

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 36262 ms
Skaidymas: 1781 ms
Rikiavimas: 2950 ms
Rasymas: 12152 ms
Is viso: 53145 ms
Pirmo studento atminties adresas: 0000021F252FDB70

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 34618 ms
Skaidymas: 154 ms
Rikiavimas: 3189 ms
Rasymas: 11786 ms
Is viso: 49747 ms

========================================
Failas: .\studentai_1000000_K6.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 2759 ms
Skaidymas: 63 ms
Rikiavimas: 506 ms
Rasymas: 1137 ms
Is viso: 4465 ms
Pirmo studento atminties adresas: 0000021F7BBA5060

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 3356 ms
Skaidymas: 66 ms
Rikiavimas: 634 ms
Rasymas: 1284 ms
Is viso: 5340 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 3525 ms
Skaidymas: 65 ms
Rikiavimas: 668 ms
Rasymas: 1282 ms
Is viso: 5540 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3738 ms
Skaidymas: 140 ms
Rikiavimas: 234 ms
Rasymas: 1391 ms
Is viso: 5503 ms
Pirmo studento atminties adresas: 0000021F28626600

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3636 ms
Skaidymas: 158 ms
Rikiavimas: 228 ms
Rasymas: 1267 ms
Is viso: 5289 ms
Pirmo studento atminties adresas: 0000021F6CDAB1F0

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3411 ms
Skaidymas: 14 ms
Rikiavimas: 253 ms
Rasymas: 1214 ms
Is viso: 4892 ms

========================================
Failas: .\studentai_100000_K6.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 346 ms
Skaidymas: 7 ms
Rikiavimas: 65 ms
Rasymas: 134 ms
Is viso: 552 ms
Pirmo studento atminties adresas: 0000021F75F91060

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 545 ms
Skaidymas: 9 ms
Rikiavimas: 81 ms
Rasymas: 146 ms
Is viso: 781 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 388 ms
Skaidymas: 6 ms
Rikiavimas: 51 ms
Rasymas: 129 ms
Is viso: 574 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 351 ms
Skaidymas: 21 ms
Rikiavimas: 19 ms
Rasymas: 110 ms
Is viso: 501 ms
Pirmo studento atminties adresas: 0000021F9ABDC7F0

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 349 ms
Skaidymas: 10 ms
Rikiavimas: 14 ms
Rasymas: 145 ms
Is viso: 518 ms
Pirmo studento atminties adresas: 0000021F9ABDCB70

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 370 ms
Skaidymas: 1 ms
Rikiavimas: 12 ms
Rasymas: 138 ms
Is viso: 521 ms

========================================
Failas: .\studentai_10000_K6.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 42 ms
Skaidymas: 0 ms
Rikiavimas: 2 ms
Rasymas: 23 ms
Is viso: 67 ms
Pirmo studento atminties adresas: 0000021F87CAF020

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 31 ms
Skaidymas: 0 ms
Rikiavimas: 2 ms
Rasymas: 20 ms
Is viso: 53 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 27 ms
Skaidymas: 0 ms
Rikiavimas: 2 ms
Rasymas: 15 ms
Is viso: 44 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 33 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 18 ms
Is viso: 51 ms
Pirmo studento atminties adresas: 0000021F8BC6B1F0

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 41 ms
Skaidymas: 1 ms
Rikiavimas: 0 ms
Rasymas: 17 ms
Is viso: 59 ms
Pirmo studento atminties adresas: 0000021F8BC6BDF0

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 34 ms
Skaidymas: 0 ms
Rikiavimas: 1 ms
Rasymas: 16 ms
Is viso: 51 ms

========================================
Failas: .\studentai_1000_K6.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 21 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 4 ms
Is viso: 25 ms
Pirmo studento atminties adresas: 0000021F87CAF020

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 2 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 8 ms
Is viso: 10 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 15 ms
Is viso: 18 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 4 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 12 ms
Is viso: 16 ms
Pirmo studento atminties adresas: 0000021F9ABDC770

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 4 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 6 ms
Is viso: 10 ms
Pirmo studento atminties adresas: 0000021F9ABDCDF0

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 2 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 17 ms
Is viso: 19 ms

========================================
Failas: .\studentai_1000_K7.txt

---

Konteineris: std::vector

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 16 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 4 ms
Is viso: 20 ms
Pirmo studento atminties adresas: 0000021F87CAF020

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 8 ms
Is viso: 11 ms

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (vector) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 14 ms
Is viso: 17 ms

---

Konteineris: std::list

## [Strategija 1 (partition_copy)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 13 ms
Is viso: 16 ms
Pirmo studento atminties adresas: 0000021F9ABDC370

## [Strategija 2 (remove_if)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 7 ms
Is viso: 10 ms
Pirmo studento atminties adresas: 0000021F9ABDCDF0

## [Strategija 3 (partition)]
Rezultatai issaugoti faile: vargsiukai.txt
Rezultatai issaugoti faile: kietiakiai.txt
=== v0.3 (list) ===
Skaitymas: 3 ms
Skaidymas: 0 ms
Rikiavimas: 0 ms
Rasymas: 11 ms
Is viso: 14 ms

Visi benchmark testai baigti.