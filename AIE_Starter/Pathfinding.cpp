#include "Pathfinding.h"

#include <algorithm>
#include <iostream>

using namespace AIForGames;

NodeMap::~NodeMap()
{
	for (int i = 0; i < m_width * m_height; i++) {
		delete m_nodes[i];
	}
	delete[] m_nodes;
}

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
	m_cellSize = tileSize / 2;

	const int grassID = 0; const int dirtID = 1; const int brickID = 2; const int waterID = 3;
	const int grassCost = 2; const int dirtCost = 1; const int waterCost = 4;

	/*m_height = tileMap->mapSize * 2;
	m_width = tileMap->mapSize * 2;*/

	m_height = TM_ROWS * 2;
	m_width = TM_COLS * 2;

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
				m_nodes[x + m_width * y]->nodeID = grassID;
				break;
			case 1:
				m_nodes[x + m_width * y] = new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
				m_nodes[x + m_width * y]->nodeID = dirtID;
				break;
			case 2:
				m_nodes[x + m_width * y] = nullptr;
				break;
			case 3:
				m_nodes[x + m_width * y] = new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
				m_nodes[x + m_width * y]->nodeID = waterID;
			default:
				break;
			}
		}
	}

	/*for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				int nodeCost = node->nodeID == 0 ? grassCost : dirtCost;
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					int nodeWestCost = node->nodeID == 0 ? grassCost : dirtCost;
					node->ConnectTo(nodeWest, nodeWestCost);
					nodeWest->ConnectTo(node, nodeCost);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					int nodeSouthCost = node->nodeID == 0 ? grassCost : dirtCost;
					node->ConnectTo(nodeSouth, nodeSouthCost);
					nodeSouth->ConnectTo(node, nodeCost);
				}
			}
		}
	}*/

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				int nodeCost;
				int nodeWestCost;
				int nodeEastCost;
				int nodeSouthCost;

				//int nodeNorthCost;

				switch (node->nodeID)
				{
				case grassID:
					nodeCost = grassCost;
					break;
				case dirtID:
					nodeCost = dirtCost;
					break;
				case waterID:
					nodeCost = waterCost;
					break;
				default:
					std::cout << "ERROR! Invalid node ID\n";
					break;
				}

				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					switch (nodeWest->nodeID)
					{
					case grassID:
						nodeWestCost = grassCost;
						break;
					case dirtID:
						nodeWestCost = dirtCost;
						break;
					case waterID:
						nodeWestCost = waterCost;
						break;
					default:
						std::cout << "ERROR! Invalid node ID\n";
						break;
					}
					node->ConnectTo(nodeWest, nodeWestCost);
					nodeWest->ConnectTo(node, nodeCost);
				}

				Node* nodeEast = x == (m_width - 1) ? nullptr : GetNode(x + 1, y);
				if (nodeEast)
				{
					switch (nodeEast->nodeID)
					{
					case grassID:
						nodeEastCost = grassCost;
						break;
					case dirtID:
						nodeEastCost = dirtCost;
						break;
					case waterID:
						nodeEastCost = waterCost;
						break;
					default:
						std::cout << "ERROR! Invalid node ID\n";
						break;
					}
					node->ConnectTo(nodeEast, nodeEastCost);
					nodeEast->ConnectTo(node, nodeCost);
				}

				/*Node* nodeNorth = y == (m_height - 1) ? nullptr : GetNode(x, y + 1);
				if (nodeNorth)
				{
					switch (nodeNorth->nodeID)
					{
					case grassID:
						nodeNorthCost = grassCost;
						break;
					case dirtID:
						nodeNorthCost = dirtCost;
						break;
					case waterID:
						nodeNorthCost = waterCost;
						break;
					default:
						std::cout << "ERROR! Invalid node Id\n";
						break;
					}
					node->ConnectTo(nodeNorth, nodeNorthCost);
					nodeNorth->ConnectTo(node, nodeCost);
					if (nodeWest && nodeEast)
					{
						nodeWest->ConnectTo(nodeNorth, nodeNorthCost);
						nodeNorth->ConnectTo(nodeWest, nodeWestCost);

						nodeEast->ConnectTo(nodeNorth, nodeNorthCost);
						nodeNorth->ConnectTo(nodeEast, nodeEastCost);
					}
				}*/

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					switch (nodeSouth->nodeID)
					{
					case grassID:
						nodeSouthCost = grassCost;
						break;
					case dirtID:
						nodeSouthCost = dirtCost;
						break;
					case waterID:
						nodeSouthCost = waterCost;
						break;
					default:
						std::cout << "ERROR! Invalid node ID\n";
						break;
					}
					node->ConnectTo(nodeSouth, nodeSouthCost);
					nodeSouth->ConnectTo(node, nodeCost);
					if (nodeWest && nodeEast)
					{
						nodeWest->ConnectTo(nodeSouth, nodeSouthCost * 1.25f);
						nodeSouth->ConnectTo(nodeWest, nodeWestCost * 1.25f);

						nodeEast->ConnectTo(nodeSouth, nodeSouthCost * 1.25f);
						nodeSouth->ConnectTo(nodeEast, nodeEastCost * 1.25f);
					}
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
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize , (int)m_cellSize , DARKGRAY);
			}
			else
			{
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, {200,200,200,255});
				}
				switch (node->nodeID)
				{
				case 0:
					DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
						(int)m_cellSize, (int)m_cellSize , LIME);
					break;
				case 1:
					DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
						(int)m_cellSize , (int)m_cellSize , GREEN);
					break;
				case 3:
					DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
						(int)m_cellSize, (int)m_cellSize, DARKGREEN);
				default:
					break;
				}
				/*DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize, (int)m_cellSize, GRAY);*/
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
		std::cout << "Error! Either the start node or end node for Dijkstra's Search is NULL! Line 354 Pathfinding.cpp\n";
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

