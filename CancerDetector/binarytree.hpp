/*!	\file	binarytree.hpp
	\brief	class for binary decision tree structure.
	\author	Ethan Rivers
	\date	2023-11-22
*/
#pragma once
#include <iostream>
#include <functional>
#include <optional>
#include "patient.hpp"

template <typename T>
class BinaryDecisionTree {

	struct Node {
		Node* leftChild;
		Node* rightChild;
		std::function<bool(const T&)> condition; // each node will hold a fucntion 
		std::optional<int> classification; // will contain 2(benign) or 4(malignant) only for leaf nodes

		/* ctor that accpets a function which will be used to compare a patients atttribute to nodes condition */
		Node(std::function<bool(const T&)> conditionFunc)
			: condition(conditionFunc), leftChild(nullptr), rightChild(nullptr) {}

		/* leaf node ctor (will not contain any condtion just a 2 for benign or 4 for malignant */
		Node(int classif)
			: condition(nullptr), leftChild(nullptr), rightChild(nullptr), classification(classif) {}


		bool isLeaf() const {
			return classification.has_value();
		}

	};

	/*
	@name free_node
	@param Node*
	@return void
	*/
	void free_node(Node* node)
	{
		if (!node) return;
		free_node(node->leftChild);
		free_node(node->rightChild);
		delete node;
	}

	/*
	@name generateNodes
	@param void
	@return Node*
	@note builds the tree structure stuffing each node with a function that patients 
		  will be compared against. returns the head of the tree once done building tree.
	*/
	Node* generateNodes() {
		// conditions that will each patient will later be tested against
		auto c1 = [](const Patient& p) { return p.cellsizeunif() <= 2; };
		auto c2 = [](const Patient& p) { return p.barenuclei() <= 3; };
		auto c3 = [](const Patient& p) { return p.cellshapeunif() <= 2; };
		auto c4 = [](const Patient& p) { return p.clumpthickness() <= 3; };
		auto c5 = [](const Patient& p) { return p.clumpthickness() <= 5; };
		auto c6 = [](const Patient& p) { return p.cellsizeunif() <= 4; };
		auto c7 = [](const Patient& p) { return p.blandchromatin() <= 2; };
		auto c8 = [](const Patient& p) { return p.barenuclei() <= 2; };
		auto c9 = [](const Patient& p) { return p.adhesion() <= 3; };
		auto c10 = [](const Patient& p) { return p.clumpthickness() <= 6; };
		auto c11 = [](const Patient& p) { return p.cellsizeunif() <= 3; };
		auto c12 = [](const Patient& p) { return p.adhesion() <= 5; };

		// starting backwards to code this easier
		Node* n13 = new Node(c12); // adhesion <= 5
		n13->leftChild = new Node(2);
		n13->rightChild = new Node(4);

		Node* n12 = new Node(c11); // unif cell size <= 3
		n12->leftChild = new Node(4);
		n12->rightChild = n13;

		Node* n11 = new Node(c10); // clump thickness <= 6
		n11->leftChild = n12;
		n11->rightChild = new Node(4);

		Node* n10 = new Node(c9); // adhesion <= 3
		n10->leftChild = new Node(2);
		n10->rightChild = new Node(4);

		Node* n9 = new Node(c8); // bare nuclei <= 2
		n9->leftChild = n10;
		n9->rightChild = n11;

		Node* n8 = new Node(c6); // unif cell size <= 4
		n8->leftChild = n9;
		n8->rightChild = new Node(4);

		Node* n7 = new Node(c5); // clump thickness <= 5
		n7->leftChild = new Node(2);
		n7->rightChild = new Node(4);

		Node* n6 = new Node(c3); // unif cell shape <= 2
		n6->leftChild = n7;
		n6->rightChild = n8;

		// LEFT BRANCH BOTTOM UP
		Node* n5 = new Node(c9); // adhesion <= 3
		n5->leftChild = new Node(4);
		n5->rightChild = new Node(2);

		Node* n4 = new Node(c7); // bland chromatin <= 2
		n4->leftChild = n5;
		n4->rightChild = new Node(4);

		Node* n3 = new Node(c4); // clump thickness <= 3
		n3->leftChild = new Node(2);
		n3->rightChild = n4;

		Node* n2 = new Node(c2); // bare nuclei <= 3
		n2->leftChild = new Node(2);
		n2->rightChild = n3;

		Node* root = new Node(c1); // unif cell size <= 2
		root->leftChild = n2;
		root->rightChild = n6;

		return root;
	}

	void buildTree() { rootNode_ = generateNodes(); }

	Node* rootNode_;

public:

	~BinaryDecisionTree() {
		free_node(rootNode_);
		rootNode_ = nullptr;
	}

	/* default ctor*/
	BinaryDecisionTree() { buildTree(); }



	/*
	@name getTypeOfCancer
	@param const Patient&
	@author Ethan Rivers
	@note traverses the tree comparing a patient against node conditions.
		  will determine if the cancer is benign or malignant
	*/
	int getTypeOfCancer(const Patient& p) {
		if (!rootNode_)
			exit(EXIT_FAILURE);

		Node* current = rootNode_;

		while (!current->isLeaf()) {
			if (current->condition(p))
				current = current->leftChild;
			else
				current = current->rightChild;
		}

		return current->classification.value_or(-1);

	}


};