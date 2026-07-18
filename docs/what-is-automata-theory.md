# What is automata theory?

**Automata theory** is the branch of computer science that studies abstract machines (automata) and the problems they can solve. Together with **formal languages**, it forms the core of **theory of computation (TOC)** and college courses often titled **ATFL** (Automata Theory and Formal Languages).

In one sentence: automata theory asks *what kinds of computation can different machine models perform, and which languages can those machines recognize?*

## Why it matters

- **Compilers and interpreters** use finite automata for lexical analysis (tokens, identifiers, numbers).
- **Protocol and hardware design** use finite-state machines for controllers and network states.
- **Natural language and XML/JSON tools** rely on context-free grammars and parsers.
- **Complexity and limits of computing** start from Turing machines and decidability.

## The Chomsky hierarchy (quick map)

| Level | Language class | Typical machine | Examples |
|-------|----------------|-----------------|----------|
| Type-3 | Regular | DFA / NFA | keywords, simple patterns, regex |
| Type-2 | Context-free | PDA | nested parentheses, many programming constructs |
| Type-1 | Context-sensitive | Linear-bounded automaton | some natural-language fragments |
| Type-0 | Recursively enumerable | Turing machine | general algorithms |

## What this repository implements

This ATFL lab provides **working C programs** for:

1. Lexical classification (keywords / numbers / identifiers)
2. DFA and NFA simulation
3. Mealy machines (output on transitions)
4. CFG derivation
5. PDA simulation
6. Conversions: regex → ε-NFA, NFA → DFA, ε-NFA → DFA, CFG → CNF
7. JFLAP visual models for DFA, NFA, CFG, PDA, and Turing machines

## Related terms students search for

automata theory definition, formal languages, theory of computation notes, ATFL lab programs in C, finite automata, DFA vs NFA, pushdown automata, context-free grammar, Turing machine, compiler design finite automata

## Next reading in this repo

- [DFA](dfa.md) · [NFA](nfa.md) · [Mealy machine](mealy-machine.md) · [CFG](cfg.md) · [PDA](pda.md) · [Turing machine](turing-machine.md) · [FAQ](faq.md)
