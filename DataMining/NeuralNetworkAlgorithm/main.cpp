#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<std::pair<std::string, int>>> tuples = {
	{{"x0", -1}, {"x1", 0}, {"x2", 0}, {"t", 0}},
	{{"x0", -1}, {"x1", 0}, {"x2", 1}, {"t", 0}},
	{{"x0", -1}, {"x1", 1}, {"x2", 0}, {"t", 0}},
	{{"x0", -1}, {"x1", 1}, {"x2", 1}, {"t", 1}}
};

std::vector<std::pair<std::string, float>> weights = {
	{"x0", -0.2},
	{"x1", -0.1},
	{"x2", -0.2}	
};

constexpr float kLearningRate = 0.1;

int ActivationFunction(float weighted_sum) {
	if (weighted_sum > 0.0)
		return 1;
	return 0;
}

bool CompareName(std::string variable_name, std::pair<std::string, float> weight) {
	if (variable_name == weight.first)
		return true;
	return false;
}

float FindVariableWeight(std::string variable_name, 
	std::vector<std::pair<std::string, float>> weights) {
	for (auto pair : weights) {
		if (pair.first == variable_name)
			return pair.second;
	}
	// Value to notify the user that there is an issue.
	return 98990.0;
}

void SimpleNNPerceptronTrainingAlgorithm(
	std::vector<std::vector<std::pair<std::string, int>>> tuples,
	std::vector<std::pair<std::string, float>> weights,
	std::function<int(float)> const &activation_function,
	float const &learning_rate) {
	int nb_consecutive_successes = 0;
	int nb_iteration = 1;

	// We want a 0% error rate therefor, if nb_consecutive_successes is greater or equal to
	// the number of tuples, it means that our classification is correct for all the tuples.
	while (nb_consecutive_successes < tuples.size()) {
		for (auto tuple : tuples) {
			float weighted_sum = 0.0;
			for (auto variable : tuple) {
				if (variable != (*(tuple.end() - 1))) {
					float variable_weight = FindVariableWeight(variable.first, weights);
					weighted_sum += (float)variable.second * variable_weight;
				}
			}
			int output = activation_function(weighted_sum);
			int expected_output = (*(tuple.end() - 1)).second;
			if (output != expected_output) {
				// We ajust the weights here.
				auto attributes = tuple.begin();
				for (auto &weight : weights) {
					float delta_weight = learning_rate * (float)(expected_output - output)
										* (float)(*attributes).second;
					weight.second = weight.second + delta_weight;
					++attributes;
				}
				nb_consecutive_successes = 0;
			} else {
				nb_consecutive_successes += 1;
			}
		}
		++nb_iteration;
	}
}

int main() {
	SimpleNNPerceptronTrainingAlgorithm(tuples, weights, ActivationFunction, kLearningRate);
}

