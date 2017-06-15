// HuffmanCodes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	int keyNum = -1; // store node number in huffman tree
	int i = 0; // iterator variable
	int counter = 0;
	vector<HuffmanNode> nodeVector;


	scanf_s("%d", &keyNum); // input key number

	while (keyNum != 0)
	{
		counter++;
		for (i = 0; i < keyNum; i++)
		{
			char key;
			int weight;
			rewind(stdin);
			scanf_s("%c %d", &key, 1, &weight);

			HuffmanNode newNode;  // new a huffman tree leaf node
			newNode.key = key;
			newNode.weight = weight;
			newNode.leftChild = NULL;
			newNode.rightChild = NULL;

			nodeVector.push_back(newNode);
		}

		sort(nodeVector.begin(), nodeVector.end(), compareWeight); // sort by weight, make huffman tree node order from weight low to weight high

		/*
			Build a huffman tree
		*/
		while (nodeVector.size() > 1)
		{
			HuffmanNode *newNode, *leftChild, *rightChild; // new a huffman tree node, not leaf
			newNode = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));  // must use calloc to create a new memory place
			leftChild = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
			rightChild = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
			newNode->key = '$'; // use '$' represent this is a node not leaf and either its left child nor right child not visited
			newNode->weight = nodeVector.at(0).weight + nodeVector.at(1).weight; // the new node weight equal to two leaf node total weight
			*leftChild = nodeVector.at(0);
			*rightChild = nodeVector.at(1);
			newNode->leftChild = leftChild;
			newNode->rightChild = rightChild;
			//newNode.leftChild = &nodeVector.at(0);
			//newNode.rightChild = &nodeVector.at(1);
			// remove the two nodes from nodesVector with the smallest weight
			vector<HuffmanNode>::iterator it = nodeVector.begin();
			nodeVector.erase(it);
			it = nodeVector.begin();
			nodeVector.erase(it);
			// push the new node into nodeVector
			nodeVector.push_back(*newNode);
			// sort by weight, make huffman tree node order from weight low to weight high
			sort(nodeVector.begin(), nodeVector.end(), compareWeight);
		}


		/*
			Use DFS Traversal to build each character's huffman code
		*/

		stack<HuffmanNode> VStack;
		deque<char> huffmanDeque;
		vector<HuffmanCode> huffmanCode;
		VStack.push(nodeVector.at(0));

		while (!VStack.empty())
		{
			HuffmanNode currentNode = VStack.top();
			if (currentNode.key == '$')
			{
				currentNode.key = '%'; // '%' represent its left child has visited
				VStack.pop();
				VStack.push(currentNode);
				VStack.push(*currentNode.leftChild);
				huffmanDeque.push_front('0'); // left code 0
			}
			else if (currentNode.key == '%') {
				currentNode.key = '^'; // '^' represent its childs all been visited
				VStack.pop();
				VStack.push(currentNode);
				VStack.push(*currentNode.rightChild);
				huffmanDeque.push_front('1'); // right code 1
			}
			else if (currentNode.key == '^') {
				if (VStack.size() != 1)
					huffmanDeque.pop_front();
				VStack.pop(); // up to its parent node
			}
			else { // traversal to the leaf
				HuffmanCode newCode;
				newCode.key = currentNode.key; // store the key
				for (deque<char>::reverse_iterator it = huffmanDeque.rbegin(); it != huffmanDeque.rend(); it++)
				{
					newCode.huffmanCode += *it; // build haffman code for the key
				}
				huffmanCode.push_back(newCode); // store the huffman code to vector
				huffmanDeque.pop_front(); // pop last code 
				VStack.pop(); // up to its parent node
			}
		}

		sort(huffmanCode.begin(), huffmanCode.end(), compareCharacter); // sort by character for print them out



		/*
			De huffman code by using huffman tree
		*/
		string dehuffmanCode;
		rewind(stdin);
		cin >> dehuffmanCode;
		string outputString;
		HuffmanNode root = nodeVector.at(0);
		HuffmanNode currentNode = root;
		//for (string::iterator it = dehuffmanCode.begin(); it != dehuffmanCode.end(); it++)
		for (int i = 0; i <= dehuffmanCode.length(); i++)
		{
			if (currentNode.key != '$') // if current node is leaf
			{
				outputString += currentNode.key;
				currentNode = root;
				if (i == dehuffmanCode.length())
					break;
			}
			//if (*it == '0')	// code '0' move left
			if (dehuffmanCode[i] == '0')
			{
				currentNode = *currentNode.leftChild;
			}
			//else if (*it == '1') { // code '1' move right
			else if (dehuffmanCode[i] == '1') {
				currentNode = *currentNode.rightChild;
			}
			else {
				cout << "error" << endl;
				exit(1);
			}
		}
		cout << "Huffman Codes #" << counter << endl;
		/*
			 printf huffman codes
		*/
		for (vector<HuffmanCode>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); it++)
		{
			cout << it->key << " " << it->huffmanCode << endl;
		}
		/*
			printf decode
		*/
		cout << "Decode=" << outputString << endl;

		rewind(stdin);
		scanf_s("%d", &keyNum);
	}
	system("pause");
	return 0;
}

bool compareWeight(const HuffmanNode &a, const HuffmanNode &b)
{
	return a.weight < b.weight;
}

bool compareCharacter(const HuffmanCode &a, const HuffmanCode &b)
{
	return a.key < b.key;
}

