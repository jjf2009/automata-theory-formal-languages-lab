# Nondeterministic Finite Automaton (NFA)

A **nondeterministic finite automaton (NFA)** is a finite-state machine that may have **multiple** possible next states for the same input symbol, or transitions on the empty string **ε**. A string is accepted if **at least one** computation path ends in an accepting state.

## Formal definition

An NFA is a 5-tuple **M = (Q, Σ, δ, q₀, F)** where:

- **Q** — finite set of states  
- **Σ** — input alphabet  
- **δ : Q × (Σ ∪ {ε}) → 2^Q** — transition function returning a **set** of states  
- **q₀ ∈ Q** — start state  
- **F ⊆ Q** — accepting states  

## Why NFAs are useful

- **Easier design** for many patterns (optional symbols, unions, “ends with”).
- **Thompson’s construction** builds an ε-NFA from a regular expression.
- Equivalence: every NFA can be converted to a DFA via **subset construction** (powersets of Q).

## How simulation works (intuition)

Instead of one current state, the simulator keeps a **set of active states**. On reading symbol *a*, replace the set with the union of all δ(q, a) for q in the set. For ε-NFAs, close under ε-transitions after each step.

## Implementation in this repository

| File | Description |
|------|-------------|
| [`03-nfa-simulator/nfa_simulator.c`](../03-nfa-simulator/nfa_simulator.c) | Full interactive NFA with multi-target transitions |
| [`03-nfa-simulator/nfa_exam_simple.c`](../03-nfa-simulator/nfa_exam_simple.c) | Compact exam-style NFA |
| [`05-jflap-automata/nfa.jff`](../05-jflap-automata/nfa.jff) | Visual NFA for JFLAP |
| [`08-automata-conversions/nfa_to_dfa.c`](../08-automata-conversions/nfa_to_dfa.c) | NFA → DFA conversion |
| [`08-automata-conversions/enfa_to_dfa.c`](../08-automata-conversions/enfa_to_dfa.c) | ε-NFA → DFA conversion |
| [`08-automata-conversions/regex_to_enfa.c`](../08-automata-conversions/regex_to_enfa.c) | Regex → ε-NFA |

### Compile and run

```bash
gcc -o nfa_simulator 03-nfa-simulator/nfa_simulator.c
./nfa_simulator
```

## Related docs

[DFA](dfa.md) · [CFG](cfg.md) · [FAQ](faq.md)
