# C++ Module 04 — 42KL

> Subtype polymorphism, abstract classes, pure virtual functions, and deep copy semantics in C++.

## Overview

Module 04 addresses the most powerful aspect of object-oriented design in C++: the ability to write code that operates on a base class pointer and automatically invokes the correct method at runtime, regardless of the concrete derived type. This is *runtime polymorphism* — also called *subtype polymorphism* — and it is what makes pluggable architectures, strategy patterns, and extensible systems possible.

The module also covers a critical detail that bites every C++ developer at least once: when a derived class owns heap memory, copy and assignment must *deep copy* that memory, not just copy the pointer. Finally, abstract classes are introduced as a way to define an interface — a contract that derived classes must fulfil — without providing an implementation.

## The Challenge

`ex00` sets up a base class (`Animal`) with a virtual `makeSound()`, and two concrete subclasses (`Dog`, `Cat`). The key requirement: when a `Dog` is stored in an `Animal*`, calling `makeSound()` must produce a dog sound — not the base class sound. This only works if `makeSound()` is declared `virtual`.

`ex01` adds a `Brain` class with 100 ideas, owned by `Dog` and `Cat`. The challenge: when you copy a `Dog`, you must copy its `Brain` too (deep copy), not just the pointer to it. Failing this means two `Dog` objects sharing one `Brain` — a dangling pointer on destruction.

`ex02` makes `Animal` abstract by adding a pure virtual function, preventing direct instantiation of the base class. Only concrete derived types can be instantiated.

## Concepts Introduced

- **Virtual functions**: declaring a function `virtual` in the base class so derived class overrides are called through base pointers
- **Runtime polymorphism**: the compiler inserts a vtable lookup so the correct function is called based on the *actual* type of the object, not the *declared* type of the pointer
- **`virtual` destructor**: why base class destructors must be `virtual` — without it, deleting a `Derived*` through a `Base*` leaks the derived object's resources
- **Pure virtual functions (`= 0`)**: declaring a function with no implementation, making the class abstract and forcing derived classes to provide one
- **Abstract classes**: classes with at least one pure virtual function; they cannot be instantiated directly but can be used as interfaces
- **Deep copy**: when a class owns heap-allocated members, the copy constructor and copy assignment operator must allocate new memory and copy the data — not just copy the pointer
- **Shallow copy danger**: what happens when two objects share the same heap pointer and one is destroyed

## Learning Outcomes

After completing this module you will have:
- Understood how virtual function dispatch works (vtable/vptr mechanism conceptually)
- Written a class hierarchy where polymorphism works correctly through base class pointers
- Understood why `virtual` destructors are mandatory in base classes that may be deleted polymorphically
- Implemented deep copy semantics for classes with owned heap resources
- Designed abstract interfaces using pure virtual functions and understood their role in architecture
- Gained intuition for why C++ is explicit about polymorphism (unlike Java/Python where everything is virtual)

## Exercises

### ex00 — Polymorphism
`Animal` has a `virtual makeSound()`. `Dog` and `Cat` override it. Storing mixed types in a `Animal*` array and calling `makeSound()` in a loop demonstrates that the correct subtype method is called.

```cpp
Animal *animals[4] = {new Dog, new Dog, new Cat, new Cat};
for (int i = 0; i < 4; i++)
    animals[i]->makeSound();  // calls Dog::makeSound or Cat::makeSound correctly
```

### ex01 — I don't want to set the world on fire
`Dog` and `Cat` each own a `Brain*` (100 ideas). Deep copy is implemented in the copy constructor and `operator=`. Verified by modifying the copy's brain and confirming the original is unchanged.

### ex02 — Abstract class
`Animal::makeSound()` becomes a pure virtual function (`= 0`). Attempting `Animal a;` now produces a compile error. Only `Dog` and `Cat` — which provide a concrete `makeSound()` — can be instantiated.

## How to Build

```bash
cd ex02 && make && ./animal
```

The test should create animals, copy them, call sounds polymorphically, and clean up without memory leaks. Run with Valgrind to verify:

```bash
valgrind --leak-check=full ./animal
```
