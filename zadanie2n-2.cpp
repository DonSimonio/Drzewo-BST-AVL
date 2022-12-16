/*
	Projekt prezentuje znajomość struktury drzewa poszukiwań binarnych (ang. Binary Search Tree - BST)
	Uwzględnia takie funkcjonalności jak:
		- tworzenie oraz usuwanie drzewa
		- wyszukiwanie elementu w drzewie
		- usuwanie elementu z drzewa
		- przeglądanie drzewa w 3 porządkach (poprzecznie, wstecznie, wzdłużnie)
		- generacje drzewa AVL-wyważonego za pomocą połowienia binarnego

	Doświadczenie ma na celu zobrazować czas tworzenia, usuwania, wyszukiwania w BST oraz sprawdzić wysokość drzewa AVL względem niewyważonego drzewa BST (dla losowych danych).
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std::chrono;
using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
	Node* parent;
};

/**********************************/
//zmienne globalne
Node* root = nullptr;
vector <int> imp;	//tablica z importowanymi danymi
vector <int> tablica;
vector <int> tablicaAVL;
int x = 0;

/**********************************/
//zadanie I
void add(int x);	//dodaje element do drzewa
void inorder(Node* root);	//wyswietla sortujac poprzecznie LKP
void postorder(Node* root);	//wyswietla sortujac wstecznie LPK
void preorder(Node* root);	//wyswietla sortujac wzdluznie KLP
void del_postorder(Node* v);	//usuwa drzewo wstecznie
void del_postorder2(Node* v);	//usuwa element wstecznie
void search(Node* root, int k);	//poszukiwania binarne
//zadanie II
int HeightTree(Node* v);	//wysokosc drzewa
void inorder_pushback(Node* root);	//dodaje do tablicy wezły drzewa w kolejnosci inorder
void polowienie(vector <int> tab, int start,int koniec);	//polowienie binarne dla tablicy

void czytaj();	// wczytuje dane z pliku do programu

int main()
{
	fstream wyjscie, wyjscie2;
	czytaj();

	//zadanie 1.2
	/*
	wyjscie2.open("output-2.txt");
	auto s = high_resolution_clock::now();
	for (int i = 0; i < 200000; i++)
	{
		add(imp[i]);
		if ((i + 1) % 10000 == 0)
		{
			auto st = high_resolution_clock::now();
			auto czas = duration_cast<milliseconds>(st - s);
			wyjscie2 << "Tworzenie-BST-" << i + 1 << "-"<< czas.count() << endl;
		}
	}
	s = high_resolution_clock::now();
	for (int i = 0; i < 200000; i++)
	{
		search(root,imp[i]);
		if ((i + 1) % 10000 == 0)
		{
			auto st = high_resolution_clock::now();
			auto czas = duration_cast<milliseconds>(st - s);
			wyjscie2 << "Wyszukiwanie-BST-" << i + 1 << "-" << czas.count() << endl;
		}
	}
	s = high_resolution_clock::now();
	for (int i = 0; i < 200000; i++)
	{
		del_postorder2(root);
		if ((i + 1) % 10000 == 0)
		{
			auto st = high_resolution_clock::now();
			auto czas = duration_cast<milliseconds>(st - s);
			wyjscie2 << "Usuwanie-BST-" << i + 1 << "-" << czas.count() << endl;
		}
	}
	
	wyjscie2.close();
	*/



	// zadanie 2
	/*
	wyjscie.open("output.txt");
	for (int k = 20000; k <= imp.size(); k += 20000)
	{
		for (int i = 0; i < k; i++) {

			add(imp[i]);
		}
		cout << "Wysokosc - "<<k<<" : " << HeightTree(root) << endl;
		wyjscie << "Wysokosc-default-" << k << "-" << HeightTree(root) << endl;
		inorder_pushback(root);	//dodaje do zmiennej - 'tablica' posortowane elementy drzewa
		polowienie(tablica, 0, tablica.size() - 1);
		del_postorder(root);
		for (int i = 0; i < tablicaAVL.size(); i++)
		{
			add(tablicaAVL[i]);
		}
		cout << "Wysokosc - AVL - " << k << " : " << HeightTree(root) << endl;
		wyjscie << "Wysokosc-AVL-" << k << "-" << HeightTree(root) << endl;
		del_postorder(root);
		tablica.clear();
		tablicaAVL.clear();
	}
	wyjscie.close();
	*/
	
}



