# 01 — C Lexical Analyzer (Keywords, Numbers, Identifiers)

**Topic:** lexical analysis · compiler design foundation · regular patterns  
**Language:** C  

## What this program does

Classifies interactive input strings as:

1. **C keyword** (e.g. `int`, `return`, `while`)  
2. **Number** (optional sign, digits, optional fractional part)  
3. **Valid identifier** (letter or `_`, then alphanumerics/`_`, not a keyword)  
4. **Invalid identifier** (anything else)

This is a classic first ATFL / compiler-design lab: finite-state thinking without building a full automaton table by hand.

## Files

| File | Role |
|------|------|
| `lexical_analyzer.c` | Full interactive classifier |

## Build and run

```bash
gcc -o lexical_analyzer lexical_analyzer.c
./lexical_analyzer
```

Example session:

```text
Enter a string : int
-> C keyword

Enter a string : count_1
-> Valid identifier

Enter a string : 3.14
-> Number
```

## Concepts

- Character classes as transitions  
- Keywords as a reserved finite set  
- Identifier rules matching the C language subset  

## Related docs

- [What is automata theory?](../docs/what-is-automata-theory.md)  
- [DFA](../docs/dfa.md)  
