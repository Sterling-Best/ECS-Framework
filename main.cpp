
// Include generated headers (these should include components, factories, etc.)
#include <iostream>
#include <random>
#include <chrono>  // For timing

#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
#pragma message("ankerl/unordered_dense.h included successfully")

#include "component_framework/component_repository.h"
#include "modules/TransformComponent.h"

int main() {
    // Simple output to verify that the system is working
    std::cout << "ECSframework System Test - Main Executable" << std::endl;

    // Here you can create simple test cases for your ECS library to ensure linkage is correct
    // Example usage of components, entities, or factories could be added here
    // For now, just a simple message to confirm the executable runs
    ankerl::unordered_dense::map<int, int> test_map;
    test_map[1] = 42;
    std::cout << "Test value: " << test_map[1] << std::endl;
    ComponentRepository<uint32_t, TransformComponent>  componentRepository = ComponentRepository<uint32_t,TransformComponent>();
    
    TransformComponent componentTest1 = TransformComponent(0, 1, 13.0, 14.0, 15.0);
    TransformComponent componentTest2 = TransformComponent(2, 3, 69.0, 70.0, 71.0);
    componentRepository.AddComponent(componentTest1);
    componentRepository.AddComponent(componentTest2);
    std::cout << "Test Component: " << componentRepository.GetComponent(3).componentID << std::endl;

    componentRepository.Clear();

    auto start = std::chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_real_distribution<> dis(1.0, 10.0);  // Range [1, 10]


    int numComponents = 160000;  // Number of components to create and add
    for (uint32_t i = 0; i < numComponents; ++i) {

        double x = dis(gen);
        double y = dis(gen);
        double z = dis(gen);

        // Create a TransformComponent with varying IDs and example positions
        TransformComponent component(i, i + 1, z, y, z);

        // Add the component to the repository
        componentRepository.AddComponent(component);

        // Output each added component’s ID to verify addition
        // std::cout << "Added Component with ID: " << component.entityID << std::endl;
        i++;
    }
    // End timing and calculate duration
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Display the time taken for the process
    std::cout << "Time taken to add components: " << duration.count() << " seconds" << std::endl;

    // Example of retrieving a component to confirm it's been stored
    uint32_t testID = 145001;
    std::cout << "Component with ID " << testID << ": "
        << componentRepository.GetComponent(testID).componentID << std::endl;
    std::cout << "X " << testID << ": "
        << componentRepository.GetComponent(testID).x << std::endl;
    std::cout << "Y " << testID << ": "
        << componentRepository.GetComponent(testID).x << std::endl;
    std::cout << "Z " << testID << ": "
        << componentRepository.GetComponent(testID).x << std::endl;

    componentRepository.Clear();

    return 0;
}