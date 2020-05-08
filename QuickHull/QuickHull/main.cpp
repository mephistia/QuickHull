#include "Point.h"
#include <iostream>
#include <ctime>
#include <clocale>
#include <vector>
#include <algorithm>



// Função utilitária para gerar números aleatórios
float randBetween(int min, int max) {
	return min + rand() % (max + 1 - min);
}


// Função para verificar o lado
int ccw(Point p1, Point p2, Point p3){
	// ccw > 0: counter-clockwise; ccw < 0: clockwise; ccw = 0: collinear 
	return (p2.x - p1.x) * (p3.y - p1.y)
	     - (p2.y - p1.y) * (p3.x - p1.x);
}


// Função de distância entre ponto e linha
float dist(Point p1, Point p2, Point p3) {
	int a = p2.y - p1.y;
	int b = p2.x - p1.x;
	return std::abs((a * p3.x - b * p3.y + p2.x * p1.y - p2.y * p1.x)
		/ std::sqrt(a*a + b * b));
}


// Função recursiva do Quick Hull
void quickHull(std::vector<Point> points, std::vector<Point> &hull, Point p1, Point p2) {

	// se não houver mais pontos
	if (points.empty())
		return;

	int fartherId = 0;

	float distance = dist(p1, p2, points[0]);

	// econtrar o ponto mais distante
	for (int i = 0; i < points.size(); i++) {

		float newDist = dist(p1, p2, points[i]);

		if (newDist > distance) {
			distance = newDist;
			fartherId = i;
		}
	}

	// adicionar o ponto C no polígono
	hull.push_back(points[fartherId]);

	// novas divisões
	std::vector<Point> S1, S2;


	for (int i = 0; i < points.size(); i++) {

		// testa apenas pontos que não são o ponto C
		if (i != fartherId) {
			int side = ccw(p1, points[fartherId], points[i]);

			// no lado cw da linha AC, adiciona todos
			if (side <= 0) {
				S1.push_back(points[i]);
			}

			// no outro lado tem pontos dentro do "triângulo"
			else {
				// então muda a linha para CB
				side = ccw(points[fartherId], p2, points[i]);
				if (side <= 0) {
					S2.push_back(points[i]);
				}
			}
		}

	}

	// agora verifica os novos conjuntos de pontos
	// no S1, de A a C
	quickHull(S1, hull, p1, points[fartherId]);
	// no S2, de C a B
	quickHull(S2, hull, points[fartherId], p2);
}


int main() {

	// imprimir texto
	std::setlocale(LC_ALL, "pt_BR");
	srand((unsigned)time(0));

	// Pontos do exercício
	std::vector<Point> points = {
		Point(-13, 0.5),
		Point(-10.5, -11.5),
		Point(-10, 9),
		Point(-4.5, -2),
		Point(-1, 8.5),
		Point(0.5, 6),
		Point(0.5, -12),
		Point(2, 12.5),
		Point(3.5, 11),
		Point(5.5, 3),
		Point(5.5, -7),
		Point(5, 11.5),
		Point(6.5, 3.2),
		Point(7, -10),
		Point(9, -5),
		Point(11.5, -4)
	};


	// Criar vetor de pontos do polígono
	std::vector<Point> hull;

	// Ordenar os pontos por X
	std::sort(points.begin(), points.end(), [](Point p1, Point p2) {
		return p1.x < p2.x;
	});

	// Adiciona o primeiro e o último ponto no polígono
	hull.push_back(points[0]);
	hull.push_back(points.back());


	// Separar pontos por lado
	std::vector<Point> SA, SB;

	// apenas os pontos intermediários
	for (int i = 1; i < points.size() - 1; i++) {
		int side = ccw(points[0], points.back(), points[i]);

		if (side < 0) {
			SA.push_back(points[i]);
		}
		else {
			SB.push_back(points[i]);
		}
	}

	// Chamar a função recursiva para os dois lados (direção AB e BA)
	quickHull(SA, hull, points[0], points.back());
	quickHull(SB, hull, points.back(), points[0]);


	// Ordenar os pontos
	Point center = hull.front();

	for (Point &p : hull) {
		double angle = center.getAngleWith(p);
		p.angle = angle;
	}

	
	std::sort(hull.begin(), hull.end(), [](Point p1, Point p2) {
		return p1.angle < p2.angle; 
	});
	// problema: o ponto que deveria ser o final está no meio, "cortando" o polígono


	// Imprimir os pontos no polígono
	std::cout << "Pontos no polígono: " << std::endl << std::endl;
	for (int i = 0; i < hull.size(); i++) {
		std::cout << "(" << hull[i].x << ", " << hull[i].y << ")" << std::endl;
	}

	std::cout << std::endl << std::endl;

	// Com Random: 
	// Pontos aleatórios
	std::vector<Point> points2;
	std::cout << "Gerando pontos aleatórios..." << std::endl << std::endl;
	for (int i = 0; i < 16; i++) {
		float randX, randY;

		do {
			// criar aleatório (problema: só gera inteiros)
			randX = randBetween(-15, 15);
			randY = randBetween(-15, 15);

		// enquanto já existir no array
		} while (std::find(points2.begin(), points2.end(), Point(randX, randY)) != points2.end());

		// adicionar o ponto
		points2.push_back(Point(randX, randY));
		std::cout << "(" << points2[i].x << ", " << points2[i].y << ")" << std::endl;
	}

	// Criar vetor de pontos do polígono
	std::vector<Point> hull2;

	// Ordenar os pontos por X
	std::sort(points2.begin(), points2.end(), [](Point p1, Point p2) {
		return p1.x < p2.x;
	});

	// Adiciona o primeiro e o último ponto no polígono
	hull2.push_back(points2[0]);
	hull2.push_back(points2.back());


	// Separar pontos por lado
	std::vector<Point> SA2, SB2;

	// apenas os pontos intermediários
	for (int i = 1; i < points2.size() - 1; i++) {
		int side = ccw(points2[0], points2.back(), points2[i]);

		if (side < 0) {
			SA2.push_back(points2[i]);
		}
		else {
			SB2.push_back(points[i]);
		}
	}

	// Chamar a função recursiva para os dois lados (direção AB e BA)
	quickHull(SA2, hull2, points2[0], points2.back());
	quickHull(SB2, hull2, points2.back(), points2[0]);


	// Ordenar os pontos
	Point center2 = hull2.front();

	for (Point &p : hull2) {
		double angle = center2.getAngleWith(p);
		p.angle = angle;
	}


	std::sort(hull2.begin(), hull2.end(), [](Point p1, Point p2) {
		return p1.angle < p2.angle;
	});
	// problema: o ponto que deveria ser o final está no meio, "cortando" o polígono


	// Imprimir os pontos no polígono
	std::cout << "Pontos no polígono: " << std::endl << std::endl;
	for (int i = 0; i < hull2.size(); i++) {
		std::cout << "(" << hull2[i].x << ", " << hull2[i].y << ")" << std::endl;
	}


	std::cin.get();

	return 0;
}