#include "QuadTree.h"
using namespace NCL;

template<class T>
inline void NCL::CSC8503::QuadTreeNode<T>::OperateOnContents(QuadTreeFunc& func) {
	if (children) {
		for (int i = 0; i < 4; ++i) {
			children[i].OperateOnContents(func);
		}
	}
	else {
		if (!contents.empty()) {
			func(contents);
		}
	}
}

template<class T>
void NCL::CSC8503::QuadTreeNode<T>::Split() {
	Vector2 halfSize = size / 2.0f;
	children = new QuadTreeNode <T >[4];
	children[0] = QuadTreeNode <T>(position + Vector2(-halfSize.x, halfSize.y), halfSize);
	children[1] = QuadTreeNode <T>(position + Vector2(halfSize.x, halfSize.y), halfSize);
	children[2] = QuadTreeNode <T>(position + Vector2(-halfSize.x, -halfSize.y), halfSize);
	children[3] = QuadTreeNode <T>(position + Vector2(halfSize.x, -halfSize.y), halfSize);
}

template<class T>
void NCL::CSC8503::QuadTreeNode<T>::Insert(T& object, const Vector3& objectPos, const Vector3& objectSize, int depthLeft, int maxSize) {
	if (!CollisionDetection::AABBTest(objectPos,
		Vector3(position.x, 0, position.y), objectSize,
		Vector3(size.x, 1000.0f, size.y))) {
		return;
	}
	if (children) { //not a leaf node , just descend the tree
		for (int i = 0; i < 4; ++i) {
			children[i].Insert(object, objectPos, objectSize, depthLeft - 1, maxSize);
		}
	}
	else { // currently a leaf node , can just expand
		contents.push_back(QuadTreeEntry <T>(object, objectPos, objectSize));
		if ((int)contents.size() > maxSize && depthLeft > 0) {
			if (!children) {
				Split();
				//we need to reinsert the contents so far!
					for (const auto& i : contents) {
					for (int j = 0; j < 4; ++j) {
						auto entry = i;
						children[j].Insert(entry.object, entry.pos, entry.size, depthLeft - 1, maxSize);
					}
				}
				contents.clear(); // contents now distributed!
			}
		}
	}
}