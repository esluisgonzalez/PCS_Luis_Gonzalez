#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
	static const int N = 5;
	double array[N] = {4.4, 6.7, 3.2, -7.1, 5.3};
	
	// Minimo
	double min = array[0];
	
	for (int i = 1; i < N; ++i)
	{
		min = std::min(min, array[i]);
	}
	
	// Massimo
	double max = array[0];
	
	for (int i = 1; i < N; ++i)
	{
		max = std::max(max, array[i]);
	}
	
	// Media
	double somma = 0.0;
	
	for (int i = 0; i < N; ++i)
	{
		somma += array[i];
	}
	
	double media = somma/N;
	
	// Deviazione standard
	double varianza = 0.0;
	
	for (int i = 0; i < N; ++i)
	{
		varianza += (array[i] - media)*(array[i] - media);
	}
	
	varianza /= N;
	
	double deviazione = std::sqrt(varianza);
	
	// Stampa risultati
	std::cout << "Il minimo è " << min << "\n";
	std::cout << "Il massimo è " << max << "\n";
	std::cout << "La media è " << media << "\n";
	std::cout << "La deviazione standard è " << deviazione << "\n";
	
	return 0;
}