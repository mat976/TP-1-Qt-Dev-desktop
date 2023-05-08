### Sur la branche `fsm` nous avons donc le **lexer** et la **FSM**.
L'objectif initial de la **FSM** est de construire une requête SQL à ensuite envoyer à la base de données et suivre tout le processus. 


L' **UI** va dialoguer avec la **FSM** en lui passant la requête (requête utilisant le dialecte). 

Ensuite la **FSM** à l'aide du **Lexer** va check toutes les parties de notre requête "token par token" en suivant les étapes et en checkant bien les transitions possibles entre chaque états, et cela grâce à la classe **State**.

Et grâce à la callback de chaque `checkState()` on va monter notre requête **SQL** qui sera transmise à notre base de donnée pour remonter les résultats à l' **UI**.

Toutes les étapes de la FSM ne sont pas faite, mais le SEARCH fonctionne. Il y manque quelques précisions d'options comme les "BETWEEN".

> le code de la FSM devrait run sans erreurs.
> 
Exemple de requête à tester:
```
SEARCH 'testme please' CREATED:12/2020 MAX_SIZE:10M MIN_SIZE:20M TYPE:image OR text LAST_MODIFIED:05/07/2023
```
