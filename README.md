# TP-1-Qt-Dev-desktop

L' **UI** va dialoguer avec la **FSM** en lui passant la requête (requête utilisant le dialecte). 

----
Ensuite la **FSM** à l'aide du **Lexer** va check toutes les parties de notre requête "token par token" en suivant les étapes et en checkant bien les transitions possibles entre chaque états.

----
Et grâce à la callback de chaque `checkState()` on va monter notre requête **SQL** qui sera transmise à notre base de donnée pour remonter les résultats à l' **UI**.