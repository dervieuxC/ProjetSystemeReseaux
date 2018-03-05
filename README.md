# ProjetSystemeReseaux
Projet de groupe de fin de 1er semestre dans le cadre de L3MIAGE


Makefile
Le makefile a quatre commandes principale :
    >-    `<make>` : qui permet de compiler et faire les liens avec le code se trouvant dans src “.c” et dans les include “.h”.
    >-    `<make clean>` : permet de supprimer les fichiers se trouvant dans dossier bin “.o” 
    >-    `<make help>` : affiche toutes les possibilités de compilation du makefile
    >-    `<make mrproper>`  : réalise un clean et supprimer aussi l’exécutable qui porte le nom donné dans le champs EXEC (soit serveur ou soit client).

Le mot clé wildcard permet l’utilisation du joker *.c et donc de pouvoir compiler un nombre N de fichier .c .

Makefile Père :
    >-    `<make>` : permet d’appeler les makefiles et de les exécuter
    >-    `<make clean>` clean : appelle les autres makefiles avec la commande clean