float AStarHeuristic(Node* current, Node* goal) {
	float val = std::abs(current->position.x - goal->position.x) + std::abs(current->position.y - goal->position.y);
	return val;
}

bool compareFScore(Node* n1, Node* n2, Node* goal) {
	bool val = (n1->gScore + AStarHeuristic(n1, goal)) < (n2->gScore + AStarHeuristic(n2, goal));
	//std::cout << val << "\tFScore check\n\n";
	return val;
}

std::vector<AIForGames::Node*> NodeMap::AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode)
{
	if (!startNode || !endNode) {
		std::cout << "Error! Either the start node or end node for AStar Search is NULL! Line 428 Pathfinding.cpp\n";
		return {};
	}
	if (startNode == endNode) return {};

	startNode->gScore = 0;
	startNode->previous = nullptr;

	std::vector<Node*> openList = { startNode };
	std::vector<Node*> closedList;

	while (!openList.empty()) {
		std::sort(openList.begin(), openList.end(), [&](Node* n1, Node* n2) {
			return compareFScore(n1, n2, endNode);
			});

		Node* currentNode = openList.front();
		if (currentNode == endNode) break;

		openList.erase(openList.begin());
		closedList.push_back(currentNode);

		for (auto& c : currentNode->connections) {
			Node* neighbour = c.target;
			if (std::find(closedList.begin(), closedList.end(), neighbour) != closedList.end()) {
				continue;
			}

			float gScore = currentNode->gScore + c.cost;
			if (gScore < neighbour->gScore) {
				neighbour->gScore = gScore;
				neighbour->previous = currentNode;

				if (std::find(openList.begin(), openList.end(), neighbour) == openList.end()) {
					openList.push_back(neighbour);
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

float NodeMap::EuclideanDistance(glm::vec2 pos1, glm::vec2 pos2)
{
	return glm::sqrt(glm::pow((pos1.x - pos2.x), 2) + glm::pow((pos1.y - pos2.y), 2));
}

PathAgent::~PathAgent()
{
	UnloadTexture(agentTexture); 
	m_path.clear();
}

void PathAgent::Update(/*float deltaTime*/)
{
	if (m_path.empty()) return;

	Node* nextNode = m_path.at(m_currentIndex + 1);

	if (m_position.x < nextNode->position.x) { m_position.x++; if (flipAgentTexture) flipAgentTexture = false; }
	
	if (m_position.x > nextNode->position.x) { m_position.x--; if (!flipAgentTexture) flipAgentTexture = true; }
	
	if (m_position.y < nextNode->position.y) { m_position.y++; }
	
	if (m_position.y > nextNode->position.y) { m_position.y--; }
	
	if (m_position == nextNode->position) {
		m_currentNode = nextNode;
		m_currentIndex++;
		if (m_currentNode == m_path.back())
		{
			m_position = m_path.back()->position;
			m_path.clear();
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
	if (!flipAgentTexture)
	{
		DrawTexturePro(agentTexture,
			Rectangle{ 0.0f, 0.0f, (float)agentTexture.width, (float)agentTexture.height },
			Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
			Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
			0.0f, WHITE);
	}
	else
	{
		DrawTexturePro(agentTexture,
			Rectangle{ 0.0f, 0.0f, -(float)agentTexture.width, (float)agentTexture.height },
			Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
			Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
			0.0f, WHITE);
	}
}
