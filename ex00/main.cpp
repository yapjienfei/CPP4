#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "===== Correct polymorphism =====" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    j->makeSound(); // dog sound
    i->makeSound(); // cat sound
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << "\n===== Wrong example (no virtual) =====" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << wrongCat->getType() << " " << std::endl;
    wrongCat->makeSound(); // calls WrongAnimal's sound, NOT WrongCat's
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    // Extra test: direct WrongCat
    std::cout << "\n===== Direct WrongCat call =====" << std::endl;
    WrongCat wc;
    wc.makeSound(); // calls WrongCat's version correctly (no pointer)

    return 0;
}
