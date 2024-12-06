import random
from abc import ABC, abstractmethod


class EcosystemEntity(ABC):
    def __init__(self, name, energy, position, survival_rate):
        self.name = name
        self.energy = energy
        self.position = position  # (x, y)
        self.survival_rate = survival_rate

    @abstractmethod
    def act(self, ecosystem):
        pass

    def reproduce(self):
        if self.energy > 50:
            self.energy //= 2
            return self.__class__(
                name=self.name,
                energy=self.energy,
                position=(self.position[0] + 1, self.position[1] + 1),
                survival_rate=self.survival_rate,
            )
        return None


class Plant(EcosystemEntity):
    def act(self, ecosystem):
        self.energy += 10  # Photosynthesis increases energy
        if random.random() < 0.3:  # 30% chance to reproduce
            new_plant = self.reproduce()
            if new_plant:
                ecosystem.add_entity(new_plant)


class Animal(EcosystemEntity, ABC):
    def __init__(self, name, energy, position, survival_rate, speed, diet):
        super().__init__(name, energy, position, survival_rate)
        self.speed = speed
        self.diet = diet  # 'plants', 'animals', 'mixed'

    @abstractmethod
    def eat(self, prey=None):
        pass

    def move(self):
        dx = random.randint(-self.speed, self.speed)
        dy = random.randint(-self.speed, self.speed)
        self.position = (self.position[0] + dx, self.position[1] + dy)


class Herbivore(Animal):
    def eat(self, plants):
        if plants:
            plant = random.choice(plants)
            self.energy += plant.energy
            plants.remove(plant)

    def act(self, ecosystem):
        self.move()
        plants = [p for p in ecosystem.entities if isinstance(p, Plant)]
        self.eat(plants)


class Carnivore(Animal):
    def eat(self, prey):
        if prey:
            victim = random.choice(prey)
            self.energy += victim.energy
            prey.remove(victim)

    def act(self, ecosystem):
        self.move()
        prey = [a for a in ecosystem.entities if isinstance(a, Animal) and not isinstance(a, Carnivore)]
        self.eat(prey)


class Omnivore(Animal):
    def eat(self, ecosystem):
        if random.random() < 0.5:  # 50% chance to eat plants or animals
            plants = [p for p in ecosystem.entities if isinstance(p, Plant)]
            if plants:
                plant = random.choice(plants)
                self.energy += plant.energy
                ecosystem.entities.remove(plant)
        else:
            prey = [a for a in ecosystem.entities if isinstance(a, Animal) and not isinstance(a, Omnivore)]
            if prey:
                victim = random.choice(prey)
                self.energy += victim.energy
                ecosystem.entities.remove(victim)

    def act(self, ecosystem):
        self.move()
        self.eat(ecosystem)


class Ecosystem:
    def __init__(self, size):
        self.size = size
        self.entities = []

    def add_entity(self, entity):
        self.entities.append(entity)

    def remove_entity(self, entity):
        if entity in self.entities:
            self.entities.remove(entity)

    def display_state(self):
        print(f"Ecosystem size: {self.size}")
        for entity in self.entities:
            print(f"{entity.name}: Energy={entity.energy}, Position={entity.position}")

    def simulate_steps(self, steps):
        for step in range(steps):
            print(f"\n--- Step {step + 1} ---")
            # Random events
            event = random.random()
            if event < 0.1:
                print("Random event: storm! Some entities disappear.")
                self.entities = random.sample(self.entities, len(self.entities) // 2)
            elif event < 0.2:
                print("Random event: drought! Plants lose energy.")
                for entity in self.entities:
                    if isinstance(entity, Plant):
                        entity.energy -= 10

            # Entities take actions
            for entity in list(self.entities):  # Use a copy to prevent modification issues
                if entity.energy <= 0:
                    self.remove_entity(entity)
                else:
                    entity.act(self)

            self.display_state()


def test_ecosystem():
    ecosystem = Ecosystem(size=(10, 10))

    # Add entities
    ecosystem.add_entity(Plant("Flower", 20, (2, 2), 0.8))
    ecosystem.add_entity(Herbivore("Rabbit", 50, (1, 1), 0.9, 2, "plants"))
    ecosystem.add_entity(Carnivore("Wolf", 70, (5, 5), 0.7, 3, "animals"))
    ecosystem.add_entity(Omnivore("Bear", 100, (3, 3), 0.85, 2, "mixed"))

    # Simulate 5 steps
    ecosystem.simulate_steps(5)


if __name__ == "__main__":
    test_ecosystem()
