# 🅿️ Parking Management System (C++)

A console-based vehicle parking management system built in **C++** as a final project for an Algorithms/Programming lab course. The program manages vehicle check-in/check-out, tracks slot occupancy on a 7×10 parking grid, calculates parking fees, and generates daily reports.

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Project Structure](#-project-structure)
- [Core Data & Algorithms](#-core-data--algorithms)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Compiling & Running](#compiling--running)
- [Usage](#-usage)
- [Sample Output](#-sample-output)
- [Known Issues & Roadmap](#-known-issues--roadmap)
- [License](#-license)

## 📖 Overview

This application is a menu-driven, terminal-based system for managing a parking lot with **70 slots** arranged in a 7×10 grid (rows `A`–`G`, columns `1`–`10`). It supports vehicle entry and exit, manual or automatic slot assignment, fee calculation based on parking duration, persistent storage to text files, and daily statistics reporting.

Built as a coursework final project (NIM 123240010 & 123240020), it demonstrates core programming concepts including structs, arrays, pointers, recursion, sorting, file I/O, and time handling in C++.

## ✨ Features

- **Vehicle Check-In** — register plate number, vehicle type, and automatically timestamp entry; prevents duplicate plate registration
- **Slot Assignment** — choose a parking slot manually (e.g. `B5`) or let the system auto-assign the first available slot
- **Vehicle Check-Out** — calculate parking duration and fee (Rp 2,000/hour, rounded up, minimum 1 hour), free the occupied slot, and remove the record from storage
- **Parking Layout View** — visual grid display showing occupied (`X`) vs. empty (` `) slots
- **Vehicle Listing** — display all currently parked vehicles (implemented via pointer arithmetic)
- **Sorting** — sort the active vehicle list alphabetically by plate number (bubble sort)
- **Daily Statistics** — total vehicles served and total revenue for the session, with active vehicle count computed recursively
- **Persistent Storage**
  - `data_parkir.txt` — live record of currently parked vehicles
  - `laporan.txt` — appended daily summary report (date, vehicle count, revenue) on exit

## 🧰 Tech Stack

| Component     | Technology            |
|----------------|------------------------|
| Language       | C++ (C++11 or later)  |
| Standard Library | `<bits/stdc++.h>`, `<fstream>`, `<ctime>` |
| Platform       | Windows (uses `system("cls")` / `system("pause")`) |

## 📁 Project Structure

```
Final_Projek_10_20-main/
├── Project_Parkiran.cpp   # Main program source code
├── laporan.txt            # Daily report log (auto-generated/appended)
└── README.md
```

> Note: `data_parkir.txt` is generated at runtime in the same directory when vehicles check in.

## 🧠 Core Data & Algorithms

| Concept              | Implementation                                                             |
|-----------------------|------------------------------------------------------------------------------|
| Struct                | `Kendaraan` (plate, type, entry time, assigned slot)                       |
| Static array          | `daftarParkir[100]` holds active vehicle records                           |
| 2D array (grid)       | `slot[7][10]` represents the physical parking layout                       |
| Pointer arithmetic    | `tampilkanDenganPointer()` iterates the vehicle list via pointer offsets   |
| Recursion             | `hitungKendaraan()` recursively counts currently parked vehicles           |
| Sorting               | Bubble sort by plate number in `sortKendaraanByPlat()`                     |
| File I/O              | Append/read/rewrite `data_parkir.txt`; append `laporan.txt`                |
| Time handling         | `time_t` / `localtime` / `difftime` for entry/exit timestamps and duration |

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g. **g++** via MinGW on Windows, or any standard C++ toolchain)

### Compiling & Running

```bash
g++ Project_Parkiran.cpp -o parkiran
./parkiran        # Linux/macOS
parkiran.exe       # Windows
```

> ⚠️ The program uses `system("cls")` and `system("pause")`, which are Windows-specific. On Linux/macOS, replace `system("cls")` with `system("clear")` and remove or adapt `system("pause")` to run correctly.

## 🖥️ Usage

Upon running the program, you'll see a menu:

```
====================
||    Parkiran    ||
====================
1. Kendaraan Masuk           (Vehicle Check-In)
2. Kendaraan Keluar          (Vehicle Check-Out)
3. Tampilkan Data Parkir     (Show Parked Vehicles)
4. Tampilkan Slot Parkir     (Show Parking Layout)
5. Statistik & Laporan Harian (Daily Statistics)
6. Urutkan Data Parkir       (Sort by Plate Number)
0. Keluar                    (Exit)
```

On exit (option `0`), you can choose to:
1. Save the daily report to `laporan.txt`, or
2. Delete the `data_parkir.txt` file before quitting

## 📊 Sample Output

```
Layout Slot Parkir (X = terisi):
[X] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]  <== Baris A
[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]  <== Baris B
...

Detail Parkir:
Plat nomor      : B1234XY
Jenis kendaraan : Motor
Slot            : A1
Waktu masuk     : 04-06-2025 10:09:55
Waktu keluar    : 04-06-2025 11:15:20
Durasi parkir   : 1.09 jam
Biaya parkir    : Rp 2000
```

## ⚠️ Known Issues & Roadmap

- [ ] `system("cls")` / `system("pause")` are Windows-only; not portable to Linux/macOS without modification
- [ ] Parking fee, revenue, and vehicle counters reset every run instead of persisting across sessions (only the report log accumulates)
- [ ] No input validation for non-numeric input on the main menu (can cause `cin` failure loops)
- [ ] Fixed-size array (`MAX_KENDARAAN = 100`) could be replaced with a dynamic container (e.g. `std::vector`)
- [ ] Consider using a more efficient sorting algorithm for larger datasets
- [ ] Add unit tests for fee calculation and slot assignment logic

## 📄 License

This project was developed for academic coursework purposes. Feel free to fork and adapt it for learning or educational use.
