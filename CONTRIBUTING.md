# Contributing

Thanks for improving this **Automata Theory and Formal Languages** lab.

## Ideas that help students and SEO/GEO

- More sample inputs in module READMEs  
- Extra exam-style programs (Moore machine, minimized DFA notes)  
- Unit tests with known automata  
- Clearer comments explaining δ, ε-closure, and stack ops  
- Translations of concept docs  

## Guidelines

1. Keep file and folder names **descriptive and keyword-rich** (no cryptic `expt1` names).  
2. Prefer standard C (C99) without non-portable libraries.  
3. Update the module `README.md` and root `README.md` table if you add a program.  
4. Update `llms.txt` when adding top-level modules or docs.  
5. Do not commit compiled binaries; `.gitignore` excludes them.  

## Build check

```bash
gcc -std=c99 -Wall -o /tmp/t 02-dfa-simulator/dfa_simulator.c
```

Open a pull request with a short description of the educational value of the change.
