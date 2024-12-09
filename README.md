# minishell
# 2024

#sigint(ctrl c) and sigquit(ctrl \) - ignore sigquit, sigint use readline function
#read, tokenize, ast nodes, parse, expansion, execute

### File Structure
```
minishell
├── inc/
│   ├── minishell.h
│   ├── token.h
│   ├── parse.h
│   ├── exec.h
│   ├── pipe.h
│   ├── redirect.h
│   ├── builtins.h
│   ├── heredoc.h
│   ├── signal.h
│   └── error.h
├── libft/
├── token/
├── parse/
├── exec/
├── pipe/
├── redirect/
├── builtins/
├── heredoc/
├── signal/
├── error/
├── main.c
└── Makefile
```
- [x] Write Makefile
- [ ] Update headers
- [ ] Clean up code to fit new headers and Makefile
