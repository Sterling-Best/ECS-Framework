#include <iostream>
#include <random>
#include <chrono>  // For timing
#include <iomanip> // For setting precision
#include <cassert>

#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
#pragma message("ankerl/unordered_dense.h included successfully")

#include "component_framework/component_repository.h"
#include "modules/TransformComponent.h"

#include "ECSF.h"



void ModifyComponent(TransformComponent* component, double multiplier) {
    component->x *= multiplier;
    component->y *= multiplier;
    component->z *= multiplier;
}

int main() {
    using namespace ECSF;

    //int numRuns = 100;        // Number of times each test will run
    //int numComponents = 40000;  // Number of components to create and add

    //std::cout << "ECSframework System Test - Main Executable" << std::endl;

    //// Timing and memory usage storage
    //std::vector<double> addDurations, iterateDurations, getDurations, individualModifyDurations;
    //std::vector<double> perComponentAddTimes, perComponentIterateTimes, perComponentGetTimes, perComponentModifyTimes;;



    //// Random device and generator setup
    //std::random_device rd;
    //std::mt19937 gen(rd());
    //std::uniform_real_distribution<> dis(1.0, 10.0);

    //ECSF::ChangeComponent<IComponent>();

    ////Start Runs
    //for (int run = 0; run < numRuns; ++run) {
    //    std::cout << "\nRun #" << (run + 1) << ":\n";

    //    ComponentRepository<uint64_t, TransformComponent> componentRepository;
    //    componentRepository.ReserveSize(numComponents);

    //    //Adding Components Test
    //    // Start timing for adding components
    //    auto addStart = std::chrono::high_resolution_clock::now();
    //    for (uint64_t i = 0; i < numComponents; ++i) {
    //        double x = dis(gen);
    //        double y = dis(gen);
    //        double z = dis(gen);
    //        TransformComponent component(i, i + 1, x, y, z);
    //        componentRepository.AddComponent(component);
    //    }
    //    auto addEnd = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<double, std::milli> addDuration = addEnd - addStart;
    //    addDurations.push_back(addDuration.count());
    //    perComponentAddTimes.push_back(addDuration.count() / numComponents);

    //    std::cout << "Time taken to add components: " << addDuration.count() << " ms ("
    //        << addDuration.count() * 1e6 / numComponents << " ns per component)" << std::endl;

    //    // Memory size of components in MB
    //    double memoryUsageMB = (numComponents * sizeof(TransformComponent)) / (1024.0 * 1024.0);
    //    std::cout << "Estimated memory usage: " << memoryUsageMB << " MB" << std::endl;

    //    //Iterate over all components individually test with IterateComponentMethod()
    //    double totalModifyTime = 0.0;

    //    for (uint64_t i = 2; i < numComponents; ++i) {
    //        auto modifyStart = std::chrono::high_resolution_clock::now();
    //        double multiplier = 1.5f;
    //        componentRepository.IterateComponentMethod(ModifyComponent, i, multiplier);
    //        auto modifyEnd = std::chrono::high_resolution_clock::now();
    //        std::chrono::duration<double, std::nano> modifyDuration = modifyEnd - modifyStart;
    //        double modifyTime = modifyDuration.count();
    //        totalModifyTime += modifyTime;
    //        perComponentModifyTimes.push_back(modifyTime);
    //        ++i;
    //    }
    //    double avgModifyTimePerComponent = totalModifyTime / numComponents;
    //    individualModifyDurations.push_back(totalModifyTime / 1e6); // Convert to milliseconds
    //    std::cout << "Total time to modify all components individually: "
    //        << totalModifyTime / 1e6 << " ms\n";
    //    std::cout << "Average time to modify each component individually: "
    //        << avgModifyTimePerComponent << " ns\n";


    //    // Multiply all components by a factor (iteration test)
    //    auto iterateStart = std::chrono::high_resolution_clock::now();
    //    double multiplier = 10;
    //    componentRepository.IterateAllComponentsMethod(&ModifyComponent, multiplier);
    //    auto iterateEnd = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<double, std::milli> iterateDuration = iterateEnd - iterateStart;
    //    iterateDurations.push_back(iterateDuration.count());
    //    perComponentIterateTimes.push_back(iterateDuration.count() / numComponents);

    //    std::cout << "Time taken to iterate and modify components: " << iterateDuration.count() << " ms ("
    //        << iterateDuration.count() * 1e6 / numComponents << " ns per component)" << std::endl;

    //    // Get Components Test
    //    auto getStart = std::chrono::high_resolution_clock::now();
    //    for (uint64_t i = 0; i < numComponents; ++i) {
    //        TransformComponent* testComponent = componentRepository.GetComponent(i);
    //        if (testComponent) {
    //            testComponent->x += 1.0;  // Small modification to prevent optimization
    //        }
    //        ++i;
    //    }
    //    auto getEnd = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<double, std::milli> getDuration = getEnd - getStart;
    //    getDurations.push_back(getDuration.count());
    //    perComponentGetTimes.push_back(getDuration.count() / numComponents);

    //    std::cout << "Time taken to get components: " << getDuration.count() << " ms ("
    //        << getDuration.count() * 1e6 / numComponents << " ns per component)" << std::endl;

    //    // .find() Test
    //    auto directAccessStart = std::chrono::high_resolution_clock::now();
    //    for (uint64_t i = 0; i < numComponents; ++i) {
    //        auto iter = componentRepository._componentPool.find(i);  // Direct access
    //        if (iter != componentRepository._componentPool.end()) {
    //            iter->second.x += 1.0;  // Small modification to simulate access
    //        }
    //    }
    //    auto directAccessEnd = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<double, std::milli> directAccessDuration = directAccessEnd - directAccessStart;
    //    std::cout << "Time taken for direct _componentPool.find access: "
    //        << directAccessDuration.count() << " ms" << std::endl;


    //    componentRepository.Clear();
    //}

    //// Calculate overall average durations
    //double avgAddDuration = 0.0, avgIterateDuration = 0.0, avgGetDuration = 0.0;
    //for (const auto& d : addDurations) avgAddDuration += d;
    //for (const auto& d : iterateDurations) avgIterateDuration += d;
    //for (const auto& d : getDurations) avgGetDuration += d;

    //avgAddDuration /= numRuns;
    //avgIterateDuration /= numRuns;
    //avgGetDuration /= numRuns;

    //// Calculate average per-component times across all runs
    //double avgPerComponentAddTime = 0.0, avgPerComponentIterateTime = 0.0, avgPerComponentGetTime = 0.0;
    //for (const auto& t : perComponentAddTimes) avgPerComponentAddTime += t;
    //for (const auto& t : perComponentIterateTimes) avgPerComponentIterateTime += t;
    //for (const auto& t : perComponentGetTimes) avgPerComponentGetTime += t;

    //avgPerComponentAddTime /= numRuns;
    //avgPerComponentIterateTime /= numRuns;
    //avgPerComponentGetTime /= numRuns;

    //

    //// Display average times in milliseconds and nanoseconds with high precision
    //std::cout << std::fixed << std::setprecision(10);

    //std::cout << "\nAverage Time taken to add components over " << numRuns << " runs: "
    //    << avgAddDuration << " ms (" << avgAddDuration * 1e6 / numComponents << " ns per component)" << std::endl;
    //std::cout << "Average Time taken to iterate and modify components over " << numRuns << " runs: "
    //    << avgIterateDuration << " ms (" << avgIterateDuration * 1e6 / numComponents << " ns per component)" << std::endl;
    //std::cout << "Average Time taken to get components over " << numRuns << " runs: "
    //    << avgGetDuration << " ms (" << avgGetDuration * 1e6 / numComponents << " ns per component)" << std::endl;

    //std::cout << "\nAverage per-component time taken to add components: "
    //    << avgPerComponentAddTime << " ms (" << avgPerComponentAddTime * 1e6 << " ns)" << std::endl;
    //std::cout << "Average per-component time taken to iterate and modify components: "
    //    << avgPerComponentIterateTime << " ms (" << avgPerComponentIterateTime * 1e6 << " ns)" << std::endl;
    //std::cout << "Average per-component time taken to get components: "
    //    << avgPerComponentGetTime << " ms (" << avgPerComponentGetTime * 1e6 << " ns)" << std::endl;

    return 0;
}

