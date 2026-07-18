# 06 — Context-Free Grammars & JFLAP (CFG, PDA, TM)

**Topic:** CFG · derivation · CFL · PDA · Turing machine  
**Language:** C + JFLAP  

## What this module does

- **C programs** check whether a string can be derived from a CFG.  
- **JFLAP models** visualize CFG, PDA, and Turing machine examples.

## Files

| File | Role |
|------|------|
| `cfg_derivation.c` | Interactive CFG derivation / membership search |
| `cfg_exam_simple.c` | Compact recursive derivation check |
| `cfg.jff` | JFLAP context-free grammar |
| `pda.jff` | JFLAP pushdown automaton |
| `turing_machine.jff` | JFLAP Turing machine |

## Build and run (C)

```bash
gcc -o cfg_derivation cfg_derivation.c && ./cfg_derivation
gcc -o cfg_exam_simple cfg_exam_simple.c && ./cfg_exam_simple
```

## Open JFLAP models

```bash
java -jar ../tools/jflap/JFLAP7.1.jar
```

## Related docs

- [docs/cfg.md](../docs/cfg.md)  
- [docs/pda.md](../docs/pda.md)  
- [docs/turing-machine.md](../docs/turing-machine.md)  
- [07 PDA simulator (C)](../07-pda-simulator/)  
