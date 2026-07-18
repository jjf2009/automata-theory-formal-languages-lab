# Turing machine

A **Turing machine (TM)** is a theoretical model of computation with a finite control unit and an **infinite tape** that can be read and written while the head moves left or right. It is the standard formalization of “algorithm” and sits at the top of the common undergrad hierarchy (Type-0 languages).

## Why Turing machines matter

- Define what is **computable** vs **undecidable** (e.g., the halting problem).  
- Provide the foundation for **complexity classes** (time/space on TMs).  
- Unify the idea that general-purpose programming languages are equivalent in power to TMs (Church–Turing thesis, informal).  

## Compared to simpler machines

| Model | Memory | Typical languages |
|-------|--------|-------------------|
| DFA / NFA | Finite control only | Regular |
| PDA | Stack | Context-free |
| Turing machine | Infinite read/write tape | Recursively enumerable |

## Implementation in this repository

This lab focuses on **JFLAP visualization** for Turing machines rather than a full C TM simulator:

| File | Description |
|------|-------------|
| [`06-cfg-and-jflap/turing_machine.jff`](../06-cfg-and-jflap/turing_machine.jff) | JFLAP Turing machine model |
| [`tools/jflap/JFLAP7.1.jar`](../tools/jflap/JFLAP7.1.jar) | JFLAP application (Java) |

### Open in JFLAP

```bash
java -jar tools/jflap/JFLAP7.1.jar
# File → Open → 06-cfg-and-jflap/turing_machine.jff
```

## Related docs

[PDA](pda.md) · [What is automata theory?](what-is-automata-theory.md) · [FAQ](faq.md)
