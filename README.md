# hover
ROS Node to control Hoverboard with Custom Software

Dieser ROS node ist der Nachfolger des Python ROS Nodes [Python ROS Nodes](https://github.com/Techbeard/FTS/tree/master/fts_drive).

```
  ______            ________               __________
|       |          |        |             |   Hover  |
|       |          |        | = RS422 =>  |__________|
|  NUC  | = USB => |  USB   |              __________
|  ROS  |          | Serial | = RS422 =>  |   Hover  |
|_______|          |________|             |__________|

```
# Published Topics

- /odom
- /safty


# Subscribt Toopics

- /cmd_vel

# ROS Services

- /hover/break

# ROS Services Triggert

# Configurations Möglichkeiten

- Serial Wippe1
- Serial Wippe2
- Max Speed Wippen => Was in der Wippe Konfiguriert ist
 



## Verwendet Fireware auf den Hoverboard Mainboards

https://github.com/EmanuelFeru/hoverboard-firmware-hack-FOC
