## Small C++ Projects

### Overview

This repository collects dozens of self-contained console applications written in modern C++. Each source file focuses on a single topic—from fundamentals such as input validation, functions, and storage classes, to data structures, algorithms, media processing, and small games. The projects are intentionally lightweight so you can compile and run any program in isolation while exploring different techniques and idioms.

### Getting Started

- **Prerequisites:** A C++17-compliant toolchain (e.g., GCC, Clang, or Microsoft Visual C++). The examples were primarily tested with GCC/Clang, but they rely only on the standard library and the headers in this repository.
- **Build one program:**
	1. Open a terminal in the repository root.
	2. Compile the desired source file and include the `headers/` directory, for example:
     
		 ```powershell
		 g++ -std=c++17 -I headers swap_values.cpp -o swap_values.exe
		 ```
	3. Run the produced executable. Programs that process external data (BMPs, WAVs, dictionaries, etc.) expect the supporting assets to live alongside the executable or to be referenced by path at runtime.
- **Windows users:** You can substitute `g++` with the compiler installed via MinGW, MSYS2, or Visual Studio's `cl.exe`. Make sure any required input files (such as `*.bmp`, `*.wav`, or dictionary text files) are present before execution.

### Shared Utilities

Several programs build on common helper headers under `headers/`:

- `basic_functions.h` — templated input helpers with validation and utility routines for dynamic memory management.
- `bmp.h` — packed structs for reading and writing 24-bit BMP files.
- `wav.h` — WAV header definitions for manipulating PCM audio metadata and samples.
- `dictionary.h` — a hash-table-based word dictionary with load/check/unload helpers used by the spelling and word-game exercises.

Include these headers only when needed; each executable pulls in its dependencies independently, so there is no central build system to maintain.

### Program Catalog

#### Basics & Console Interaction
| Program | Summary |
| --- | --- |
| `adventure_time.cpp` | Interactive story that gathers personal info, branches on choices, and ends with a Fibonacci reveal. |
| `average_score.cpp` | Dynamic array of course grades with per-subject echo and average calculation. |
| `calculate_the_half_bill.cpp` | Applies tax and tip to a bill, then divides the total evenly among diners. |
| `calculator_testing.cpp` | Demonstrates division, modulo, casting, and overflow edge cases with formatted output. |
| `contacts.cpp` | Prompts for a contact's name, age, and phone number and prints the entry. |
| `hello.cpp` | Minimal hello world example showing basic console output. |
| `hours_study.cpp` | Logs weekly study hours into a dynamic array and reports totals or averages. |
| `how_many_coins_to_give_back.cpp` | Greedy coin change calculator that counts quarters, dimes, nickels, and pennies. |
| `max_and_min.cpp` | Finds the maximum, minimum, or both from a user-filled integer array. |
| `population_time_growth.cpp` | Simulates population growth using birth/death rates until a target size is reached. |
| `power_up_array.cpp` | Builds an array of powers of two up to a user-specified length. |
| `temperature.cpp` | Captures city temperatures, sorts them descending, and displays the ranked list. |
| `triangle_check.cpp` | Validates triangle side lengths, detects right triangles, and computes area via Heron’s formula. |
| `snackbar.cpp` | Menu editor for a snack stand supporting add/edit/delete items and total cost calculation. |

#### Strings & Ciphers
| Program | Summary |
| --- | --- |
| `caeser_cipher.cpp` | Command-line Caesar cipher encryptor with robust digit-only key validation. |
| `substitution_cipher.cpp` | Implements monoalphabetic substitution with key validation for unique 26-letter mappings. |
| `swap_characters.cpp` | Leet-speak converter that swaps vowels for numerals within an input string. |
| `cut_string.cpp` | Outputs all substrings of a chosen length from a provided word. |
| `palindrome.cpp` | Checks numeric and string palindromes by reversing digits and characters. |
| `string_to_integer_recursive.cpp` | Recursively converts a numeric string (with optional sign) into an integer. |
| `is_it_in_alphabetical_order.cpp` | Tests whether characters in a string appear in nondecreasing alphabetical order. |
| `scrabble_points_compare.cpp` | Scores two words using Scrabble letter values and announces the winner. |
| `what_grade_is_this_text.cpp` | Calculates Coleman-Liau readability grade from counts of letters, words, and sentences. |

