# TP-1-Qt-Dev-desktop

L' **UI** va dialoguer avec la **FSM** en lui passant la requête (requête utilisant le dialecte). 

----
Ensuite la **FSM** à l'aide du **Lexer** va check toutes les parties de notre requête "token par token" en suivant les étapes et en checkant bien les transitions possibles entre chaque états.

----
Et grâce à la callback de chaque `checkState()` on va monter notre requête **SQL** qui sera transmise à notre base de donnée pour remonter les résultats à l' **UI**.

Toutes les étapes de la FSM ne sont pas faite, mais le SEARCH fonctionne. Il y manque quelques précisions d'options comme les "BETWEEN".

Exemple de requête à tester:
```
SEARCH 'testme please' CREATED:12/2020 MAX_SIZE:10M MIN_SIZE:20M TYPE:image OR text LAST_MODIFIED:05/07/2023
```

L'objectif de la FSM est de construire une requête SQL à ensuite envoyer à la base de données et suivre tout le processus.
