# 02 — DFA Simulator (Deterministic Finite Automaton)

**Topic:** DFA · regular languages · transition tables  
**Language:** C  

## What this module does

Builds a DFA from user input (states, alphabet, start state, final states, δ) and processes strings for acceptance.

## Files

| File | Role |
|------|------|
| `dfa_simulator.c` | Full lab program: prints M = (Q, Σ, δ, q₀, F) and transition table |
| `dfa_exam_simple.c` | Compact exam-friendly version |

## Build and run

```bash
gcc -o dfa_simulator dfa_simulator.c && ./dfa_simulator
# or
gcc -o dfa_exam_simple dfa_exam_simple.c && ./dfa_exam_simple
```

## Theory link

A DFA is **M = (Q, Σ, δ, q₀, F)** with **δ : Q × Σ → Q**. See [docs/dfa.md](../docs/dfa.md).

## Related modules

- [03 NFA simulator](../03-nfa-simulator/)  
- [08 NFA→DFA conversion](../08-automata-conversions/)  
- [05 JFLAP DFA](../05-jflap-automata/)  
