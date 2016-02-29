# SLAM
Simultaneous Localization And Mapping

Projet de fin d'Ã©tude, SupÃ©lec Majeure SERI.

---------------

* Dossier git Comprend:

- workspace catkin_ws pour ROS (catkin_ws)
- Fichier de récupération des données codeurs en Python 	(Codeur_Rasp)
- Fichier de gestion Kinect (Raspberry_kinect)
- Fichier de gestion communication client serveur (raspConnect)

* Fichiers archives (Non utile pour le moment):
	
- Déplacement du robot + Gestion codeur en C++ (ManageRobotPi)
- Gestion de chemin le plus court type A* (PathFinder)
- Gestion avec interface graphique du chemin le plus court 	(sdlPathFinder)
	
----------------

Installation du driver kinect sur le raspberry pi 2 : http://www.mariolukas.de/2015/04/proof-of-concept-3d-scanner-with-kinect-and-raspberry-pi2/

Installation recommandÃ©e pour ROS :
Ubuntu 14.04 avec ROS Jade.

Le projet ROS se trouve dans le dossier catkin_ws. Il utilise un workspace catkin et contient un package (slam).