#### Validation & Utility Tools
| Program | Summary |
| --- | --- |
| `command_line_arguments.cpp` | Prints argc and every argv entry to illustrate command-line parsing. |
| `license_plates.cpp` | Reads license plate strings from a file into a vector and prints them. |
| `strong_password.cpp` | Validates password strength and reports missing uppercase, lowercase, digit, symbol, or length. |
| `valid_credit_card.cpp` | Applies the Luhn checksum and reports the detected card brand or invalidity. |
| `validate_file.cpp` | Inspects file signatures to determine whether a binary is PDF, JPG, EXE, or unknown. |
| `return_initials.cpp` | Echoes the initials of two command-line name arguments. |

#### Math & Algorithm Exercises
| Program | Summary |
| --- | --- |
| `binary_search.cpp` | Populates a million-item array and benchmarks binary search on a chosen target. |
| `bitwise_operations.cpp` | Showcases bitwise math for parity, power-of-two tests, swaps, and manual multiplication. |
| `decimal_to_binary.cpp` | Transforms each character of a string into an 8-bit binary representation. |
| `linear_equation.cpp` | Solves a 2×2 linear system with determinants and reports special solution cases. |
| `linear_search.cpp` | Generates a large random array and times linear search for a requested value. |
| `matrix.cpp` | Matrix class supporting input, arithmetic, determinants, adjugates, and inversion helpers. |
| `prime.cpp` | Lists primes within a user-specified range using square-root divisibility checks. |
| `quadratic.cpp` | Quadratic equation helper that inputs coefficients, prints the form, and computes roots. |
| `recursion.cpp` | Computes factorial, Fibonacci, Collatz steps, powers, GCD, and digit divisibility recursively. |
| `sorting.cpp` | Benchmarks bubble, selection, insertion, merge, quick, counting, radix, shell, and heap sorts. |
| `complex_numbers.cpp` | Demonstrates complex-number addition via a simple class and command-line inputs. |
| `prefix_infix_postfix.cpp` | Menu-driven converter among infix, prefix, and postfix forms using stack logic. |
| `printing_hashtag_grids.cpp` | Generates ASCII grids, pyramids, and diamond patterns for a chosen size. |

#### Data Structures & Collections
| Program | Summary |
| --- | --- |
| `data_structures.cpp` | Reference implementations for linked lists with insert, delete, find, and sort routines. |
| `singly_linked_list.cpp` | Interactive singly linked list supporting prepend, append, update, and deletion by key. |
| `doubly_linked_list.cpp` | Doubly linked list toolkit with bidirectional traversal and extensive mutation options. |
| `circular_linked_list.cpp` | Template-based circular linked list with sorted insert, delete, and update helpers. |
| `stack_array.cpp` | Array-backed stack exposing push, pop, peek, change, count, and display operations. |
| `stack_linked_list.cpp` | Pointer-based stack that demonstrates dynamic push/pop and traversal. |
| `queue_array.cpp` | Array implementation of a FIFO queue with enqueue, dequeue, peek, and count logic. |
| `queue_linked_list.cpp` | Linked-list queue offering dynamic enqueue/dequeue and introspection utilities. |
| `circular_queue_array.cpp` | Circular array queue showcasing wraparound indexing and overflow/underflow guards. |
| `circular_queue_linked_list.cpp` | Circular linked-list queue with insert, delete, and peek operations. |
| `heap_array.cpp` | Array-based min-heap featuring insert, search, heapify, extraction, and heap sort. |
| `hash_table.cpp` | Chained hash table template with configurable hashing, collision handling, and CRUD actions. |
| `tree.cpp` | Comprehensive BST/AVL demo with traversals, balancing, visualization, and search utilities. |
| `graph.cpp` | Graph adjacency-list implementation supporting vertex/edge management and traversal algorithms. |
| `tries.cpp` | Trie structure enabling insert, search, delete, and visualization of string keys. |
| `dog_names.cpp` | Trie-backed dictionary that loads dog names and checks membership interactively. |

