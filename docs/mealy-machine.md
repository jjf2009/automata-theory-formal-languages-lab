# Mealy machine

A **Mealy machine** is a finite-state **transducer**: it not only changes state on input, it also produces **output on transitions**. The output depends on the **current state and the input symbol**.

## Formal definition

A Mealy machine is typically **M = (Q, Σ, Δ, δ, λ, q₀)** where:

- **Q** — states  
- **Σ** — input alphabet  
- **Δ** — output alphabet  
- **δ : Q × Σ → Q** — next-state function  
- **λ : Q × Σ → Δ** — output function (edge-labeled output)  
- **q₀** — start state  

Contrast with a **Moore machine**, where output is a function of the **state alone** (λ : Q → Δ).

## When Mealy machines appear

- Digital circuit controllers with input-conditioned outputs  
- Protocol encoders/decoders  
- Simple stream transformers (e.g., 1’s complement bit-by-bit with carry-like state)  
- ATFL lab exams comparing Mealy vs Moore  

## Implementation in this repository

| File | Description |
|------|-------------|
| [`04-mealy-machine/mealy_machine.c`](../04-mealy-machine/mealy_machine.c) | Interactive Mealy: define δ and λ, process strings |
| [`04-mealy-machine/mealy_exam_simple.c`](../04-mealy-machine/mealy_exam_simple.c) | Compact exam-style Mealy program |

### Compile and run

```bash
gcc -o mealy_machine 04-mealy-machine/mealy_machine.c
./mealy_machine
```

## Mealy vs Moore (exam table)

| Aspect | Mealy | Moore |
|--------|-------|-------|
| Output depends on | State **and** input | State only |
| Output timing | On transition | On entering state |
| Diagram labels | Edges: *a / x* | States: output value |
| Often fewer states | Yes | Sometimes more |

## Related docs

[DFA](dfa.md) · [What is automata theory?](what-is-automata-theory.md)
