#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <map>
//
///* FOR DELETING */
//enum class TaskStatus {
//	NEW,
//	IN_PROGRESS,
//	TESTING,
//	DONE
//};
//
//using TasksInfo = std::map<TaskStatus, int>;
///* FOR DELETING */


TaskStatus GetNextTaskStatus(const TaskStatus& taskStatus) {
	switch (taskStatus) {
		case TaskStatus::NEW:
			return TaskStatus::IN_PROGRESS;
		case TaskStatus::IN_PROGRESS:
			return TaskStatus::TESTING;
		default:
			return TaskStatus::DONE;
	}
}

//Класс, позволяющий хранить статистику по статусам задач команды разработчиков.
class TeamTasks {
private:
	std::map<std::string, TasksInfo> m_tasks {};

public:
	//Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
		return m_tasks.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person) {
		m_tasks[person][TaskStatus::NEW]++;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
		TasksInfo changeable, updatedTasks, untouchedTasks;

		try {
			changeable = GetPersonTasksInfo(person);
		} catch (const std::out_of_range&) {
			return std::make_tuple(updatedTasks, untouchedTasks);
		}

		for (const auto& ts : { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING }) {
			const TaskStatus tsNext = GetNextTaskStatus(ts);
			const int count = changeable[ts];

			int x = count - updatedTasks[ts];

			if (count == 0) {
				updatedTasks[ts] = 0;
				untouchedTasks[ts] = 0;
				continue;
			} else if (x == 0) {
				untouchedTasks[ts] = 0;
				continue;
			}//fi

			int c = task_count - x;

			if (c > 0) {
				changeable[ts] -= x;
				changeable[tsNext] += x;

				untouchedTasks[ts] = 0;
				updatedTasks[tsNext] = x;

				task_count = c;
			} else if (c == 0) {
				changeable[ts] -= task_count;
				changeable[tsNext] += task_count;

				untouchedTasks[ts] = 0;
				updatedTasks[tsNext] = task_count;

				task_count = c;
			} else if (c < 0) {
				changeable[ts] -= task_count;
				changeable[tsNext] += task_count;

				untouchedTasks[ts] = x - task_count;
				updatedTasks[tsNext] = task_count;

				task_count = 0;
			}//fi
		}//rof

		for (TaskStatus ts = TaskStatus::NEW; ; ts = GetNextTaskStatus(ts)) {
			if (updatedTasks[ts] == 0) updatedTasks.erase(ts);
			if (untouchedTasks[ts] == 0) untouchedTasks.erase(ts);
			if (changeable[ts] == 0) changeable.erase(ts);
			if (ts == TaskStatus::DONE) break;
		}

		m_tasks[person].clear();
		m_tasks[person] = changeable;

		return std::make_tuple(updatedTasks, untouchedTasks);
	}
};

//
///* FOR DELETING */
//void PrintTasksInfo(const TasksInfo& tasks_info) {
//	if (tasks_info.count(TaskStatus::NEW)) {
//		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
//	}
//	if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
//		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
//	}
//	if (tasks_info.count(TaskStatus::TESTING)) {
//		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
//	}
//	if (tasks_info.count(TaskStatus::DONE)) {
//		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
//	}
//}
//
//void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
//	std::cout << "Updated: [";
//	PrintTasksInfo(updated_tasks);
//	std::cout << "] ";
//
//	std::cout << "Untouched: [";
//	PrintTasksInfo(untouched_tasks);
//	std::cout << "] ";
//
//	std::cout << std::endl;
//}
//
//int main() {
//	using namespace std;
//	TeamTasks tasks;
//	TasksInfo updated_tasks;
//	TasksInfo untouched_tasks;
//
//	/* TEST 0 */
//	std::cout << "Bubuka" << std::endl;
//
//	for (auto i = 0; i < 1; ++i) {
//		tasks.AddNewTask("Bubuka");
//	}
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bubuka", 2);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Bubuka"));  // { "IN_PROGRESS": 1 }
//	std::cout << std::endl << std::endl;
//
//
//	/* TEST 1 */
//	std::cout << "Alice" << std::endl;
//
//	for (auto i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Alice");
//	}
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
//
//	for (auto i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Alice");
//	}
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
//	PrintTasksInfo(updated_tasks, untouched_tasks);
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
//	std::cout << std::endl;
//
//	/* TEST 2 */
//	std::cout << "\nJack" << std::endl;
//
//	tasks.AddNewTask("Jack");
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
//
//	tasks.AddNewTask("Jack");
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]
//
//	tasks.AddNewTask("Jack");
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
//	std::cout << std::endl;
//
//	/* TEST 3 */
//	std::cout << "\nLisa" << std::endl;
//
//	for (auto i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Lisa");
//	}
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
//
//	for (auto i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Lisa");
//	}
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
//	std::cout << std::endl;
//
//	tasks.AddNewTask("Lisa");
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
//
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
//	std::cout << std::endl;
//
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
//	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
//
//	return 0;
//}/* FOR DELETING */
