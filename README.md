# Word Puzzle Game
 - Word Quest is a competitive multiplayer word game coded in C++ that tests players' vocabulary and strategic thinking in a crossword puzzle format.
 - The game supports up to four players, each with a unique username and score, competing in real-time to answer a series of word-based questions.
 - Players must answer within a 10-second time limit and have the option to use hints, which come with a score penalty, adding a layer of strategy to the game.

## Features

**Multithreading**: The game leverages the power of multithreading using POSIX threads (pthreads) to manage the turns of multiple players concurrently.

**Mutex Locks**: To ensure turn synchronization and prevent race conditions, mutex locks are employed. These locks are critical for managing shared resources, such as the game board and player scores.

**Turn Synchronization**: The game logic is designed to handle one active player at a time, with each player's turn being processed sequentially. This is achieved through careful thread management and synchronization mechanisms.

**Score Management**: The game maintains a dynamic scoring system that updates player scores in real-time, reflecting the points earned for correct answers and penalties for incorrect attempts or hint usage.

**File Handling**: Player information and scores are persistently stored and managed using file I/O operations, allowing for game state retrieval and updates.

## Tools/Technologies Used

 - C++
 - OOPS
 - VS Code

## Screenshots

![Screenshot 2024-03-19 191438](https://github.com/yoshitha10/WordPuzzle-Game/assets/137447815/52bd11d9-a4bf-4001-acae-8f68480e65ff)
![Screenshot 2024-03-19 191507](https://github.com/yoshitha10/WordPuzzle-Game/assets/137447815/2d5deed3-c7ff-40b5-9fe2-e05faac9c74a)
![Screenshot 2024-03-19 191527](https://github.com/yoshitha10/WordPuzzle-Game/assets/137447815/9f8b873f-e173-4174-bfd5-9dcd4c3845a1)
