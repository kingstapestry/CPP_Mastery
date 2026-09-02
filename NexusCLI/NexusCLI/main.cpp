#include "Task.h"
#include "TaskManager.h"

#include "MyCPPUtils/menu/DynamicMenu.h"
#include "MyCPPUtils/console/Console.h"

int main() {
	std::cout << R"(
 _   _ _______  ___   _ ____     ____ _     ___ 
 | \ | | ____\ \/ / | | / ___|   / ___| |   |_ _|
 |  \| |  _|  \  /| | | \___ \  | |   | |    | | 
 | |\  | |___ /  \| |_| |___) | | |___| |___ | | 
 |_| \_|_____/_/\_\\___/|____/   \____|_____|___|
                                                 

)";

	Data::Manager<Task> tasks;
	Menu::DynamicMenu menu;

	std::cout << "Loading existing tasks...\n";
	TaskManager::loadTasks(tasks);

	menu.add("Add Task", [&] {
		Console::clear();
		Console::title("New Task");

		std::string title = Utils::inputLine("Enter title: ");
		Task t(title);

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

	menu.add("Complete Task", [&] {
		int id = Utils::inputInt("Enter ID: ");

		auto found = tasks.findIf([id](const Task& t) {
			return t.getId() == id;
			});
		if (!found) {
			Console::error("No tasks with matching ID found");
			return;
		}

		found->setStatus(Status::Completed);

		bool success = tasks.updateIf(
			[id](const Task& t) { return t.getId() == id; },
			*found
		);
		if (!success) {
			Console::error("Failed to set task to completed");
			return;
		}
		found->displayTask();
		Console::success("Task set to completed");
		});

	menu.add("Delete Task", [&] {
		int id = Utils::inputInt("Enter ID: ");

		auto found = tasks.findIf([id](const Task& t) {
			return t.getId() == id;
			});
		if (!found) {
			Console::error("No tasks with matching ID found");
			return;
		}

		if (Utils::confirm()) {
			bool removed = tasks.removeIf([id](const Task& t) {
				return t.getId() == id;
				});
			if (!removed) {
				Console::error("Failed to delete task");
				return;
			}
			Console::success("Task deleted");
		}
		});

	menu.add("Edit Task", [&] {
		int id = Utils::inputInt("Enter ID: ");

		// Get a copy of the task
		auto found = tasks.findIf([id](const Task& t) {
			return t.getId() == id;
			});
		if (!found) {
			Console::error("No tasks with matching ID found");
			return;
		}
		found->displayTask();

		// Modify the copy
		std::string title = Utils::inputLine("Enter new title: ");
		found->setTitle(title);

		std::string description = Utils::inputLine("Enter new description: ");
		found->setDescription(description);

		int priority = 0;
		do {
			priority = Utils::inputInt("Enter new priority (1 = Low, 2 = Medium, 3 = High): ");
		} while (priority < 1 || priority > 3);

		if (priority == 1) found->setPriority(Priority::Low);
		else if (priority == 2) found->setPriority(Priority::Medium);
		else if (priority == 3) found->setPriority(Priority::High);

		// Write it back
		bool success = tasks.updateIf(
			[id](const Task& t) { return t.getId() == id; },
			*found
		);
		if (!success) {
			Console::error("Failed to update task");
			return;
		}
		found->displayTask();
		Console::success("Task updated");
		});

	menu.addExit();
	menu.run();

	std::cout << "Saving existing tasks...\n";
	TaskManager::saveTasks(tasks);
	
	return 0;
}