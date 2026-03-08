# Web C++ Compiler

**Live Demo:**[https://web-cppcompiler.onrender.com](https://web-cppcompiler.onrender.com)

This project is a high-performance **Remote Code Execution (RCE)** engine. It bridges the gap between a web-based user interface and a low-level system compiler, managing the complete lifecycle of a C++ program from source to execution.

---

## Core Technology Stack

* **Backend (Python & Flask):** Acts as the primary orchestrator. It manages the server-side logic, handles the file system (creating/deleting temporary `.cpp` files), and interfaces with the OS to trigger compilation.
* **Frontend (HTML5, CSS3, JavaScript):** A custom-built IDE interface. It implements "Tab" key indentation handling and uses **Fetch API (AJAX)** to communicate with the backend without refreshing the page.
* **Compiler (GCC/G++):** The core execution engine. The system utilizes the GNU C++ compiler installed within a Linux environment to transform high-level code into machine-executable binaries.
* **DevOps (Docker):** Essential for cloud deployment. Since standard cloud platforms lack C++ compilers, Docker is used to build a custom Linux image containing both Python and `g++`.



---

## Key Concepts

### 1. Subprocess Management & Security
The application spawns a separate **Operating System process** for every execution.
* **Mechanism:** Uses Python’s `subprocess` module to run `g++ source.cpp -o binary` followed by `./binary`.
* **Safety:** Implements an **Execution Timeout**. This prevents "hanging" the server if a user accidentally (or maliciously) submits an infinite loop like `while(true){}`.

### 2. Header Injection (Preprocessing)
Before the code reaches the compiler, the system performs a **Preprocessing Step** similar to how a real C++ compiler handles `#include` directives.
* **Mechanism:** The backend dynamically reads the custom `.h` library files (Math, Graphs, etc.) and injects them directly into the source string before writing to disk.
* **Benefit:** This allows users to call complex functions like `dijkstra()` or `nCr()` as if they were part of the C++ standard library.



### 3. Stateless Execution & Concurrency
The server handles multiple users simultaneously without data collisions.
* **Mechanism:** Every execution request is assigned a **UUID (Universally Unique Identifier)**.
* **Collision Prevention:** This ensures that if ten users click "Run" at the same time, each has a unique file path (e.g., `temp_abc123.cpp`), preventing them from overwriting each other's code.

### 4. Containerization (Docker)
This ensures "it works on my machine" translates to the cloud.
* **Concept:** The `Dockerfile` creates a reproducible environment. It defines the specific version of Linux, Python, and GCC required.
* **Portability:** This abstraction allows the compiler to run seamlessly on a cloud provider (Render) regardless of their native software stack.

---

## 📈 Algorithmic Implementation
The integrated library provides optimized solutions for:
* **Modular Arithmetic:** Handling large-scale computations using `% MOD` to prevent integer overflow.
* **Graph Theory:** Priority-queue based Dijkstra for $O(E \log V)$ pathfinding.
* **Amortized Complexity:** Disjoint Set Union (DSU) utilizing path compression and union-by-size for near-constant time operations.
* **Number Theory:** Sieve of Eratosthenes ($O(N \log \log N)$) and Binary Exponentiation.
