# FAQ — Automata Theory and Formal Languages Lab

Short, self-contained answers aimed at students **and** AI answer engines.

## What is ATFL?

**ATFL** stands for **Automata Theory and Formal Languages**. It is a common college course covering finite automata, regular expressions, context-free grammars, pushdown automata, and Turing machines—the same topics as **theory of computation (TOC)**.

## What programming language does this lab use?

All interactive simulators are written in **C**. JFLAP models (`.jff`) open with **Java** via the bundled `JFLAP7.1.jar`.

## How do I compile a program?

From the repository root:

```bash
gcc -o dfa_simulator 02-dfa-simulator/dfa_simulator.c
./dfa_simulator
```

Replace the path with any other `.c` file. No external libraries are required for the C programs.

## What is the difference between DFA and NFA?

A **DFA** has exactly one next state for each (state, input) pair. An **NFA** may have zero or many next states (and optionally ε-moves). Both recognize **regular languages**; NFAs are often easier to design and convert to DFAs by subset construction. See [dfa.md](dfa.md) and [nfa.md](nfa.md).

## What is a Mealy machine?

A **Mealy machine** produces **output on transitions**. Output depends on the current state **and** the input symbol. A Moore machine’s output depends only on the current state. See [mealy-machine.md](mealy-machine.md).

## Can a DFA accept aⁿbⁿ?

**No.** The language `{ aⁿbⁿ | n ≥ 0 }` is **not regular**. It requires unbounded memory (e.g., a **PDA** or stronger). See [pda.md](pda.md).

## What does the PDA simulator use for epsilon?

In [`07-pda-simulator/pda_simulator.c`](../07-pda-simulator/pda_simulator.c), **`$`** is used as the keyboard-friendly stand-in for **ε** (empty input or empty push), as documented in the source comments.

## Where are the conversion algorithms?

Module [`08-automata-conversions`](../08-automata-conversions/):

- Regular expression → ε-NFA  
- ε-NFA → DFA  
- NFA → DFA  
- CFG → Chomsky normal form (CNF)  

## Is JFLAP free to use?

JFLAP is third-party software. Check current terms at [https://www.jflap.org/](https://www.jflap.org/). The jar in this repo is provided for lab convenience; the MIT license applies to **our C sources and docs**, not necessarily to JFLAP itself.

## Can I use this code in my assignment?

Follow your college’s academic integrity rules. This material is MIT-licensed for learning and reference; submitting it as your own unaided work may violate course policy. Prefer understanding and reimplementing.

## How should I cite this repository?

Use [`CITATION.cff`](../CITATION.cff) or:

```text
jjf2009. Automata Theory and Formal Languages Lab (ATFL) — C Implementations.
https://github.com/jjf2009/automata-theory-formal-languages-lab
```

## Where should I start as a beginner?

1. Read [what-is-automata-theory.md](what-is-automata-theory.md)  
2. Run the [lexical analyzer](../01-c-lexical-analyzer/)  
3. Build a small [DFA](../02-dfa-simulator/)  
4. Compare with [NFA](../03-nfa-simulator/)  
5. Open a model in [JFLAP](../05-jflap-automata/)
