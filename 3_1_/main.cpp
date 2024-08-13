/*//==============================================================================================================
Дан базовый интерфейс для представления ориентированного графа:
struct IGraph {
virtual ~IGraph() {}

	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать
 переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/ //==============================================================================================================
#include <iostream>
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void PrintGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        const auto nextVertices = graph.GetNextVertices(i);
        std::cout << "Vertex " << i << ":";
        for (int v: nextVertices) {
            std::cout << " " << v;
        }
        std::cout << std::endl;
    }
}

int main() {
    ListGraph initialGraph(5);
    initialGraph.AddEdge(0, 1);
    initialGraph.AddEdge(0, 2);
    initialGraph.AddEdge(1, 3);
    initialGraph.AddEdge(3, 4);
    initialGraph.AddEdge(4, 2);

    std::cout << "Initial ListGraph:" << std::endl;
    PrintGraph(initialGraph);

    MatrixGraph matrixGraph(initialGraph);
    SetGraph setGraph(initialGraph);
    ArcGraph arcGraph(initialGraph);

    std::cout << "\nMatrixGraph:" << std::endl;
    PrintGraph(matrixGraph);

    std::cout << "\nSetGraph:" << std::endl;
    PrintGraph(setGraph);

    std::cout << "\nArcGraph:" << std::endl;
    PrintGraph(arcGraph);

    return 0;
}
