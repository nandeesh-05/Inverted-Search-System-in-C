# Inverted Search System in C

## 📌 Description

Developed an Inverted Search system in C that indexes words from multiple text files using a hash table and linked lists. The system enables fast keyword-based searching by avoiding repeated file scanning, similar to real-world search engine indexing.

## 🎯 Key Highlights

* Indexes words from multiple text files
* Uses **hash tables** for faster search and better time complexity
* Linked lists used to handle collisions and word occurrences
* Significantly improves search performance compared to linear file scanning
* Menu-driven and command-line based execution

## 🛠️ Technologies Used

* Programming Language: C
* Data Structures: Hash Table, Linked List
* Concepts: File Handling, Algorithm Design, Search Optimization
* Build Tool: Makefile

## ▶️ How to Compile and Run

Using Makefile:

```bash
make
./inverted_search
```

## 📌 Functionalities Implemented

* Create database (index words from files)
* Update database with new files
* Display database contents
* Search for a word across indexed files
* Save database to file for reuse

## ⚙️ Working Principle

The system parses input text files and stores each word in a hash table. Each hash index maintains a linked list containing file names and word frequencies. This structure reduces search time complexity and allows fast retrieval of word occurrences.

## 📚 Skills Demonstrated

* C Programming
* Hash Table Implementation
* Linked List Operations
* File Handling
* Search Optimization
* Algorithm Development
* Command-Line Argument Handling
* Build Automation using Makefile

