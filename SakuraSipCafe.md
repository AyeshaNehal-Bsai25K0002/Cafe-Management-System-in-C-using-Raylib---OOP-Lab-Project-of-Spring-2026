The Sakura Sip Cafe

Object-Oriented Programming — Lab Project Report

A Graphical Cafe Management System in C++ with raylib

Subject:	Object-Oriented Programming Lab
Language:	C++ (C++17)
Framework:	raylib 5.x (2D Graphics Library)
Application Type:	Graphical Desktop Application
Total Screens:	7 Interactive Screens
OOP Concepts Applied:	9 Core Concepts
Date:	 04 June 2026


Abstract:
The Sakura Sip Cafe Management System is a high-performance desktop application built in C++ that balances efficient backend business logic with a responsive, hardware-accelerated Graphical User Interface (GUI) design and implementation. Driven and powered by the use of by Raylib library, the application manages the entire operational lifecycle of a modern cafe namely “ The Sakura Sip Cafe” which follows and works on: student/user authentication mapping, dynamic menu rendering through absolute screen space scissor clipping, an interactive transactional shopping cart engine, persistent data storage streams like text files, administrative record manipulation, and an active user rating log also tracked by the use of a text file..
To elevate the user experience and provide a more stable, interactive system, the system implements a real-time kinematic particle simulation layer that renders floating cherry blossoms (Sakura flower petals) using custom pixel-art routines across all visual UI states and screens. The entire application architecture balances run-time processing cycles with Object-Oriented Programming (OOP) paradigms and concepts along with file handling to maintain high performance, structural safety, and modifiable codebase scaling.
Introduction:
Managing cafe records and user streams manually or via plain text interfaces is confusing, time-occupying, and highly vulnerable. Modern interactive applications require a stable architecture that unifies hardware-accelerated interfaces with secure backend memory management.
The motive of this project is to implement The Sakura Sip Cafe Management System, an automated desktop software suite providing dedicated execution paths for both customers and administrators. Customers can fluidly browse a scroll-bounded, scissor-clipped menu canvas, modify shopping cart quantities, track live bills, checkout, and leave qualitative star feedback. Simultaneously, administrators can jump into a secure dashboard to inject new product items or delete existing profiles with automatic heap compaction. The project comprehensively covers advanced software structural design, utilizing modular class structures, custom scope boundaries, data persistence streams, and hardware multimedia link layers to optimize system performance and security.
Objectives:

1. To enable real-time product ordering, insertion, and deletion through a highly responsive graphical user interface.
2. To automatically calculate total transactional costs and permanently log order sheets to a disk ledger.
3. To secure systemic fields and application routes using a robust login state machine and integrated user rating engine.
4. To secure systemic fields and application routes using a robust login state machine and integrated user rating engine.
5. To design a visually engaging, custom-themed interactive graphical layout featuring responsive collision buttons and floating particle layers to increase user immersion.
System Design:
1. For Users:
Login Verification, Main Dashboard (HOME), View Dynamic Menu, Assemble Order & Update Quantities, Compute Total Bill, File Persistence Checkout, Leave Star Rating & Comments, Exit.

2. For Admin Members: 
Login Verification, Main Dashboard (HOME), Access Admin Panel, Append New Menu Item (Vector Push Back) OR Delete Item (Vector Erase), Auto-Refresh Menu State, Exit.
Algorithm:
1.	Start the program by building the file in VS Code and accessing the executable file via new terminal in VS Code.
2.	The Raylib Window will pop-up.
3.	Login in the system as user or administrator
4.	Prompt users to select and order items from the menu.
5.	Compute bill for the total items ordered.
6.	Items Chosen From The menu can be increased or decreased in quantity.
7.	Leave feedback in the text box and rate the café.
8.	If admin, items can be added and deleted in and from the menu.
9.	To ensure that your orders and reviews were stored in the text file go to “history.txt” for having a look at the order history and go to “ratings.txt” to take a look at the rating history.
10.	End The Program
    
Input & Output:

Input: Credentials of user or admin, add items, adjust the quantity, delete items, calculate bill and leave feedback, leave comments, check feedback and order history via text files.

Implementation:
Language: C++ (Standard ISO/IEC C++11)
Compiler/IDE: Visual Studio Code / MinGW GCC Compiler toolchain
Graphics Library: Raylib Engine (Hardware OpenGL Layer)
Linker Compilation Syntax: g++ cafemanagementsystem.cpp -o cafe.exe -lraylib -lopengl32 -lgdi32 -lwinmm
 
 OOP Features Used:

1. Encapsulation:
Encapsulation is used in this project by bundling data and functions inside the App class. All major states like cart, menu, user input, and screen control are protected inside the class and accessed only through controlled methods:
2. Abstraction
Abstraction is achieved by hiding implementation details of UI logic and screen rendering. The user interacts with simple functions like Button() without knowing internal drawing logic.
3. Composition
Composition is used where the App class has a UI object, meaning the UI system is part of the application and cannot exist independently.
4. Polymorphism
Polymorphism is implemented using a base class with a virtual function, allowing different screens to behave differently using a common interface and blueprint.
5. Inheritance
Inheritance is used to create specialized screens from a common base screen structure, improving scalability and code reuse.
6. File Handling
File handling is used in this project to store and retrieve data permanently using files instead of keeping it only in memory. Furthermore, file handling here is done in: “history.txt” and “ratings.txt”.
It allows the program to save records (like inventory or user data) using fstream header, ifstream, and ofstream.
6. Use of Vector and STL
In this project, I used std::vectors instead of traditional arrays because vectors provide dynamic memory management and organization, which is essential for handling changing data such as menu items when added or deleted, cart items when incremented or decremented, and petals animation in all the frames and screens. Unlike arrays, which have a fixed size defined at compile time, vectors can automatically grow or shrink in size during program execution, making them flexible and efficient for real-world applications like the cafe management system here. It also has Built-in functions like push_back(), erase(), and size(), simplify operations which help with our execution of objects of the classes.

