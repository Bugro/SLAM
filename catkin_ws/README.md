#Workspace ROS

ROS est ici utilisé avec workspace catkin. Il y a pour le moment un seul package (slam) dépendant de rtabmap_ros.
Actuellement le package se contente de lancer rtabmap_ros (voir slam.launch).

Pour l'utiliser il faut installer les packages openni_camera (ainsi que le driver de la kinect), openni_launch et rtabmap_ros.

Il peut être intéressant d'installer aussi le package gmapping et la stack navigation pour la suite.
