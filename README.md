# DummyMenu
A sample project to show how to create a simple but expandable menu structure that can be used in an embedded project.

It currently compiles and runs in the Linux terminal, but simple modifications could be made to make it run in a small embedded project using a character display or a graphical display.

Another key feature is that it is non-blocking.
For the sake of using it in the terminal there is a small sleep to allow the terminal time to refresh without flickering.
In an embedded project this could just be removed.

# Prerequisites
None

# Compiling and Running
```
git clone https://github.com/King-Swood/DummyMenu
cd ./DummyMenu
make
cd ./build && ./a.out && cd ..
```

# Instructions
Once the program is running, the "WASD" keys can be used to navigate the menu.

If 'a' is pressed on the top level menu, the program will exit.

If 'q' is pressed at any time, the program will exit.
