// ECSframework.cpp : Defines the entry point for the application.
//

#include "ECSframework.h"
#include "component_repository.h"
#include "TransformComponent.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	ComponentRepository<TransformComponent, uint16_t> componentRepository;
	TransformComponent testComponent1 = TransformComponent(1, 0, 0, 0, 0);
	componentRepository.AddComponent(testComponent1);
	if (componentRepository.GetComponent(0).componentID == 1) {
		cout << "This is the right component" << endl;
	}
	return 0;
}
