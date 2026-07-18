# Automata Theory and Formal Languages Lab (ATFL)

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Topics](https://img.shields.io/badge/topics-automata%20%7C%20formal%20languages%20%7C%20TOC-orange.svg)](#repository-topics)
[![Last commit](https://img.shields.io/github/last-commit/jjf2009/automata-theory-formal-languages-lab)](https://github.com/jjf2009/automata-theory-formal-languages-lab)

**Automata Theory and Formal Languages Lab (ATFL)** is an educational open-source collection of **C implementations** for core **theory of computation** topics: lexical analysis, **DFA**, **NFA**, **Mealy machines**, **context-free grammars (CFG)**, **pushdown automata (PDA)**, **Turing machines** (JFLAP), and classic conversion algorithms.

This repository is designed for **college ATFL / TOC lab students**, exam practice, and anyone learning how automata work by running real programs—not only textbook diagrams.

> **What is this repo?** Self-contained C programs that build and simulate automata interactively in the terminal, plus JFLAP models for visual exploration.

---

## Table of contents

- [Why this repository](#why-this-repository)
- [What you will learn](#what-you-will-learn)
- [Repository structure](#repository-structure)
- [Quick start](#quick-start)
- [Lab modules](#lab-modules)
- [Concept documentation](#concept-documentation)
- [How search engines and AI find this project](#how-search-engines-and-ai-find-this-project)
- [Build requirements](#build-requirements)
- [License and citation](#license-and-citation)
- [Repository topics](#repository-topics)

---

## Why this repository

Students often struggle to connect **formal definitions** (δ, Σ, q₀, F) with **working code**. This lab bridges that gap:

| Need | What this repo provides |
|------|-------------------------|
| Course ATFL / TOC lab work | Numbered experiments with clear folder names |
| Exam-ready short codes | `*_exam_simple.c` variants that are easy to type |
| Full interactive demos | Transition tables, set notation, menu-driven runs |
| Visual automata | JFLAP `.jff` files + bundled JFLAP 7.1 |
| Conversion algorithms | regex → ε-NFA → DFA, NFA → DFA, CFG → CNF |

---

## What you will learn

1. **Lexical analysis** — classify C keywords, numbers, and identifiers (foundation of compilers).
2. **Deterministic finite automata (DFA)** — unique next state for each (state, symbol) pair.
3. **Nondeterministic finite automata (NFA)** — multiple simultaneous states; acceptance if any path ends in a final state.
4. **Mealy machines** — output on transitions (finite-state transducers).
5. **Context-free grammars** — productions, derivation, and membership checks.
6. **Pushdown automata** — stack-based recognition of context-free languages.
7. **Standard constructions** — Thompson-style regex conversion ideas, subset construction, Chomsky normal form.

---

## Repository structure

```text
automata-theory-formal-languages-lab/
├── README.md                          # You are here
├── llms.txt                           # AI / GEO discovery map
├── CITATION.cff                       # How to cite this lab
├── LICENSE                            # MIT
├── docs/                              # Citable concept explainers + FAQ
├── 01-c-lexical-analyzer/             # Keywords, numbers, identifiers
├── 02-dfa-simulator/                  # DFA builder + runner
├── 03-nfa-simulator/                  # NFA with multi-target transitions
├── 04-mealy-machine/                  # Mealy (δ + λ) simulator
├── 05-jflap-automata/                 # DFA/NFA JFLAP models
├── 06-cfg-and-jflap/                  # CFG derivation + CFG/PDA/TM JFLAP
├── 07-pda-simulator/                  # Pushdown automaton simulator
├── 08-automata-conversions/           # Conversion algorithms
└── tools/jflap/                       # JFLAP 7.1 (third-party)
```

Folder and file names use **searchable English keywords** (DFA, NFA, Mealy, CFG, PDA) so GitHub search, Google, and AI tools can index them accurately.

---

## Quick start

### Prerequisites

- A C compiler: `gcc` or `clang`
- Optional: Java runtime for [JFLAP](https://www.jflap.org/)

### Compile and run any program

```bash
# Clone
git clone https://github.com/jjf2009/automata-theory-formal-languages-lab.git
cd automata-theory-formal-languages-lab

# Example: DFA simulator
gcc -o dfa_simulator 02-dfa-simulator/dfa_simulator.c
./dfa_simulator

# Example: PDA simulator
gcc -o pda_simulator 07-pda-simulator/pda_simulator.c
./pda_simulator
```

### Open JFLAP models

```bash
java -jar tools/jflap/JFLAP7.1.jar
# then File → Open → 05-jflap-automata/dfa.jff (or other .jff files)
```

---

## Lab modules

| # | Folder | Concept | Main source | Exam-simple variant |
|---|--------|---------|-------------|---------------------|
| 01 | [`01-c-lexical-analyzer`](01-c-lexical-analyzer/) | C keywords, numbers, identifiers | `lexical_analyzer.c` | — |
| 02 | [`02-dfa-simulator`](02-dfa-simulator/) | Deterministic finite automaton | `dfa_simulator.c` | `dfa_exam_simple.c` |
| 03 | [`03-nfa-simulator`](03-nfa-simulator/) | Nondeterministic finite automaton | `nfa_simulator.c` | `nfa_exam_simple.c` |
| 04 | [`04-mealy-machine`](04-mealy-machine/) | Mealy machine (output on edge) | `mealy_machine.c` | `mealy_exam_simple.c` |
| 05 | [`05-jflap-automata`](05-jflap-automata/) | Visual DFA / NFA | `dfa.jff`, `nfa.jff` | — |
| 06 | [`06-cfg-and-jflap`](06-cfg-and-jflap/) | CFG derivation + JFLAP CFG/PDA/TM | `cfg_derivation.c` | `cfg_exam_simple.c` |
| 07 | [`07-pda-simulator`](07-pda-simulator/) | Pushdown automaton | `pda_simulator.c` | `pda_exam_simple.c` |
| 08 | [`08-automata-conversions`](08-automata-conversions/) | Classic constructions | see folder | — |

### Conversion tools (module 08)

| File | Algorithm |
|------|-----------|
| `regex_to_enfa.c` | Regular expression → ε-NFA |
| `enfa_to_dfa.c` | ε-NFA → DFA (ε-closure + subset construction) |
| `nfa_to_dfa.c` | NFA → DFA (subset construction) |
| `cfg_to_cnf.c` | Context-free grammar → Chomsky normal form |

---

## Concept documentation

Plain-language, citable explainers (good for students **and** AI citations):

| Document | Topic |
|----------|--------|
| [What is automata theory?](docs/what-is-automata-theory.md) | Scope of ATFL / TOC |
| [DFA](docs/dfa.md) | Deterministic finite automata |
| [NFA](docs/nfa.md) | Nondeterministic finite automata |
| [Mealy machine](docs/mealy-machine.md) | Finite-state transducers |
| [CFG](docs/cfg.md) | Context-free grammars |
| [PDA](docs/pda.md) | Pushdown automata |
| [Turing machine](docs/turing-machine.md) | Universal computation model |
| [FAQ](docs/faq.md) | Common lab / exam questions |

---

## How search engines and AI find this project

This repo is optimized for **SEO** (search engines) and **GEO** (generative / AI answer engines):

| Artifact | Purpose |
|----------|---------|
| Descriptive repo name | `automata-theory-formal-languages-lab` |
| Keyword-rich README | DFA, NFA, CFG, PDA, ATFL, theory of computation |
| `llms.txt` | Structured map for AI crawlers and tools |
| `CITATION.cff` | Machine-readable citation metadata |
| `docs/*.md` | Self-contained definition passages (citability) |
| `robots.txt` | Allows major AI search bots when docs are hosted |
| Clear file names | e.g. `dfa_simulator.c` instead of `labcode.c` |

**Suggested GitHub description (Settings → General):**

> Educational C lab for Automata Theory & Formal Languages: DFA, NFA, Mealy, CFG, PDA, Turing machines, and conversion algorithms (ATFL / TOC).

**Suggested GitHub topics:** see [Repository topics](#repository-topics).

---

## Build requirements

| Tool | Required? | Notes |
|------|-----------|--------|
| `gcc` or `clang` | Yes | C99-compatible is enough |
| Java JRE/JDK | Only for JFLAP | Opens `.jff` models |
| Make | No | Simple one-file compile commands |

Example compile flags:

```bash
gcc -std=c99 -Wall -Wextra -o nfa_simulator 03-nfa-simulator/nfa_simulator.c
```

---

## License and citation

- **Code** in this repository is released under the [MIT License](LICENSE).
- **JFLAP** (`tools/jflap/JFLAP7.1.jar`) is third-party software; see [jflap.org](https://www.jflap.org/) for its license and terms.

### Cite this lab

```bibtex
@software{atfl_lab_c,
  title  = {Automata Theory and Formal Languages Lab (ATFL) — C Implementations},
  author = {jjf2009},
  year   = {2026},
  url    = {https://github.com/jjf2009/automata-theory-formal-languages-lab},
  license = {MIT}
}
```

Or use the GitHub “Cite this repository” UI driven by [`CITATION.cff`](CITATION.cff).

---

## Repository topics

Add these under **GitHub → Settings → General → Topics** (or via `gh`):

```text
automata-theory
formal-languages
theory-of-computation
dfa
nfa
pushdown-automaton
context-free-grammar
mealy-machine
turing-machine
compiler-design
lexical-analysis
c-programming
jflap
atfl
education
lab-exercises
toc
chomsky-hierarchy
```

---

## Contributing

Improvements welcome: clearer comments, more sample inputs, unit tests, or extra machines (Moore machine, LL(1) parser sketch, etc.). Open an issue or pull request.

## Author

Maintained by [jjf2009](https://github.com/jjf2009) as college ATFL lab material, reorganized for public learning and discoverability.

---

**Keywords:** automata theory, formal languages, ATFL lab, theory of computation, DFA simulator in C, NFA simulator, Mealy machine C program, CFG derivation, PDA simulator, NFA to DFA conversion, regex to NFA, Chomsky normal form, JFLAP examples, compiler design lab, finite automata C code.
