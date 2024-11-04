#include <gtest/gtest.h>
#include "component_repository.h"  // Include the headers for your ECS
#include "TransformComponent.h"

TEST(ComponentRepositoryTest, AddAndGetComponent) {
    // Example test for adding a component and retrieving it
    ComponentRepository<TransformComponent, uint16_t> repo;
    TransformComponent component1 = TransformComponent(1, 0, 0, 0, 0);
    repo.AddComponent(component1);

    EXPECT_EQ(repo.GetComponent(1).componentID, 1);  // Assert the component was added correctly
}