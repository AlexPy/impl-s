// Boruvka's algorithm to find Minimum Spanning
// Tree of a given connected, undirected and
// weighted graph

#include"generator.h"


// Граф - структура с количеством вершин и ребер и указателем на список ребер графа
struct Graph
{
	// V - количество вершин, E - количество ребер
	int V, E;

	// Указатель на список ребер графа
	Edge* edge;
};

// Компонента связности
struct subset
{
	int parent;
	int rank;
};

// Прототипы
int find(subset subsets[], int i);
void Union(subset subsets[], int x, int y, set<int> *roots);

// ALGO
void boruvkaMST(Graph* graph, std::set<int> *roots)
{
	//subset - компонента связности
	//INITIALIZATION

	// В графе V вершин и E ребер.
	int V = graph->V, E = graph->E;
	//указатель на массив ребер графа.
	Edge *edge = graph->edge;

	//Выделение памяти под компоненты связности
	subset *subsets = new subset[V];

	// Массив, хрянящий индекс(номер) минимального ребра из вершины. Номер вершины равен индексу в массиве.
	// Этот массив хранит индекс для индексирования массива edge[]
	int *cheapest = new int[V];

	// Создадим V компонент связности с 1 элементом в каждой
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	    cheapest[v] = std::numeric_limits<int>::max();
		//initialize roots
		roots->insert(v);
	}

	//IMPLEMENTATION

	// Изначально имеем V деревьев(компонент), вес MST равен 0
	int numTrees = V;
	int MSTweight = 0;

	// Будем соединять компоненты, пока не останется одна
	while (numTrees > 1)
	{

		// Идем по всем ребрам и обновляем самые дешевые ребра у каждой компоненты
		for (int i = 0; i<E; i++)
		{
			if (edge[i].inserted)
			{
				continue;
			}
			//находит ИНДЕКС корня
			int set1 = find(subsets, edge[i].src);
			int set2 = find(subsets, edge[i].dest);

			// Если корень один и тот же, значит это одна компонента - continue;
			// следующая итерация и берем две следующие вершины
			if (set1 == set2)
			{
				edge[i].inserted = true;
				continue;
			}

			// Иначе присваиваем вершинам другие номера компонент связности
			else
			{
				//здесь ищем минимальное ребро из рассматирваемой компоненты
				// если минимальное ребро для этой компоненты == -1 или вес мин. ребра больше, чем вес текущего
				// рассматриваемого, тогда меняем индекс минимального ребра на i, так как цикл идет по всем ребрам

				if (edge[cheapest[set1]].weight > edge[i].weight)/* TODO ДОПИСАТЬ УСЛОВИЕ, ЧТО ЭТО РЕБРО ЕЩЁ НЕ ПРИНАДЛЕЖИТ MST || (std::find(MST->begin(), MST->end(), edge[i]) != MST->end())*/
					cheapest[set1] = i;
				// аналогично для второй компоненты 
				if (edge[cheapest[set2]].weight > edge[i].weight)
					cheapest[set2] = i;
			}
		}
		
		//OLD IMPLEMENTATION
		/*
		for (int i = 0; i<V; i++)
		{
			// Check if cheapest for current set exists
			if (cheapest[i] != std::numeric_limits<int>::max())
			{
				
				// cheapest[i] : i - номер вершины. cheapest[i] хранит в себе номер минимального ребра в массиве edge.
				// например : i == 0; cheapest[i] == 2 - это значит, что для нулевой(первой для понимания) вершины
				// минимальным является второе ребро из списка всех ребер.

				// функция find находит номер вершины родителя рассматриваемой компоненты связности
				// вернее, индекс этой вершины в массиве subsets
				// в данном случае, находится присвоенный ранее номер компоненты связности
				int set1 = find(subsets, edge[cheapest[i]].src);
				int set2 = find(subsets, edge[cheapest[i]].dest);

				if (set1 == set2)
				{				
					continue;
				}
				MSTweight += edge[cheapest[i]].weight;

				//edge[cheapest[i]].included_in_mst = true;

				//MST->push_back(edge[i]);
				printf("Edge %d-%d included in MST\n",
					edge[cheapest[i]].src, edge[cheapest[i]].dest,
					edge[cheapest[i]].weight);
				

				// Do a union of set1 and set2 and decrease number
				// of trees
				edge[cheapest[i]].weight = std::numeric_limits<int>::max();
				Union(subsets, set1, set2, roots);
				numTrees--;
			}
		}*/
		
		//A NEW ONE
		std::set<int>::iterator it;
		//std::set<int>::iterator itt;
		//for (it = (*roots).begin(); it != (*roots).end(); it++)
		//{
			//cout << "root" << *it << endl;
		//}		
		for (it = (*roots).begin(); it != (*roots).end(); it++)
		{
			//for (itt = (*roots).begin(); itt != (*roots).end(); itt++)
			//{
			//	cout << "root" << *itt << endl;
			//}
			
			if (cheapest[*it] != std::numeric_limits<int>::max())
			{

				// cheapest[i] : i - номер вершины. cheapest[i] хранит в себе номер минимального ребра в массиве edge.
				// например : i == 0; cheapest[i] == 2 - это значит, что для нулевой(первой для понимания) вершины
				// минимальным является второе ребро из списка всех ребер.

				// функция find находит номер вершины родителя рассматриваемой компоненты связности
				// вернее, индекс этой вершины в массиве subsets
				// в данном случае, находится присвоенный ранее номер компоненты связности
				//int set1 = find(subsets, edge[cheapest[i]].src);
				//int set2 = find(subsets, edge[cheapest[i]].dest);

				if (distance(++it, (*roots).end()) >= 0 &&  cheapest[*it] == cheapest[*(++it)])
				{
					continue;
				}
				MSTweight += edge[cheapest[*it]].weight;

				//edge[cheapest[i]].included_in_mst = true;

				//MST->push_back(edge[i]);
				printf("Edge %d-%d included in MST\n",
					edge[cheapest[*it]].src, edge[cheapest[*it]].dest,
					edge[cheapest[*it]].weight);


				// Do a union of set1 and set2 and decrease number
				// of trees
				edge[cheapest[*it]].weight = std::numeric_limits<int>::max();
				Union(subsets, cheapest[*it], cheapest[*(--it)], roots);
				numTrees--;
			}
		}
		
	printf("Weight of MST is %d\n", MSTweight);
	return;
}

