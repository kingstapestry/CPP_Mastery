#include "Task.h"

#include "MyCPPUtils/menu/DynamicMenu.h"
#include "MyCPPUtils/console/Console.h"

int main() {
	Data::Manager<Task> tasks;
	Menu::DynamicMenu menu;

	std::cout << R"(
 _   _ _______  ___   _ ____     ____ _     ___ 
 | \ | | ____\ \/ / | | / ___|   / ___| |   |_ _|
 |  \| |  _|  \  /| | | \___ \  | |   | |    | | 
 | |\  | |___ /  \| |_| |___) | | |___| |___ | | 
 |_| \_|_____/_/\_\\___/|____/   \____|_____|___|
                                                 

)";

	menu.add("Add Task", [&] {
		Console::clear();
		Console::title("New Task");

		std::string title = Utils::inputLine("Enter title: ");
		Task t(title);
		Console::success(title + " created");

		std::string description = Utils::inputLine("Enter description: ");
		t.setDescription(description);
		
		int priority = 0;
		do {
			priority = Utils::inputInt("Enter priority (1 = Low, 2 = Medium, 3 = High): ");
		} while (priority < 1 || priority > 3);

		if (priority == 1) t.setPriority(Priority::Low);
		else if (priority == 2) t.setPriority(Priority::Medium);
		else if (priority == 3) t.setPriority(Priority::High);

		t.setStatus(Status::Pending);

		t.displayTask();

		tasks.add(t);
		Console::success(title + " added to task list");
		});

	menu.add("Display All Tasks", [&] {
		Task::displayAllTasks(tasks);
		});

	menu.addExit();
	menu.run();
	
	return 0;
}