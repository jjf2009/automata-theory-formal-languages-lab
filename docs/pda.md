# Pushdown Automaton (PDA)

A **pushdown automaton (PDA)** is a finite automaton equipped with a **stack**. The extra memory lets PDAs recognize many **context-free languages**—for example, `{ aⁿbⁿ | n ≥ 0 }`—that no DFA or NFA can accept.

## Formal definition (informal)

A PDA has:

- A finite set of **states**  
- An **input alphabet** Σ  
- A **stack alphabet** Γ  
- A transition relation that, given state, input (or ε), and stack top, can move to a new state and **replace** the stack top by a string of stack symbols  
- A start state, initial stack symbol, and accepting states (or empty-stack acceptance, depending on the presentation)

## Acceptance modes (course variants)

1. **Final state** — after consuming the input, the control state is accepting (stack may be nonempty).  
2. **Empty stack** — after consuming the input, the stack is empty.  

Many textbooks prove these modes are equivalent in power for nondeterministic PDAs.

## PDA vs DFA (exam snapshot)

| Feature | DFA | PDA |
|---------|-----|-----|
| Memory | Finite states only | Finite states + unbounded stack |
| Languages | Regular | Context-free (NPDAs) |
| Nesting (aⁿbⁿ) | Impossible | Possible |
| Implementation | Single state variable | State + stack ADT |

## Implementation in this repository

| File | Description |
|------|-------------|
| [`07-pda-simulator/pda_simulator.c`](../07-pda-simulator/pda_simulator.c) | Interactive PDA with ε-input (`$`), push/pop, stack print |
| [`07-pda-simulator/pda_exam_simple.c`](../07-pda-simulator/pda_exam_simple.c) | Compact exam-style PDA |
| [`07-pda-simulator/pda_output.png`](../07-pda-simulator/pda_output.png) | Sample run screenshot |
| [`06-cfg-and-jflap/pda.jff`](../06-cfg-and-jflap/pda.jff) | JFLAP PDA model |

### Compile and run

```bash
gcc -o pda_simulator 07-pda-simulator/pda_simulator.c
./pda_simulator
```

In the full simulator, **`$`** denotes ε (epsilon) for input or for “push nothing / pop only” style stack updates—read the program prompts carefully.

## Related docs

[CFG](cfg.md) · [Turing machine](turing-machine.md) · [What is automata theory?](what-is-automata-theory.md)
