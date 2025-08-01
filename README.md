# emax-chess-zero

A lightweight, modular chess engine written in C, utilizing bitboards and optimized alpha-beta pruning for efficient move generation and game tree search.

## Motivation

This project was initiated as a personal deep dive into how chess engines function at the low level. By building every core component from scratch—including move generation, board evaluation, and search—I aimed to:

- Understand how bit-level representations improve performance
- Explore the interaction between data structures and algorithms in real-time decision-making
- Practice clean C programming and systems-level optimization

## Features

- Bitboard-based board representation (using `uint64_t`)
- Legal move generation
- Alpha-beta pruning with increasing-depth search

## Technologies Used

- Language: C
- Concepts: Bitboards, Alpha-Beta Pruning, Branchless Logic
- Tools: GCC, Make, Unix shell

## Author

Ian Yim  
Computer Science & Mathematics Undergraduate  
University of Arizona  
GitHub: https://github.com/ianyimstudent  
LinkedIn: https://www.linkedin.com/in/ian-yim

## License

This project is licensed under the MIT License – see the [LICENSE](./LICENSE) file for details.