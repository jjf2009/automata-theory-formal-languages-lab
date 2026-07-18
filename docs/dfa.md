# Deterministic Finite Automaton (DFA)

A **deterministic finite automaton (DFA)** is a finite-state machine that accepts or rejects strings over an alphabet. From any state and input symbol, the machine has **exactly one** next state.

## Formal definition

A DFA is a 5-tuple **M = (Q, Σ, δ, q₀, F)** where:

- **Q** — finite set of states  
- **Σ** — input alphabet  
- **δ : Q × Σ → Q** — transition function (total, single-valued)  
- **q₀ ∈ Q** — start state  
- **F ⊆ Q** — set of accepting (final) states  

A string *w* is **accepted** if, after reading *w* from *q₀*, the machine ends in a state in *F*.

## Key properties (citable facts)

- Every regular language has a DFA.
- DFA and NFA recognize the **same** class of languages (regular languages); DFAs may need more states.
- Subset construction converts an NFA into an equivalent DFA.
- Lexical analyzers in compilers are often implemented as DFAs or optimized automata.

## DFA vs NFA (one glance)

| Feature | DFA | NFA |
|---------|-----|-----|
| Next states per (q, a) | Exactly 1 | 0 or more |
| ε-transitions | No | Allowed (ε-NFA) |
| Implementation | Simple loop | Set of active states |
| State count | Often larger | Can be smaller |

## Implementation in this repository

| File | Description |
|------|-------------|
| [`02-dfa-simulator/dfa_simulator.c`](../02-dfa-simulator/dfa_simulator.c) | Interactive DFA: read states, alphabet, δ, finals; process strings |
| [`02-dfa-simulator/dfa_exam_simple.c`](../02-dfa-simulator/dfa_exam_simple.c) | Compact exam-style DFA program |
| [`05-jflap-automata/dfa.jff`](../05-jflap-automata/dfa.jff) | Visual DFA for JFLAP |

### Compile and run

```bash
gcc -o dfa_simulator 02-dfa-simulator/dfa_simulator.c
./dfa_simulator
```

## Typical lab exercise

1. Design a DFA that accepts strings over `{0,1}` ending with `01`.  
2. Enter states and the transition table into the simulator.  
3. Test accepting and rejecting strings (`101`, `1101`, `0`, `010`).

## Related docs

[NFA](nfa.md) · [Automata theory overview](what-is-automata-theory.md) · [Conversions](../08-automata-conversions/)
