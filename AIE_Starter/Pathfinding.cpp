#include "Pathfinding.h"

#include <algorithm>
#include <iostream>

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

void NodeMap::Initialise(TileMap* tileMap, int tileSize)
{
	m_cellSize = tileSize/2 ;

	const int grassID = 0; const int dirtID = 1; const int brickID = 2; const int waterID = 3;
	const int grassCost = 2; const int dirtCost = 1;

	m_height = tileMap->mapSize * 2;
	m_width = tileMap->mapSize * 2;

	m_nodes = new Node * [m_width * m_height];

	for (int y = 0; y < m_height; y++)
	{
		//int line[COLS];
		//for (int i = 0; i < COLS; i++) 
		//{ 
		//	line[i] = tileMap->map[y/2][i/2]; 
		//}

		for (int x = 0; x < m_width; x++)
		{
			//int tile = line[x/2];
			int tile = tileMap->map[y / 2][x / 2];

			switch (tile)
			{
			case 0:
				m_nodes[x + m_width * y] = new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
				m_nodes[x + m_width * y]->gScore = grassCost;
				break;
			case 1:
				m_nodes[x + m_width * y] = new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
				m_nodes[x + m_width * y]->gScore = dirtCost;
				break;
			case 2: 
			case 3:
				m_nodes[x + m_width * y] = nullptr;
				break;
			default:
				break;
			}
		}

	}

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					node->ConnectTo(nodeWest, nodeWest->gScore);
					nodeWest->ConnectTo(node, node->gScore);
				}
				
				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, nodeSouth->gScore);
					nodeSouth->ConnectTo(node, node->gScore);
				}
			}
		}
	}
}

AIForGames::Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int i = static_cast<int>(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;
	int j = static_cast<int>(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_height) return nullptr;
	return GetNode(i, j);
}

void NodeMap::Draw()
{
	

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				/*DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize - 1, (int)m_cellSize - 1, BLACK);*/
			}
			else
			{
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, LIGHTGRAY);
				}
			}
		}
	}
}

void NodeMap::DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor, float lineThickness)
{

	for (int i = 1; i < nodeMapPath.size(); ++i)
	{
		Node* prevNode = nodeMapPath.at(i - 1);	//placeholder variable to store the previous node aka the start of the path
		Node* curNode = nodeMapPath.at(i);	//placeholder variable to store the current node in the path

		//Drawing from last node to current node
		DrawLineEx(Vector2{ prevNode->position.x, prevNode->position.y }, Vector2{ curNode->position.x, curNode->position.y }, lineThickness, lineColor);
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

		if (currentNode == endNode)
		{
			break;
		}

		openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());  
		closedList.push_back(currentNode);

		for (int c = 0; c < currentNode->connections.size(); c++)
		{
			Node* tempNode = currentNode->connections.at(c).target;
			if (std::find(closedList.begin(), closedList.end(), tempNode ) == closedList.end())//checking that the currentNode doesn't exist in closedList 
			{
				float gScore = currentNode->gScore + currentNode->connections.at(c).cost;

				if (std::find(openList.begin(), openList.end(), tempNode) == openList.end())//checking that the tempNode doesn't exist in openList
				{
					tempNode->gScore = gScore;
					tempNode->previous = currentNode;
					openList.push_back(tempNode);
				}
				else if (gScore < tempNode->gScore)
				{
					tempNode->gScore = gScore;
					tempNode->previous = currentNode;
				}
			}
		}
	}

	if (openList.empty()) return {};
	else {

		std::vector<Node*> Path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			Path.insert(Path.begin(), currentNode);
			currentNode = currentNode->previous;
		}
		return Path;
	}

}

void PathAgent::Update(float deltaTime)
{
	if (m_path.empty()) return;
	
	int distance = m_speed * deltaTime;

	if (distance > 0)
	{
		glm::vec2 targetPos = m_currentNode->connections.back().target->position;
		glm::dot(m_position, targetPos);
	}
	else
	{
		m_currentIndex++;
		if (m_currentNode == m_path.front())
		{
			m_position = m_path.front()->position;
			m_path.clear();
		}
		else
		{
			distance = distance - m_speed * deltaTime;
			m_position -= m_currentNode->position;
		}
	}
}

void PathAgent::GoToNode(AIForGames::Node* node)
{
	m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::SetNode(AIForGames::Node* node)
{
	m_currentNode = node;
	m_position = node->position;
}

void PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}

void PathAgent::Draw()
{
	DrawCircleV(Vector2(m_position.x, m_position.y), 8, ORANGE);
}
