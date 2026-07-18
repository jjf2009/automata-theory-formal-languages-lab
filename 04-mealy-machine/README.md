# 04 — Mealy Machine Simulator

**Topic:** Mealy machine · finite-state transducer · output on transitions  
**Language:** C  

## What this module does

Defines next-state function **δ** and output function **λ**, then produces an **output string** while processing the input.

## Files

| File | Role |
|------|------|
| `mealy_machine.c` | Full table + menu-driven processor |
| `mealy_exam_simple.c` | Compact exam-friendly Mealy |

## Build and run

```bash
gcc -o mealy_machine mealy_machine.c && ./mealy_machine
gcc -o mealy_exam_simple mealy_exam_simple.c && ./mealy_exam_simple
```

## Theory link

Mealy: output depends on **state and input**. See [docs/mealy-machine.md](../docs/mealy-machine.md).
