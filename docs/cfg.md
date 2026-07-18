# Context-Free Grammar (CFG)

A **context-free grammar (CFG)** is a formal grammar whose production rules replace a single nonterminal regardless of surrounding symbols. CFGs generate **context-free languages (CFLs)**, which sit above regular languages in the Chomsky hierarchy and are recognized by **pushdown automata (PDA)**.

## Formal definition

A CFG is **G = (V, Σ, R, S)** where:

- **V** — finite set of variables (nonterminals)  
- **Σ** — terminals (Σ ∩ V = ∅)  
- **R** — finite set of productions **A → α** with A ∈ V and α ∈ (V ∪ Σ)*  
- **S ∈ V** — start symbol  

A string of terminals *w* is in **L(G)** if **S ⇒\* w** (derivation from S).

## Why CFGs matter

- Programming language syntax (expressions, blocks, nested structure)  
- Balanced parentheses and recursive nesting  
- Compiler front-ends (parsers) after the lexer  
- Conversion to **Chomsky normal form (CNF)** for CYK parsing  

## Chomsky normal form (CNF)

In CNF, every production is one of:

- **A → BC** (two nonterminals), or  
- **A → a** (single terminal),  
- (and sometimes S → ε if ε is in the language).

This repository includes a CFG → CNF helper in module 08.

## Implementation in this repository

| File | Description |
|------|-------------|
| [`06-cfg-and-jflap/cfg_derivation.c`](../06-cfg-and-jflap/cfg_derivation.c) | Interactive CFG membership via derivation search |
| [`06-cfg-and-jflap/cfg_exam_simple.c`](../06-cfg-and-jflap/cfg_exam_simple.c) | Compact exam-style CFG check |
| [`06-cfg-and-jflap/cfg.jff`](../06-cfg-and-jflap/cfg.jff) | JFLAP CFG model |
| [`08-automata-conversions/cfg_to_cnf.c`](../08-automata-conversions/cfg_to_cnf.c) | CFG → Chomsky normal form |

### Compile and run

```bash
gcc -o cfg_derivation 06-cfg-and-jflap/cfg_derivation.c
./cfg_derivation
```

## Related docs

[PDA](pda.md) · [NFA](nfa.md) · [FAQ](faq.md)
