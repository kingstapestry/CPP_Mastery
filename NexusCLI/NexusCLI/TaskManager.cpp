#include "TaskManager.h"
#include "Task.h"

#include "MyCPPUtils/common/Utils.h"
#include "MyCPPUtils/console/Console.h"

const std::string DATA_FILE = "data/tasks.txt";

bool TaskManager::loadTasks(Data::Manager<Task>& tasks) {
	std::string content = Utils::readFromFile(DATA_FILE);

	if (content.empty()) {
		return false;										// empty or file doesn't exist
	}
	
	std::stringstream ss(content);
	std::string line;
	int highestId = 0;

	while (std::getline(ss, line)) {
		if (line.empty()) continue;

		Task t = Task::fromFileString(line);

		if (t.getId() > highestId) {
			highestId = t.getId();
		}

		tasks.add(t);
	}

	Task::setNextId(highestId + 1);
	return true;
}

bool TaskManager::saveTasks(const Data::Manager<Task>& tasks) {
	std::string fileContent;

	for (const auto& task : tasks.all()) {
		fileContent.append(task.toFileString()).append("\n");
	}

	auto run = Utils::writeToFile(DATA_FILE, fileContent);

	if (!run) {
		Console::error("Unable to write to file");
		return false;
	}

	Console::success("Successfully written to file");
	return true;
}