// Cоздаем граф
struct Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = generateGraph(int V);
	return graph;
}

// Функция ищет корень компоненты и возвращает номер корня
int find(subset subsets[], int i)
{
	// Найти корень и вернуть его(родителя этой вершины)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

// Соединяет две компоненты связности по ранку
// вернее, присваивает одной компоненте связности номер другой, если та более старше "ранком" и наоборот
void Union(subset subsets[], int x, int y, set<int> * roots)
{
	//int xroot = find(subsets, x);
	//int yroot = find(subsets, y);
	int xroot = x;
	int yroot = y;
	// Соединение по ранку
	if (subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;
		roots->erase(xroot);
	}
	else if (subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
		roots->erase(yroot);
	}
	
	// Если ранк одинаков - берем любую, увеличиваем ее ранк, и присваиваем другой компоненте номер этой компоненты
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
		roots->erase(xroot);
	}
}
 

//MAIN
int main()
{
	int V;
	cin >> V;
	int E = V*20;
	struct Graph* graph = createGraph(V, E);
	std::vector<Edge> * MST = new std::vector<Edge>();
	set<int> *roots = new set<int>();
	
	//засекаем время
	double time1 = omp_get_wtime();
	boruvkaMST(graph, roots);
	double duration = (omp_get_wtime() - time1);
	
	cout << "Time cost: " << duration << '\n';
/*
	omp_set_num_threads(5);
#pragma omp parallel
	{
		cout << "Hello" << endl;
	} */
	return 0;
}