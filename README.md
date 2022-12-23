# TaskManager
A simple task management program.
## Сapabilities
```
1) Creating, updating and deleting a task
2) The ability to mark a task as completed
3) Sort task by date, substring and parameter equality on content(console version)
```
## Requirements
```
1) cmake
2) qt creator and qt libs
```
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
## Build
```bash
mkdir build && cd build
cmake .. -DGUI=ON && make  // Use "-DGUI=OFF" for console version
```
## Usage
```
1) add {task_name} {description} {date(like: 2020-12-12-00:00)} {category} - adds a task
2) done {task_name} - marks the task as finished
3) update {task_name} (and you shuold be enter your new date) - updates the task with your data
4) delete {task_name} - removes a task from the list
5) select * - print all tasks
6) select * where {predicate} - provides output filtering by given parameters and keywords
```
## Screenshots
### Gui version
![task_manager](https://github.com/Retr0Wawe/TaskManager/blob/main/screenshots/task_manager.png "Task Manager(Gui version)")
### Console version with own sort algorithm
![task_manager](https://github.com/Retr0Wawe/TaskManager/blob/main/screenshots/console_manager.png "Task Manager(Console version)")
