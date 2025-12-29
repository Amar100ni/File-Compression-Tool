# File Compression Tool (C++)

A performance-driven, modular file compression system built in C++ to implement, analyze, and compare lossless compression algorithms from the ground up.

This project focuses on **algorithm design**, **systems programming**, and **performance analysis**, rather than relying on existing compression libraries.

---

## This Project

- Implements real compression algorithms instead of using wrappers
- Measures actual runtime and compression efficiency
- Designed with clean, extensible architecture
- Built incrementally with a clear roadmap and engineering intent

This project demonstrates the ability to **translate theoretical algorithms into production-style systems code**.

---

## Key Capabilities

- Lossless file compression and decompression
- Multiple compression algorithms
  - Huffman Coding
  - Run-Length Encoding (RLE)
- Automatic calculation of:
  - Compression ratio
  - Compression time
  - Decompression time
- Modular design allowing easy addition of new algorithms
- Support for multiple file types
- Clean separation between algorithm logic and application flow

---

## Implemented Algorithms

### Huffman Coding
- Greedy, optimal prefix-code compression algorithm
- Built using frequency analysis, priority queues, and binary trees
- Demonstrates strong application of DAA concepts and data structures
- Effective for general-purpose text and binary data

### Run-Length Encoding (RLE)
- Encodes consecutive repeating symbols
- Highlights best-case vs worst-case algorithm behavior
- Useful for understanding data-dependent performance tradeoffs

---

## Performance Analysis

The tool captures and reports:
- Original file size
- Compressed file size
- Compression ratio
- Compression time
- Decompression time

This enables **empirical comparison** of algorithms under different input conditions, not just theoretical analysis.

---

## Architecture Overview


The architecture is designed to:
- Keep algorithms independent of UI and I/O
- Support easy scalability (new algorithms, GUI, reports)
- Maintain readability and testability

---

## Engineering Focus

- Clean C++ design
- Strong use of data structures (heaps, trees, maps)
- Algorithmic efficiency and tradeoff analysis
- File I/O handling and performance measurement
- Incremental development with future extensibility in mind

---

## Planned Enhancements

- Additional algorithms (LZ77, LZW)
- Batch compression support
- Compression history and logging
- Optional encryption layer
- GUI interface
- Exportable performance reports and graphs

---

## Technologies

- **Language:** C++(Qt for app)
- **Concepts:** Greedy Algorithms, Trees, Heaps, File I/O, Performance Metrics
- **Focus Areas:** Algorithms, Systems Programming, Performance Engineering

---

## Contributions

Contributions, suggestions, and improvements are welcome.

If you are interested in:
- Adding new compression algorithms (e.g., LZ77, LZW)
- Improving performance or memory usage
- Enhancing documentation or test coverage
- Extending the project with visualization, reports, or a GUI

Feel free to:
1. Fork the repository
2. Create a new feature branch
3. Commit your changes with clear messages
4. Open a pull request describing your changes

This project is primarily educational, but it is designed with clean architecture and extensibility in mind, making it a good foundation for collaborative experimentation and learning.


