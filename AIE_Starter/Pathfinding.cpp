#include "Pathfinding.h"

#include <algorithm>
#include <iostream>
#include <ppltasks.h>
#include <raylib.h>

using namespace AIForGames;

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySquare = '0';

	m_height = static_cast<int>(asciiMap.size());
	m_width = static_cast<int>(asciiMap[0].size());

	m_nodes = new Node* [ m_width * m_height ];

	for (int y = 0; y < m_height; y++)
	{
		std::string& line = asciiMap[y];

		if(line.size() != m_width)
		{
			std::cout << "Mismatched line number " << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")\n";
		}

		for (int x = 0; x < m_width; x++)
		{
			char tile = x < line.size() ? line[x] : emptySquare;

			m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
				: new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
		}

	}
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if(node)
			{
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	Color cellColor;
	cellColor.a = 255;
	cellColor.r = 255;
	cellColor.g = 0;
	cellColor.b = 0;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
			}
			else
			{
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, GOLD);
				}
			}
		}
	}
}

bool compareGScore(const Node* n1, const Node* n2) { return n1->gScore < n2->gScore; }

std::vector<AIForGames::Node*> NodeMap::DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode)
{
	if (startNode == nullptr || endNode == nullptr)
	{
		std::cout << "Error! Either the start node or end node for Dijkstra's Search is NULL! Line 95 Pathfinding.cpp\n";
	}
	if (startNode == endNode) return {};

	startNode->gScore = 0;
	startNode->previous = nullptr;

	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	openList.insert(openList.begin(), startNode);
	while(openList.empty() == false)
	{
		std::sort(openList.begin(), openList.end(), compareGScore);
		Node* currentNode = openList.front();

		if (currentNode == endNode) { break; }

		openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
		closedList.push_back(currentNode);

		/*for(std::vector<Edge>::iterator c = currentNode->connections.begin(); c!= currentNode->connections.end(); ++c)
		{
			std::vector<Node*>::iterator it = std::find(closedList.begin(), closedList.end(), c->target);
			if (it != closedList.end())
			{
				float gScore = currentNode->gScore + c->cost;
				if ((std::find(openList.begin(), openList.end(), c))!= openList.end())
				{
					c->target->gScore = gScore;
					c->target->previous = currentNode;
					openList.push_back(c->target);
				}
				else if (gScore < c->target->gScore)
				{
					c->target->gScore = gScore;
					c->target->previous = currentNode;
				}
				
			}
		}*/
		for (int c = 0; c < currentNode->connections.size(); c++)
		{
			if (std::find(closedList.begin(), closedList.end(), currentNode->connections.at(c).target ) != closedList.end())
			{
				float gScore = currentNode->gScore + currentNode->connections.at(c).cost;

				if (std::find(openList.begin(), openList.end(), currentNode->connections.at(c).target) != openList.end())
				{
					currentNode->connections.at(c).target->gScore = gScore;
					currentNode->connections.at(c).target->previous = currentNode;
					openList.push_back(currentNode->connections.at(c).target);
				}
				else if (gScore < currentNode->connections.at(c).target->gScore)
				{
					currentNode->connections.at(c).target->gScore = gScore;
					currentNode->connections.at(c).target->previous = currentNode;
				}
			}
		}
	}
	std::vector<Node*> Path;
	Node* currentNode = endNode;
	while (currentNode != nullptr)
	{
		Path.insert(Path.begin(), currentNode);
		currentNode = currentNode->previous;
	}

	return Path;
}
