# minishell 🐚
# 2024

#sigint(ctrl c) and sigquit(ctrl \) - ignore sigquit, sigint use readline function
#read, tokenize, ast nodes, parse, expansion, execute

### File Structure
```
                  ░█░░░█░█▀▀░█▀▀▄░█▀▀░█▀▀░█▀▄░▀█▀░█░░░░█▀▀░█▀▀▄░█▀▀▄░▄▀▀▄░█░░█
                  ░▀▄█▄▀░█▀▀░█░▒█░█▀▀░█▀▀░█░█░░█░░█▀▀█░█▀▀░█▄▄▀░█▄▄█░█▄▄█░█▄▄█
                  ░░▀░▀░░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀▀░░░▀░░▀░░▀░▀▀▀░▀░▀▀░▀░░▀░█░░░░▄▄▄▀
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
│   ├── sig_control.h
│   └── error.h
│   └── env.h
│   └── expansion.h
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
├── env/
├── expansion/
├── main.c
└── Makefile
```
###Main branch:
- [x] Write Makefile
- [x] Update headers
- [x] Clean up code to fit new headers and Makefile
- [x] clean memory leaks
- [x] Norm

###Token:
- [x] Add expansion
- [x] Implement correct word splitting (quotes don't split words) 
- [x] Norm

###Env:
- [x] Dup env
- [x] Norm

###Expansion
- [x] Read from env
- [x] Expand word
- [x] Expand quote
- [x] Norm
