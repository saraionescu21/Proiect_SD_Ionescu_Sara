#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

void afisare(int v[], int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << endl;
}

void functie_merge(int v[], int low, int high)
{
	int mid = low + (high - low) / 2;

	int i = low;
	int j = mid + 1;

	int temp[100000];
	int temp_index = 0;

	while (i <= mid && j <= high)
	{
		if (v[i] < v[j])
		{
			temp[temp_index] = v[i];
			temp_index++;
			i++;
		}
		else
		{
			temp[temp_index] = v[j];
			temp_index++;
			j++;
		}
	}
	while (i <= mid)
	{
		temp[temp_index] = v[i];
		temp_index++;
		i++;
	}

	while (j <= high)
	{
		temp[temp_index] = v[j];
		temp_index++;
		j++;
	}

	for (int i = low; i <= high; i++)
	{
		v[i] = temp[i - low];
	}
}

void mergesort(int v[], int low, int high)
{
	if (low < high)
	{
		int mid = low + (high - low) / 2;
		mergesort(v, low, mid);
		mergesort(v, mid + 1, high);
		functie_merge(v, low, high);
	}
}

void shellsort(int v[], int n)
{
	int h = n / 2;
	int temp, j;
	while (h >= 1)
	{
		for (int i = h; i < n; i++) {
			temp = v[i];
			j = i;
			while (j >= h && v[j - h] > temp)
			{
				v[j] = v[j - h];
				j -= h;
			}
			v[j] = temp;
		}
		h /= 2;
	}
}

void countingsortradix(int v[], int n, int putere) {
	int copie[100000];
	int frcif[10] = { 0 };

	for (int i = 0; i < n; i++) {
		int cifra = (v[i] / putere) % 10;
		frcif[cifra]++;
	}

	for (int i = 1; i < 10; i++) {
		frcif[i] += frcif[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		int cifra = (v[i] / putere) % 10;
		copie[frcif[cifra] - 1] = v[i];
		frcif[cifra]--;
	}

	for (int i = 0; i < n; i++) {
		v[i] = copie[i];
	}
}

void radixsort(int v[], int n) {

	int maxi = v[0];
	for (int i = 1; i < n; i++) {
		if (v[i] > maxi) {
			maxi = v[i];
		}
	}


	for (int putere = 1; maxi / putere > 0; putere *= 10) {
		countingsortradix(v, n, putere);
	}
}

void insertionsort(int v[], int n)
{
	int i, j, aux;
	for (i = 1; i < n; i++)
	{
		aux = v[i];
		j = i - 1;

		while (j >= 0 && v[j] > aux)
		{
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = aux;
	}
}

void countingsort(int v[], int n)
{
	int copie[100000];
	int fr[100000] = { 0 };
	int maxi = v[0];

	for (int i = 1; i < n; i++)
	{
		if (v[i] > maxi)
			maxi = v[i];
	}

	for (int i = 0; i < n; i++) {
		fr[v[i]]++;
	}

	for (int i = 1; i <= maxi; i++)
	{
		fr[i] += fr[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		copie[fr[v[i]] - 1] = v[i];
		fr[v[i]]--;
	}

	for (int i = 0; i < n; i++)
	{
		v[i] = copie[i];
	}
}

int main()
{
	int n;
	int v[10000];
	cin >> n;
	srand(time(NULL));

	for (int i = 0; i < n; i++)
		v[i] = rand() % 1000000;

	// Sortam vectorul cu mergesort
	cout << "Vectorul initial:" << endl;
	afisare(v, n);

	auto start_merge = chrono::high_resolution_clock::now();

	int copie_vector[100000]; 
	for (int i = 0; i < n; i++)
		copie_vector[i] = v[i];

	mergesort(copie_vector, 0, n - 1);

	auto end_merge = chrono::high_resolution_clock::now();
	chrono::duration<double> duration_merge = end_merge - start_merge;

	cout << "Vectorul sortat folosind mergesort:" << endl;
	afisare(copie_vector, n);

	cout << "Timpul de executie al functiei mergesort(): " << duration_merge.count() << " secunde." << endl << endl;

	// Sortam vectorul cu shellsort
	cout << "Vectorul initial:" << endl;
	afisare(v, n);

	auto start_shell = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++)
		copie_vector[i] = v[i];

	shellsort(copie_vector, n);

	auto end_shell = chrono::high_resolution_clock::now();
	chrono::duration<double> duration_shell = end_shell - start_shell;

	cout << "Vectorul sortat folosind shellsort:" << endl;
	afisare(copie_vector, n);

	cout << "Timpul de executie al functiei shellsort(): " << duration_shell.count() << " secunde." << endl << endl;

	// Sortam vectorul cu radixsort
	cout << "Vectorul initial:" << endl;
	afisare(v, n);

	auto start_radix = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++)
		copie_vector[i] = v[i];

	radixsort(copie_vector, n);

	auto end_radix = chrono::high_resolution_clock::now();
	chrono::duration<double> duration_radix = end_radix - start_radix;

	cout << "Vectorul sortat folosind radixsort:" << endl;
	afisare(copie_vector, n);

	cout << "Timpul de executie al functiei radixsort(): " << duration_radix.count() << " secunde." << endl << endl;

	// Sortam vectorul cu insertionsort
	cout << "Vectorul initial:" << endl;
	afisare(v, n);

	auto start_insertion = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++)
		copie_vector[i] = v[i];

	insertionsort(copie_vector, n);

	auto end_insertion = chrono::high_resolution_clock::now();
	chrono::duration<double> duration_insertion = end_insertion - start_insertion;

	cout << "Vectorul sortat folosind insertionsort:" << endl;
	afisare(copie_vector, n);

	cout << "Timpul de executie al functiei insertionsort(): " << duration_insertion.count() << " secunde." << endl << endl;

	// Sortam vectorul cu countingsort
	cout << "Vectorul initial:" << endl;
	afisare(v, n);

	auto start_counting = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++)
		copie_vector[i] = v[i];

	countingsort(copie_vector, n);

	auto end_counting = chrono::high_resolution_clock::now();
	chrono::duration<double> duration_counting = end_counting - start_counting;

	cout << "Vectorul sortat folosind countingsort:" << endl;
	afisare(copie_vector, n);

	cout << "Timpul de executie al functiei countingsort(): " << duration_counting.count() << " secunde." << endl;

	return 0;

}

