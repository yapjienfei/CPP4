#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    std::cout << "=== Create array of animals ===" << std::endl;
    const int size = 6;
    Animal* animals[size];

    for (int i = 0; i < size; ++i)
    {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    std::cout << "\n=== Make sounds ===" << std::endl;
    for (int i = 0; i < size; ++i)
        animals[i]->makeSound();

    std::cout << "\n=== Delete all animals ===" << std::endl;
    for (int i = 0; i < size; ++i)
        delete animals[i];

    std::cout << "\n=== Deep copy test ===" << std::endl;
    Dog originalDog;
    originalDog.getBrain()->setIdea(0, "Chase the cat");
    Dog copiedDog = originalDog;   // copy constructor

    std::cout << "Original Dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied Dog idea:   " << copiedDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Brain addresses: original = " << originalDog.getBrain()
              << ", copied = " << copiedDog.getBrain() << std::endl;
    // Different addresses -> deep copy
     std::cout << "\n=== Change Copied Dog Idea ===" << std::endl;
    copiedDog.getBrain()->setIdea(0, "Fetch the ball");
    std::cout << "Original Dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied Dog idea:   " << copiedDog.getBrain()->getIdea(0) << std::endl;

    return 0;
}