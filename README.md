*This project has been created as part of the 42 curriculum by kong.*

# CPP Module 04 — Subtype Polymorphism, Abstract Classes, Interfaces

## Description

This module is about the mechanism that makes object-oriented C++ actually
*object-oriented*: calling a function through a base-class pointer or
reference and having the **derived** class's version run, decided at
runtime rather than at compile time.

The goal is to move from "inheritance as code reuse" to "inheritance as the
foundation for dynamic behavior" — understanding `virtual` functions, the
vtable mechanism behind them, virtual destructors, object slicing, and
abstract classes as a way of turning a design contract into something the
compiler enforces.

| Exercise | Topic | Status |
|---|---|---|
| `ex00` | Subtype polymorphism — `Animal`, `Dog`, `Cat`, and the deliberately-broken `WrongAnimal`/`WrongCat` pair | ✅ done |
| `ex01` | Abstract classes | ⏳ planned |
| `ex02` | Interfaces | ⏳ planned |

## Instructions

Each exercise is self-contained with its own `Makefile`.

```sh
cd ex00
make        # builds ./polymorphism
./polymorphism
make clean  # remove object files
make fclean # remove object files + binary
make re     # fclean + all
```

Compiled with `c++ -Wall -Wextra -Werror -std=c++98` — no warnings, no
C++11-and-later features (no `auto`, no `nullptr`, no range-based `for`,
etc.), consistent with the 42 C++ track's constraints.

`ex00/main.cpp` is written as a walkthrough rather than a single check: each
numbered block isolates one concept (plain construction, dynamic dispatch,
the `WrongAnimal` failure mode, slicing, copy semantics, destructor order)
so the constructor/destructor trace printed to stdout can be read as a
commentary on what's actually happening underneath each line.

## Technical Concepts

### Inheritance vs. Polymorphism vs. Abstract Classes

These three are often lumped together, but they're layered, not parallel —
each one builds on the one before it.

| Concept | What it is | What it controls |
|---|---|---|
| **Inheritance** | `class Dog : public Animal` | *Structure* — which members and interface `Dog` has, by reusing `Animal`'s. A compile-time, "is-a" relationship. |
| **Polymorphism** | `virtual` on a member function | *Behavior* — which override actually executes, resolved at **runtime** from the object's real type, when called through a base pointer/reference. |
| **Abstract base class** | `= 0` on a virtual function (pure virtual) | *A constraint on top of polymorphism* — the dispatch mechanism is unchanged, but the base can no longer be instantiated on its own, because that vtable slot has no implementation to fall back to. |

