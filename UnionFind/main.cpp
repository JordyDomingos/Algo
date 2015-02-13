#include <vector>
#include <iostream>

struct UnionObject {
	int id;
	int root_id;
	int size_of_union;
};

// A weighted, path compressed version of UnionFind algorithm.
class UnionFind {

public:
	UnionFind(int num_elements) : union_vector_(num_elements) {
		int i = 0;
		for (auto &union_object : union_vector_) {
			union_object.id = i;
			union_object.root_id = i;
			union_object.size_of_union = 1;
			++i;
		}
	}

	void Union(int id_obj1, int id_obj2) {
		int root_id_obj1 = Root(id_obj1);
		int root_id_obj2 = Root(id_obj2);

		// We use the number of elements to weight the tree.
		if (union_vector_[root_id_obj1].size_of_union > union_vector_[root_id_obj2].size_of_union) {
			union_vector_[root_id_obj2].root_id = union_vector_[root_id_obj1].root_id;
			union_vector_[root_id_obj1].size_of_union += union_vector_[root_id_obj2].size_of_union;
		} else {
			union_vector_[root_id_obj1].root_id = union_vector_[root_id_obj2].root_id;
			union_vector_[root_id_obj2].size_of_union += union_vector_[root_id_obj1].size_of_union;	
		}
	}

	int Root(int id) {
		if (union_vector_[id].root_id == id)
			return id;
		// Path compression here (we use the object "grand root").
		union_vector_[id].root_id = union_vector_[union_vector_[id].root_id].id;
		return Root(union_vector_[id].root_id);
	}

	bool IsConnected(int id1, int id2) {
		return Root(id1) == Root(id2);
	}

	~UnionFind() {
		union_vector_.clear();
	}


private:
	UnionFind();

	std::vector<struct UnionObject> union_vector_;
};

int const kUnionArraySize = 10;

int main() {
	UnionFind union_find(kUnionArraySize);
	union_find.Union(5, 3);
	union_find.Union(1, 2);
	union_find.Union(1, 6);
	union_find.Union(1, 3);	
	std::cout << "Is IsConnected : " << union_find.IsConnected(5, 3) << std::endl;
	std::cout << "Is IsConnected : " << union_find.IsConnected(1, 5) << std::endl;
	std::cout << "Is IsConnected : " << union_find.IsConnected(5, 8) << std::endl;
}