# 03 — NFA Simulator (Nondeterministic Finite Automaton)

**Topic:** NFA · multi-state transitions · regular languages  
**Language:** C  

## What this module does

Defines an NFA where each (state, symbol) can lead to a **set** of next states, then simulates input by tracking the active set of states.

## Files

| File | Role |
|------|------|
| `nfa_simulator.c` | Full interactive NFA with set printing |
| `nfa_exam_simple.c` | Compact exam-friendly NFA |

## Build and run

```bash
gcc -o nfa_simulator nfa_simulator.c && ./nfa_simulator
gcc -o nfa_exam_simple nfa_exam_simple.c && ./nfa_exam_simple
```

## Theory link

NFA transition function maps to **2^Q**. Acceptance if any active state is final. See [docs/nfa.md](../docs/nfa.md).

## Related modules

- [02 DFA simulator](../02-dfa-simulator/)  
- [08 automata conversions](../08-automata-conversions/)  
