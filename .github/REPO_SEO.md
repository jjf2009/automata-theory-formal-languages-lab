# GitHub repository SEO checklist

Use this after pushing the renamed structure.

## 1. Rename the repository (one-time)

Current remote (legacy): `ATFL-College-Codes-`  
Target name: **`automata-theory-formal-languages-lab`**

```bash
gh repo rename automata-theory-formal-languages-lab --yes
```

GitHub keeps redirects from the old URL for a while.

## 2. Set description

```bash
gh repo edit --description "Educational C lab for Automata Theory & Formal Languages: DFA, NFA, Mealy, CFG, PDA, Turing machines, conversion algorithms (ATFL / TOC)."
```

## 3. Set topics (search keywords)

```bash
gh repo edit --add-topic automata-theory --add-topic formal-languages --add-topic theory-of-computation --add-topic dfa --add-topic nfa --add-topic pushdown-automaton --add-topic context-free-grammar --add-topic mealy-machine --add-topic turing-machine --add-topic compiler-design --add-topic lexical-analysis --add-topic c --add-topic jflap --add-topic education --add-topic atfl --add-topic toc --add-topic lab-exercises --add-topic chomsky-hierarchy
```

## 4. Enable features that help discovery

- [ ] Add a social preview image (Settings → General → Social preview): simple diagram “DFA · NFA · PDA · CFG”  
- [ ] Pin this repo on your GitHub profile  
- [ ] Confirm `About` sidebar shows description, website (optional), and topics  

## 5. Optional website field

If you later publish docs with GitHub Pages:

```text
https://jjf2009.github.io/automata-theory-formal-languages-lab/
```

Copy `llms.txt` and `docs/` to the Pages root for GEO.
