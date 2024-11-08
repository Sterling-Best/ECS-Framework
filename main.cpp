
// Include generated headers (these should include components, factories, etc.)
#include <iostream>
#include <random>
#include <chrono>  // For timing

#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
#pragma message("ankerl/unordered_dense.h included successfully")

#include "component_framework/component_repository.h"
#include "modules/TransformComponent.h"

void ModifyComponent(TransformComponent* component, double multiplier) {
    component->x *= multiplier;
    component->y *= multiplier;
    component->z *= multiplier;
}

int main() {
    // Number of times each test will run
    int numRuns = 100;  // You can adjust this value

    // Simple output to verify that the system is working
    std::cout << "ECSframework System Test - Main Executable" << std::endl;

    // Here you can create simple test cases for your ECS library to ensure linkage is correct
    // Example usage of components, entities, or factories could be added here
    // For now, just a simple message to confirm the executable runs
    ankerl::unordered_dense::map<int, int> test_map;
    test_map[1] = 42;
    std::cout << "Test value: " << test_map[1] << std::endl;
    ComponentRepository<uint64_t, TransformComponent>  componentRepository = ComponentRepository<uint64_t, TransformComponent>();
    
    TransformComponent componentTest1 = TransformComponent(0, 1, 13.0, 14.0, 15.0);
    TransformComponent componentTest2 = TransformComponent(2, 3, 69.0, 70.0, 71.0);
    componentRepository.AddComponent(std::move(componentTest1));
    componentRepository.AddComponent(std::move(componentTest2));
    std::cout << "Test Component: " << componentRepository.GetComponent(3).componentID << std::endl;

    componentRepository.Clear();

    std::random_device rd;
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_real_distribution<> dis(1.0, 10.0);  // Range [1, 10]

    // Timing results storage
    std::vector<double> addDurations, iterateDurations;

    for (int run = 0; run < numRuns; ++run) {
        std::cout << "\nRun #" << (run + 1) << ":\n";

        ComponentRepository<uint32_t, TransformComponent> componentRepository;
        int numComponents = 3000000;  // Number of components to create and add
        componentRepository.ReserveSize(numComponents);

        auto start = std::chrono::high_resolution_clock::now();
        for (uint32_t i = 0; i < numComponents; ++i) {

            // Create a TransformComponent with varying IDs and example positions
            TransformComponent component(i, i + 1, dis(gen), dis(gen), dis(gen));

            // Add the component to the repository
            componentRepository.AddComponent(std::move(component));

            // Output each added component’s ID to verify addition
            // std::cout << "Added Component with ID: " << component.entityID << std::endl;
            i++;
        }
        // End timing and calculate duration
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        addDurations.push_back(duration.count());

        // Display the time taken for the process
        std::cout << "Time taken to add components: " << duration.count() << " seconds" << std::endl;

        // Example of retrieving a component to confirm it's been stored
        uint32_t testID = 9;
        std::cout << "Component with ID " << testID << ": "
            << componentRepository.GetComponent(testID).componentID << std::endl;
        std::cout << "X " << testID << ": "
            << componentRepository.GetComponent(testID).x << std::endl;
        std::cout << "Y " << testID << ": "
            << componentRepository.GetComponent(testID).y << std::endl;
        std::cout << "Z " << testID << ": "
            << componentRepository.GetComponent(testID).z << std::endl;

        std::size_t componentCount = componentRepository.Count();
        std::cout << "Number of components in repository: " << componentCount << "\n";

        // Calculate memory usage (approximate)
        std::size_t totalMemoryUsage = componentCount * sizeof(TransformComponent);
        double memoryUsageGB = static_cast<double>(totalMemoryUsage) / (1024 * 1024 * 1024);
        std::cout << "Approximate memory usage: " << memoryUsageGB << " GB\n";

        // Multiply all components by a factor
        start = std::chrono::high_resolution_clock::now();
        double multiplier = 10;
        componentRepository.IterateAllComponentsMethod(&ModifyComponent, multiplier);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        iterateDurations.push_back(duration.count());
        std::cout << "Time taken to iterate and modify components: " << duration.count() << " seconds" << std::endl;

        // Reuse the previously defined testID
        try {
            TransformComponent testComponent = componentRepository.GetComponent(testID);
            std::cout << "Random Component ID " << testID << " after modification:\n";
            std::cout << "X: " << testComponent.x << ", Y: " << testComponent.y << ", Z: " << testComponent.z << "\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

        componentRepository.Clear();
    }

    // Calculate average duration
    double avgAddDuration = 0.0;
    double avgIterateDuration = 0.0;
    for (const auto& d : addDurations) avgAddDuration += d;
    for (const auto& d : iterateDurations) avgIterateDuration += d;
    avgAddDuration /= numRuns;
    avgIterateDuration /= numRuns;

    // Display average times with high precision
    std::cout << std::fixed << std::setprecision(10);  // Set precision to 10 decimal places

    std::cout << "\nAverage Time taken to add components over " << numRuns << " runs: "
        << avgAddDuration << " seconds" << std::endl;
    std::cout << "Average Time taken to iterate and modify components over " << numRuns << " runs: "
        << avgIterateDuration << " seconds" << std::endl;

    return 0;
}