#### Object-Oriented & Language Features
| Program | Summary |
| --- | --- |
| `ambiguity.cpp` | Demonstrates virtual inheritance and scope resolution to resolve diamond ambiguity. |
| `classes.cpp` | Introduces class syntax, constructors, and encapsulation basics with simple examples. |
| `functions_can_be_friends.cpp` | Uses friend functions to access private members while computing physics examples. |
| `operator_overloading.cpp` | Shows how to overload operators for custom types and compare object behavior. |
| `virtual_functions.cpp` | Highlights dynamic dispatch through base pointers and overridden virtual methods. |
| `pure_virtual_functions.cpp` | Builds an abstract base class with pure virtual functions and derived overrides. |
| `lambdas.cpp` | Explores function pointers, captures, and higher-order utilities using C++ lambdas. |
| `macros.cpp` | Demonstrates preprocessor macros, conditional compilation, and built-in metadata tokens. |
| `storage_classes.cpp` | Explains automatic, extern, static, register, and mutable storage classes with examples. |
| `enumeration.cpp` | Introduces enumerations and scoped enums with illustrative use cases. |
| `exception_handling.cpp` | Walks through try/catch scenarios, custom exceptions, and error-reporting patterns. |
| `unions.cpp` | Compares unions versus structs and shows how shared storage behaves. |
| `dynamic_memory_allocation.cpp` | Contrasts C and C++ dynamic allocation styles and proper cleanup. |
| `pointers_addresses_references.cpp` | Visualizes references, pointers, pointer arithmetic, and manual memory management. |
| `swap_values.cpp` | Swaps integers via pointers and references while reinforcing argument passing semantics. |

#### File I/O & Media Processing
| Program | Summary |
| --- | --- |
| `bank.cpp` | Binary file-backed banking system supporting account CRUD, deposits, withdrawals, and reports. |
| `change_pixel_color_of_bmp.cpp` | Reads a 24-bit BMP, recolors selected pixels, and writes a new bitmap. |
| `change_volume_of_wav.cpp` | Scales PCM samples in a WAV file to adjust playback volume. |
| `flip_bmp_images.cpp` | Rewrites BMP headers to vertically flip an image while preserving pixel data. |
| `filter.cpp` | Applies grayscale, sepia, reflect, blur, and edge filters to BMP images. |
| `reverse_wav_audio.cpp` | Reverses WAV audio by iterating samples from the end toward the beginning. |
| `recover_jpg_images.cpp` | Recovers JPEGs from a forensic image by scanning 512-byte blocks for signatures. |
| `read_and_write_to_files.cpp` | Manages a contacts file with append, delete, and display across vector and arrays. |
| `create.cpp` | Utility that creates an empty file with the provided name. |

#### Games, Simulations & Problem Solving
| Program | Summary |
| --- | --- |
| `blood.cpp` | Recursively builds a family tree and prints simulated blood types across generations. |
| `candidates.cpp` | Stores candidate names and vote counts in a structure array and prints the roster. |
| `instant_runoff.cpp` | Simulates instant-runoff elections with ranked ballots and elimination rounds. |
| `plurality_vote.cpp` | Tallies plurality election votes and announces the highest scoring candidates. |
| `tideman_vote.cpp` | Implements the Tideman ranked-choice algorithm with pair locking and cycle detection. |
| `speller.cpp` | Spell-checker that loads a dictionary into a hash table and reports misspelled words. |
| `wordle.cpp` | Console Wordle clone with adjustable word length, dictionary validation, and colored feedback. |