# SocialNet Simulator

### COL106 — Long Assignment 2

**Author:** Tiya Mittal

---

# Overview

SocialNet Simulator is a command-line social network backend simulator inspired by the core functionalities of modern social media platforms.

The system supports:

* user management
* friendship graphs
* friend recommendation systems
* shortest-path social analysis
* post management
* chronological content retrieval

The project was developed as part of **COL106: Data Structures and Algorithms**.

---

# Core Data Structures Used

The implementation is built using custom implementations of:

* Graphs
* AVL Trees
* Breadth-First Search (BFS)

HashMaps are additionally used for efficient username lookup.

---

# Repository Structure

```text
.
├── main.cpp
├── compile.bat
├── compile.sh
└── README.md
```

---

# Features

## User & Friendship Management

* Add users
* Create friendships
* Display friend lists
* Friend recommendation system
* Degrees of separation analysis

---

## Content Management

* Add posts
* Chronological post storage
* Reverse chronological retrieval
* Efficient AVL-tree-based ordering

---

# Algorithms & Concepts

| Component          | Data Structure / Algorithm |
| ------------------ | -------------------------- |
| User Network       | Graph (Adjacency List)     |
| Post Storage       | AVL Tree                   |
| User Lookup        | HashMap                    |
| Social Distance    | BFS                        |
| Friend Suggestions | Graph Traversal + Sorting  |

---

# Supported Commands

## User Operations

### Add User

```text
ADD_USER <username>
```

Adds a new user to the network.

---

### Add Friend

```text
ADD_FRIEND <user1> <user2>
```

Creates a bi-directional friendship between two users.

---

### List Friends

```text
LIST_FRIENDS <username>
```

Displays all friends alphabetically.

---

### Suggest Friends

```text
SUGGEST_FRIENDS <username> <N>
```

Suggests up to N friends based on mutual connections.

---

### Degrees of Separation

```text
DEGREES_OF_SEPARATION <user1> <user2>
```

Computes the shortest friendship path using BFS.

---

## Post Operations

### Add Post

```text
ADD_POST <username> "<content>"
```

Adds a timestamped post for the specified user.

---

### Output Posts

```text
OUTPUT_POSTS <username> <N>
```

Displays the most recent N posts.

---

### Exit

```text
EXIT
```

Gracefully terminates the program.

---

# Compilation Instructions

## Windows

Use:

```bash
compile.bat
```

### Requirements

* Windows OS
* g++ compiler installed and configured in PATH

After successful compilation:

```text
Compilation successful. Run main.exe to start.
```

Run using:

```bash
main.exe
```

---

## Linux / Mac

Use:

```bash
chmod +x compile.sh
./compile.sh
```

After successful compilation:

```text
Compilation successful. Run ./main to start.
```

Run using:

```bash
./main
```

---

# Example Workflow

```text
ADD_USER Alice
ADD_USER Bob
ADD_FRIEND Alice Bob
ADD_POST Alice "Hello World!"
LIST_FRIENDS Alice
OUTPUT_POSTS Alice 1
DEGREES_OF_SEPARATION Alice Bob
EXIT
```

---

# Sample Output

```text
User Added
User Added
Friend Added
Post Added
bob
Hello World!
1
```

---

# Error Handling

The program safely handles:

* invalid commands
* duplicate users
* duplicate friendships
* self-friendship attempts
* malformed post inputs
* missing parameters
* disconnected user graphs
* non-existent usernames

Appropriate error messages are displayed whenever possible.

---

# Design Highlights

* Efficient user lookup using HashMaps
* Friendship modeling using adjacency-list graphs
* AVL-tree balancing for efficient post retrieval
* BFS-based shortest path computation
* Case-insensitive username handling
* Reverse chronological post ordering

---

# Technologies Used

| Category    | Tools                       |
| ----------- | --------------------------- |
| Language    | C++                         |
| Concepts    | Graphs, AVL Trees, BFS      |
| Environment | GCC / Shell Scripts         |
| Paradigm    | Object-Oriented Programming |

---

# Future Improvements

* Persistent file storage
* User authentication
* Weighted friendship graphs
* Direct messaging support
* Feed ranking algorithms
* GUI/Web interface

---

# Author

Tiya Mittal
