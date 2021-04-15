# danceDanceRevolution

Bonjour Madame,

# installation

Pour installer notre projet il suffit d'exécuter le script shell.

En tapant la commande : sudo ./script.sh
Il faudra sûrement lui donner les droits d'exécution en tapant la commande : chmod a+x script.sh

Si le script shell ne fonctionne pas il faut tout d'abord s'assurer que la librairie ncurses est installer sur votre PC.

Puis il faut taper la commande make dans le répertoire du projet

Pour lancer le jeu il faut taper la commande : ./dance.exe


# principe du jeu

Le principe du jeu est simple gagner le + de points en appuyant sur les touches de votre clavier au bon moment 
                   _ 
(juste avant le :  _ )

au plus la difficulté est grande au plus vous marquez de points à chaque saisie, mais attention la vitesse de défilement augmente également

# comment lancer une partie

Une fois que vous avez lancé la commande ./dance.exe, vous avez la possibilité de choisir le mode de jeu. Solo ou à deux.
Une fois le mode choisi il faut choisir le niveau (1 à 10).
En mode solo vous pouvez commencer à jouer, une fois la partie terminée il faut rentrer un pseudo qui s'affichera ensuite avec votre score dans le fichier scores.txt
Vous verrez également le top des scores dans ce fichier.

En mode multijoueurs une salle se crée et un code de salle est généré.
IL faut copier ce code et le mettre dans un autre terminal en tapant la même commande : ./dance.exe <numero salle>
Une fois la partie terminée vous savez qui des deux a gagné.

Bon courage !