void add(int x)
{
	Node* now = root;
	Node* AddedNode = new Node;
	AddedNode->info = x;//przypisanie wartosci do nowego wezla
	AddedNode->left = nullptr;
	AddedNode->right = nullptr;
	if (!root) {
		AddedNode->parent = nullptr;
		root = AddedNode;
		return;

	}
	while (now != nullptr)
	{
		if (AddedNode->info >= now->info)
		{
			if (now->right == nullptr)
			{
				AddedNode->parent = now;
				now->right = AddedNode;
				return;
			}
			else
			{
				now = now->right;
			}
		}
		if (AddedNode->info < now->info)
		{
			if (now->left == nullptr)
			{
				AddedNode->parent = now;
				now->left = AddedNode;
				return;
			}
			else
			{
				now = now->left;
			}
		}
	}

}

void inorder(Node* root) {		//LKP
	if (root != nullptr) {
		inorder(root->left);
		cout << root->info;
		inorder(root->right);
	}
	return;
}
void postorder(Node* root) {	//LPK
	if (root != nullptr) {
		postorder(root->left);
		postorder(root->right);
		cout << root->info;
	}
	return;
}
void preorder(Node* root) {		//KLP
	if (root != nullptr) {
		cout << root->info;
		preorder(root->left);
		preorder(root->right);
	}
	return;
}

void del_postorder(Node* v)	//usuwa wstecz
{
	if (v)
	{
		del_postorder(v->left);
		del_postorder(v->right);
		delete v;
	}
	root = nullptr;
}

void inorder_pushback(Node* root)
{
	if (root != nullptr) {
		inorder_pushback(root->left);
		tablica.push_back(root->info);
		inorder_pushback(root->right);
	}
	return;
}

void polowienie(vector <int> tab, int start, int koniec)
{
	int srodek;
	if ((koniec + start) % 2 == 1) {
		srodek = ((koniec + start) / 2) + 1;
	}
	else {
		srodek = (koniec + start) / 2;
	}

	if (koniec == start) {
		tablicaAVL.push_back(tab[koniec]);
		return;
	}
	else if (koniec - start == 1 && x > tab[koniec]) {
		tablicaAVL.push_back(tab[koniec]);
		tablicaAVL.push_back(tab[start]);
		return;
	}
	else if (koniec - start == 1 && x < tab[koniec]) {
		tablicaAVL.push_back(tab[start]);
		tablicaAVL.push_back(tab[koniec]);
		return;
	}
	else
	{
		tablicaAVL.push_back(tab[srodek]);
		x = tab[srodek];
		polowienie(tab, start, srodek - 1);
		polowienie(tab, srodek + 1, koniec);
	}

}

int HeightTree(Node* v)
{
	int hleft, hright;
	if (v != NULL)
	{
		hleft = HeightTree(v->left);
		hright = HeightTree(v->right);
		return(1 + (hleft > hright ? hleft : hright));
	}
	else
		return(0);
}

void czytaj()
{
	fstream plik;
	plik.open("tablica.txt");
	if (plik.good() == false)
	{
		cout << "Blad!!!";
		return;
	}

	string x;
	int k;
	while (getline(plik, x, ','))
	{
		k = stoi(x);
		imp.push_back(k);
	}

	plik.close();
	return;
}

void search(Node* root, int k)
{
	if (root == NULL || root->info == k)
		return;

	if (root->info < k)
		return search(root->right, k);

	return search(root->left, k);

}

void del_postorder2(Node* v)
{
	if (v)
	{
		del_postorder(v->left);
		del_postorder(v->right);
		delete v;
	}
	root = nullptr;
	return;
}