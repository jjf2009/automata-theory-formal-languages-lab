# 07 — PDA Simulator (Pushdown Automaton)

**Topic:** pushdown automaton · stack · context-free languages  
**Language:** C  

## What this module does

Simulates a PDA with:

- Input alphabet and stack alphabet  
- Transitions that read input (or ε as `$`), match stack top, and push a string  
- Stack visualization during the run  

## Files

| File | Role |
|------|------|
| `pda_simulator.c` | Full interactive PDA |
| `pda_exam_simple.c` | Compact exam-friendly PDA |
| `pda_output.png` | Sample output screenshot |

## Build and run

```bash
gcc -o pda_simulator pda_simulator.c && ./pda_simulator
gcc -o pda_exam_simple pda_exam_simple.c && ./pda_exam_simple
```

## Epsilon convention

In `pda_simulator.c`, **`$`** denotes **ε** for empty input or empty push (see source comments).

## Theory link

[docs/pda.md](../docs/pda.md) · [docs/cfg.md](../docs/cfg.md) · JFLAP PDA: [`../06-cfg-and-jflap/pda.jff`](../06-cfg-and-jflap/pda.jff)