- **Concrete base** (this module's `Animal`, in `ex00`): the base class is
  meaningful as a standalone object, and every derived class can fall back
  on a sensible default behavior if it doesn't override something.
- **Abstract base** (`ex01`'s equivalent): the base represents a category or
  contract, not a real object — "an animal in general" doesn't exist, only
  specific kinds do. Making it abstract turns that intent into a rule the
  compiler enforces, rather than a convention someone can violate by
  mistake.

### Virtual functions and dynamic dispatch

Every polymorphic object secretly carries a hidden pointer (the **vptr**) to
its class's table of function pointers (the **vtable**). Each constructor,
running base-to-derived, overwrites that vptr to point at *its own* class's
vtable — so by the time a `Dog`'s constructors finish running, the vptr
points at `Dog`'s vtable and stays there until the object starts
destructing. A `virtual` call is resolved by looking up that vtable at
runtime; a non-virtual call is resolved from the **pointer's declared
type**, at compile time.

```cpp
Animal* a = new Dog();
a->makeSound();
// a's compile-time type is Animal*, but the object is actually a Dog.
// Because makeSound() is virtual, this looks up Dog's vtable at runtime
// and prints "Woof Woof!" — NOT Animal's generic sound.
```

`ex00`'s `WrongAnimal`/`WrongCat` pair exists specifically to show the
opposite outcome from the exact same code shape, with `virtual` removed:

```cpp
WrongAnimal* w = new WrongCat();
w->makeSound();
// WrongAnimal::makeSound() is deliberately NOT virtual.
// The call is bound statically, at compile time, to WrongAnimal's version —
// it prints WrongAnimal's sound, even though the object is really a WrongCat.
```

One `virtual` keyword is the entire difference between those two outcomes.

### Virtual destructors

The same dynamic-dispatch idea applies to destruction. Without a virtual
destructor, `delete`-ing a derived object through a base pointer only runs
the base class's destructor — the derived part is leaked and never cleaned
up. Declaring the base destructor `virtual` fixes this:

```cpp
class Animal
{
public:
    virtual ~Animal();   // ensures delete through Animal* still runs
                         // Dog's/Cat's destructor first, then Animal's
};
```

Verified in `ex00/main.cpp` by deleting a `Cat` through an `Animal*` and
confirming both destructor messages print, in the correct order.

### Object slicing

Slicing happens whenever a derived object is copied into storage whose
**declared type is the base class** — not when it's referred to by pointer
or reference.

```cpp
Dog    dog;
Animal sliced = dog;   // slices: only Animal's copy ctor runs
                        // sliced's vptr points at Animal's vtable, not Dog's
sliced.makeSound();     // prints Animal's generic sound, not "Woof Woof!"
```

Passing a base-class parameter **by value** is the same mechanism, just
triggered from a different place — `void speak(Animal a)` copy-initializes
`a` on every call exactly like the line above, silently slicing whatever
derived object was passed in. This is why polymorphic code should pass by
pointer or reference (`Animal&` / `Animal*`), never by value — and why
containers of polymorphic objects should hold pointers
(`std::vector<Animal*>`), not values (`std::vector<Animal>`).

| Storage form | Slices? | Why |
|---|---|---|
| `Animal a = dog;` | Yes | Constructs a *new* `Animal`-typed object; only `Animal`'s copy ctor is visible. |
| `void f(Animal a)` | Yes | Identical mechanism — the parameter is copy-initialized the same way. |
| `Animal& ref = dog;` | No | Just an alias for `dog` — no new object, no copy. |
| `Animal* ptr = &dog;` | No | Just an address — same object, untouched. |

### Orthodox Canonical Form across an inheritance chain

Constructors chain to the base automatically **only if you say so** in the
member-initializer list:

```cpp
Dog::Dog(const Dog& other) : Animal(other) { ... }
```

**Assignment operators do not chain automatically at all** — this is easy
to miss, and it's a real bug this project's test suite caught: `Dog`,
`Cat`, and `WrongCat`'s `operator=` were initially written as

```cpp
Dog& Dog::operator=(const Dog& other)
{
    (void)other;               // bug: base subobject never gets assigned
    ...
    return (*this);
}
```

which silently discarded `other` instead of copying anything from it. It
went unnoticed at first because `Dog`'s only inherited member (`type`) is
always `"Dog"` anyway, so the missing copy produced the same output by
coincidence. The fix is to explicitly invoke the base class's `operator=`
in the body:

```cpp
Dog& Dog::operator=(const Dog& other)
{
    Animal::operator=(other);   // must be called explicitly — never implicit
    ...
    return (*this);
}
```

## Resources

**References**

- [cppreference — Virtual function specifier](https://en.cppreference.com/w/cpp/language/virtual)
- [cppreference — Virtual destructors](https://en.cppreference.com/w/cpp/language/destructor#Virtual_destructor)
- [cppreference — Abstract class](https://en.cppreference.com/w/cpp/language/abstract_class)
- [isocpp.org C++ FAQ — Object slicing](https://isocpp.org/wiki/faq/value-vs-ref-semantics)
- [isocpp.org C++ FAQ — Virtual functions](https://isocpp.org/wiki/faq/virtual-functions)
- Scott Meyers, *Effective C++*, Item 7 — "Declare destructors virtual in
  polymorphic base classes"

**AI usage**

Claude (Claude Code) was used throughout this exercise as a tutor and code
reviewer, not as the primary author of the design:

- Explaining/clarifying the mechanics of dynamic dispatch, vtables, virtual
  destructors, object slicing, and the distinction between inheritance,
  polymorphism, and abstract classes, in response to specific follow-up
  questions.
- Reviewing the already-written `Animal`/`Dog`/`Cat`/`WrongAnimal`/`WrongCat`
  implementation for correctness against the subject and against C++ OCF
  conventions — this caught the missing virtual destructor, the missing
  `Animal` implementation for the base `makeSound()`, and the
  copy-assignment operators silently failing to chain to their base class.
- Drafting `ex00/main.cpp`'s test suite (verified by compiling with
  `-Wall -Wextra -Werror -std=c++98` and running it) and this README.