//// Include generated headers (these should include components, factories, etc.)
//#include <iostream>
//#include <random>
//#include <chrono>  // For timing
//#include <iomanip> // For setting precision
//
//#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
//#pragma message("ankerl/unordered_dense.h included successfully")
//
//#include "component_framework/component_repository.h"
//#include "modules/TransformComponent.h"
//
//void ModifyComponent(TransformComponent* component, double multiplier) {
//    component->x *= multiplier;
//    component->y *= multiplier;
//    component->z *= multiplier;
//}
//
//int main() {
//    int numRuns = 10;        // Number of times each test will run
//    int numComponents = 45000;  // Number of components to create and add
//
//    std::cout << "ECSframework System Test - Main Executable" << std::endl;
//
//    // Timing and memory usage storage
//    std::vector<double> addDurations, iterateDurations, getDurations;
//    std::vector<double> perComponentAddTimes, perComponentIterateTimes, perComponentGetTimes;
//
//    // Random device and generator setup
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<> dis(1.0, 10.0);
//
//    for (int run = 0; run < numRuns; ++run) {
//        std::cout << "\nRun #" << (run + 1) << ":\n";
//
//        ComponentRepository<uint64_t, TransformComponent> componentRepository;
//        componentRepository.ReserveSize(numComponents);
//
//        // Start timing for adding components
//        auto start = std::chrono::high_resolution_clock::now();
//        for (uint32_t i = 0; i < numComponents; ++i) {
//            double x = dis(gen);
//            double y = dis(gen);
//            double z = dis(gen);
//            TransformComponent component(i, i + 1, x, y, z);
//            componentRepository.AddComponent(component);
//        }
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double, std::milli> duration = end - start;
//        addDurations.push_back(duration.count());
//        perComponentAddTimes.push_back(duration.count() / numComponents);
//
//        std::cout << "Time taken to add components: " << duration.count() << " ms ("
//            << duration.count() * 1e6 / numComponents << " ns per component)" << std::endl;
//
//        // Memory size of components in MB
//        double memoryUsageMB = (numComponents * sizeof(TransformComponent)) / (1024.0 * 1024.0);
//        std::cout << "Estimated memory usage: " << memoryUsageMB << " MB" << std::endl;
//
//        // Multiply all components by a factor (iteration test)
//        start = std::chrono::high_resolution_clock::now();
//        double multiplier = 10;
//        componentRepository.IterateAllComponentsMethod(&ModifyComponent, multiplier);
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//        iterateDurations.push_back(duration.count());
//        perComponentIterateTimes.push_back(duration.count() / numComponents);
//
//        std::cout << "Time taken to iterate and modify components: " << duration.count() << " ms ("
//            << duration.count() * 1e6 / numComponents << " ns per component)" << std::endl;
//
//        // Performance test for GetComponent() without error check
//        start = std::chrono::high_resolution_clock::now();
//        for (uint32_t i = 0; i < numComponents; ++i) {
//            TransformComponent* testComponent = componentRepository.GetComponent(i);
//            if (testComponent) {
//                testComponent->x += 1.0;  // Small modification to prevent optimization
//            }
//        }
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//        getDurations.push_back(duration.count());
//
//
//        //// Performance test for GetComponent()
//        //start = std::chrono::high_resolution_clock::now();
//        //for (uint32_t i = 0; i < numComponents; ++i) {
//        //    uint32_t testID = i;
//        //    TransformComponent* testComponent = componentRepository.GetComponent(testID);
//        //    if (testComponent) {
//        //        testComponent->x += 1.0;
//        //    }
//        //}
//        //end = std::chrono::high_resolution_clock::now();
//        //duration = end - start;
//        //getDurations.push_back(duration.count());
//        perComponentGetTimes.push_back(duration.count() / numComponents);
//
//        std::cout << "Time taken to get components: " << duration.count() << " ms ("
//            << duration.count() * 1e6 / numComponents << " ns per component)" << std::endl;
//
//        auto start = std::chrono::high_resolution_clock::now();
//
//        for (uint32_t i = 0; i < numComponents; ++i) {
//            auto iter = componentRepository._componentPool.find(i);  // Direct access
//            if (iter != componentRepository._componentPool.end()) {
//                iter->second.x += 1.0;  // Small modification to simulate access
//            }
//        }
//
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double, std::milli> duration = end - start;
//        std::cout << "Time taken for direct _componentPool.find access: "
//            << duration.count() << " ms" << std::endl;
//
//
//        componentRepository.Clear();
//
//
//    }
//
//    // Calculate overall average durations
//    double avgAddDuration = 0.0, avgIterateDuration = 0.0, avgGetDuration = 0.0;
//    for (const auto& d : addDurations) avgAddDuration += d;
//    for (const auto& d : iterateDurations) avgIterateDuration += d;
//    for (const auto& d : getDurations) avgGetDuration += d;
//
//    avgAddDuration /= numRuns;
//    avgIterateDuration /= numRuns;
//    avgGetDuration /= numRuns;
//
//    // Calculate average per-component times across all runs
//    double avgPerComponentAddTime = 0.0, avgPerComponentIterateTime = 0.0, avgPerComponentGetTime = 0.0;
//    for (const auto& t : perComponentAddTimes) avgPerComponentAddTime += t;
//    for (const auto& t : perComponentIterateTimes) avgPerComponentIterateTime += t;
//    for (const auto& t : perComponentGetTimes) avgPerComponentGetTime += t;
//
//    avgPerComponentAddTime /= numRuns;
//    avgPerComponentIterateTime /= numRuns;
//    avgPerComponentGetTime /= numRuns;
//
//    // Display average times in milliseconds and nanoseconds with high precision
//    std::cout << std::fixed << std::setprecision(10);
//
//    std::cout << "\nAverage Time taken to add components over " << numRuns << " runs: "
//        << avgAddDuration << " ms (" << avgAddDuration * 1e6 / numComponents << " ns per component)" << std::endl;
//    std::cout << "Average Time taken to iterate and modify components over " << numRuns << " runs: "
//        << avgIterateDuration << " ms (" << avgIterateDuration * 1e6 / numComponents << " ns per component)" << std::endl;
//    std::cout << "Average Time taken to get components over " << numRuns << " runs: "
//        << avgGetDuration << " ms (" << avgGetDuration * 1e6 / numComponents << " ns per component)" << std::endl;
//
//    std::cout << "\nAverage per-component time taken to add components: "
//        << avgPerComponentAddTime << " ms (" << avgPerComponentAddTime * 1e6 << " ns)" << std::endl;
//    std::cout << "Average per-component time taken to iterate and modify components: "
//        << avgPerComponentIterateTime << " ms (" << avgPerComponentIterateTime * 1e6 << " ns)" << std::endl;
//    std::cout << "Average per-component time taken to get components: "
//        << avgPerComponentGetTime << " ms (" << avgPerComponentGetTime * 1e6 << " ns)" << std::endl;
//
//
//
//
//    return 0;
//}
//
//
//
////// Include generated headers (these should include components, factories, etc.)
////#include <iostream>
////#include <random>
////#include <chrono>  // For timing
////#include <iomanip> // For setting precision
////
////#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
////#pragma message("ankerl/unordered_dense.h included successfully")
////
////#include "component_framework/component_repository.h"
////#include "modules/TransformComponent.h"
////
////void ModifyComponent(TransformComponent* component, double multiplier) {
////    component->x *= multiplier;
////    component->y *= multiplier;
////    component->z *= multiplier;
////}
////
////int main() {
////    // Number of times each test will run
////    int numRuns = 100;  // You can adjust this value
////    int numComponents = 3000000;  // Number of components to create and add
////
////    // Simple output to verify that the system is working
////    std::cout << "ECSframework System Test - Main Executable" << std::endl;
////
////    // Timing results storage
////    std::vector<double> addDurations, iterateDurations, getDurations;
////    std::vector<double> perComponentAddTimes, perComponentIterateTimes, perComponentGetTimes;
////
////    // Random device and generator setup
////    std::random_device rd;
////    std::mt19937 gen(rd());  // Seed the generator
////    std::uniform_real_distribution<> dis(1.0, 10.0);  // Range [1, 10]
////
////    for (int run = 0; run < numRuns; ++run) {
////        std::cout << "\nRun #" << (run + 1) << ":\n";
////
////        ComponentRepository<uint32_t, TransformComponent> componentRepository;
////        componentRepository.ReserveSize(numComponents);
////
////        // Start timing for adding components
////        auto start = std::chrono::high_resolution_clock::now();
////        for (uint32_t i = 0; i < numComponents; ++i) {
////            TransformComponent component(i, i + 1, dis(gen), dis(gen), dis(gen));
////            componentRepository.AddComponent(std::move(component));
////        }
////        auto end = std::chrono::high_resolution_clock::now();
////        std::chrono::duration<double> duration = end - start;
////        addDurations.push_back(duration.count());
////        perComponentAddTimes.push_back(duration.count() / numComponents);
////
////        std::cout << "Time taken to add components: " << duration.count() << " seconds" << std::endl;
////
////        // Multiply all components by a factor (iteration test)
////        start = std::chrono::high_resolution_clock::now();
////        double multiplier = 10;
////        componentRepository.IterateAllComponentsMethod(&ModifyComponent, multiplier);
////        end = std::chrono::high_resolution_clock::now();
////        duration = end - start;
////        iterateDurations.push_back(duration.count());
////        perComponentIterateTimes.push_back(duration.count() / numComponents);
////        std::cout << "Time taken to iterate and modify components: " << duration.count() << " seconds" << std::endl;
////
////        // Performance test for GetComponent()
////        start = std::chrono::high_resolution_clock::now();
////        for (uint32_t i = 0; i < numComponents; ++i) {
////            uint32_t testID = i;  // Access each component by ID
////            TransformComponent* testComponent = componentRepository.GetComponent(testID);
////            if (testComponent) {
////                testComponent->x += 1.0;  // Small modification to prevent optimization
////            }
////        }
////        end = std::chrono::high_resolution_clock::now();
////        duration = end - start;
////        getDurations.push_back(duration.count());
////        perComponentGetTimes.push_back(duration.count() / numComponents);
////        std::cout << "Time taken to get components: " << duration.count() << " seconds" << std::endl;
////
////        componentRepository.Clear();
////    }
////
////    // Calculate overall average durations
////    double avgAddDuration = 0.0;
////    double avgIterateDuration = 0.0;
////    double avgGetDuration = 0.0;
////
////    for (const auto& d : addDurations) avgAddDuration += d;
////    for (const auto& d : iterateDurations) avgIterateDuration += d;
////    for (const auto& d : getDurations) avgGetDuration += d;
////
////    avgAddDuration /= numRuns;
////    avgIterateDuration /= numRuns;
////    avgGetDuration /= numRuns;
////
////    // Calculate average per-component times across all runs
////    double avgPerComponentAddTime = 0.0;
////    double avgPerComponentIterateTime = 0.0;
////    double avgPerComponentGetTime = 0.0;
////
////    for (const auto& t : perComponentAddTimes) avgPerComponentAddTime += t;
////    for (const auto& t : perComponentIterateTimes) avgPerComponentIterateTime += t;
////    for (const auto& t : perComponentGetTimes) avgPerComponentGetTime += t;
////
////    avgPerComponentAddTime /= numRuns;
////    avgPerComponentIterateTime /= numRuns;
////    avgPerComponentGetTime /= numRuns;
////
////    // Display average times with high precision
////    std::cout << std::fixed << std::setprecision(10);  // Set precision to 10 decimal places
////
////    std::cout << "\nAverage Time taken to add components over " << numRuns << " runs: "
////        << avgAddDuration << " seconds" << std::endl;
////    std::cout << "Average Time taken to iterate and modify components over " << numRuns << " runs: "
////        << avgIterateDuration << " seconds" << std::endl;
////    std::cout << "Average Time taken to get components over " << numRuns << " runs: "
////        << avgGetDuration << " seconds" << std::endl;
////
////    // Display per-component average processing time across all runs
////    std::cout << "\nAverage per-component time taken to add components: "
////        << avgPerComponentAddTime << " seconds" << std::endl;
////    std::cout << "Average per-component time taken to iterate and modify components: "
////        << avgPerComponentIterateTime << " seconds" << std::endl;
////    std::cout << "Average per-component time taken to get components: "
////        << avgPerComponentGetTime << " seconds" << std::endl;
////
////    return 0;
////}
//
//
////#include <iostream>
////#include <random>
////#include <chrono>  // For timing
////#include <iomanip> // For setting precision
////
////#include "external/ankerl/unordered_dense_install/include/ankerl/unordered_dense.h" // Correct path to the external header file.
////#pragma message("ankerl/unordered_dense.h included successfully")
////
////#include "component_framework/component_repository.h"
////#include "modules/TransformComponent.h"
////
////void ModifyComponent(TransformComponent* component, double multiplier) {
////    component->x *= multiplier;
////    component->y *= multiplier;
////    component->z *= multiplier;
////}
////
////int main() {
////    // Number of times each test will run
////    int numRuns = 100;  // You can adjust this value
////
////    // Simple output to verify that the system is working
////    std::cout << "ECSframework System Test - Main Executable" << std::endl;
////
////    // Timing results storage
////    std::vector<double> addDurations, iterateDurations, getDurations;
////
////    // Random device and generator setup
////    std::random_device rd;
////    std::mt19937 gen(rd());  // Seed the generator
////    std::uniform_real_distribution<> dis(1.0, 10.0);  // Range [1, 10]
////
//      
////    for (int run = 0; run < numRuns; ++run) {
////        std::cout << "\nRun #" << (run + 1) << ":\n";
////
////        ComponentRepository<uint32_t, TransformComponent> componentRepository;
////        int numComponents = 3000000;  // Number of components to create and add
////        componentRepository.ReserveSize(numComponents);
////
////        // Start timing for adding components
////        auto start = std::chrono::high_resolution_clock::now();
////        for (uint32_t i = 0; i < numComponents; ++i) {
////            TransformComponent component(i, i + 1, dis(gen), dis(gen), dis(gen));
////            componentRepository.AddComponent(std::move(component));
////        }
////        // End timing and calculate duration
////        auto end = std::chrono::high_resolution_clock::now();
////        std::chrono::duration<double> duration = end - start;
////        addDurations.push_back(duration.count());
////
////        // Display the time taken for the add process
////        std::cout << "Time taken to add components: " << duration.count() << " seconds" << std::endl;
////
////        // Multiply all components by a factor (iteration test)
////        start = std::chrono::high_resolution_clock::now();
////        double multiplier = 10;
////        componentRepository.IterateAllComponentsMethod(&ModifyComponent, multiplier);
////        end = std::chrono::high_resolution_clock::now();
////        duration = end - start;
////        iterateDurations.push_back(duration.count());
////        std::cout << "Time taken to iterate and modify components: " << duration.count() << " seconds" << std::endl;
////
////        // Performance test for GetComponent()
////        start = std::chrono::high_resolution_clock::now();
////        for (uint32_t i = 0; i < numComponents; ++i) {
////            uint32_t testID = i;  // Access each component by ID
////            TransformComponent* testComponent = componentRepository.GetComponent(testID);
////            if (testComponent) {
////                // Do something with the component to avoid compiler optimization removal
////                testComponent->x += 1.0;
////            }
////        }
////        end = std::chrono::high_resolution_clock::now();
////        duration = end - start;
////        getDurations.push_back(duration.count());
////        std::cout << "Time taken to get components: " << duration.count() << " seconds" << std::endl;
////
////        componentRepository.Clear();
////    }
////
////    // Calculate average durations
////    double avgAddDuration = 0.0;
////    double avgIterateDuration = 0.0;
////    double avgGetDuration = 0.0;
////
////    for (const auto& d : addDurations) avgAddDuration += d;
////    for (const auto& d : iterateDurations) avgIterateDuration += d;
////    for (const auto& d : getDurations) avgGetDuration += d;
////
////    avgAddDuration /= numRuns;
////    avgIterateDuration /= numRuns;
////    avgGetDuration /= numRuns;
////
////    // Display average times with high precision
////    std::cout << std::fixed << std::setprecision(10);  // Set precision to 10 decimal places
////
////    std::cout << "\nAverage Time taken to add components over " << numRuns << " runs: "
////        << avgAddDuration << " seconds" << std::endl;
////    std::cout << "Average Time taken to iterate and modify components over " << numRuns << " runs: "
////        << avgIterateDuration << " seconds" << std::endl;
////    std::cout << "Average Time taken to get components over " << numRuns << " runs: "
////        << avgGetDuration << " seconds" << std::endl;
//// 
//// 
////
////    return 0;
////
////}
////
