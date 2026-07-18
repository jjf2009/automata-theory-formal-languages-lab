# 08 — Automata Conversion Algorithms

**Topic:** regex → ε-NFA · ε-NFA → DFA · NFA → DFA · CFG → CNF  
**Language:** C  

These programs implement standard **theory of computation constructions** used in exams and compiler front-end theory.

## Files

| File | Algorithm | Search keywords |
|------|-----------|-----------------|
| `regex_to_enfa.c` | Regular expression → ε-NFA | Thompson construction, regex to NFA |
| `enfa_to_dfa.c` | ε-NFA → DFA | epsilon closure, subset construction |
| `nfa_to_dfa.c` | NFA → DFA | powerset construction |
| `cfg_to_cnf.c` | CFG → Chomsky normal form | CNF conversion, CYK prep |

## Build and run (examples)

```bash
gcc -o regex_to_enfa regex_to_enfa.c && ./regex_to_enfa
gcc -o enfa_to_dfa enfa_to_dfa.c && ./enfa_to_dfa
gcc -o nfa_to_dfa nfa_to_dfa.c && ./nfa_to_dfa
gcc -o cfg_to_cnf cfg_to_cnf.c && ./cfg_to_cnf
```

## Theory links

- [NFA](../docs/nfa.md) · [DFA](../docs/dfa.md) · [CFG](../docs/cfg.md)  
- Related simulators: [02](../02-dfa-simulator/), [03](../03-nfa-simulator/), [06](../06-cfg-and-jflap/)  
