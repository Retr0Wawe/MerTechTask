# TaskManager
A simple task management program.
## Сapabilities
1) Creating, updating and deleting a task
2) The ability to mark a task as completed
3) Sort task by date, substring and parameter equality on content(console version)
## Requirements
1) cmake
2) qt creator and qt libs
## Project setup
```bash
git clone --recursive https://github.com/Retr0Wawe/TaskManager
```
### Download
```bash
sudo apt install cmake
sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt install qtcreator
```
### Build
```bash
mkdir build && cd build
```
```bash
cmake .. -DGUI=ON && make  // Use "-DGUI=OFF" for console version
```
