#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string filename;
	
	std::cout << "Inserisci il nome del file: ";
	std::cin >> filename;
	
	std::ifstream ifs(filename);
	
	if (!ifs.is_open())
	{
		std::cerr << "ERRORE: Impossibile aprire il file " << filename << "\n";
		return 1;
	}
	
	std::string citta;
	double t0, t6, t12, t18;
	
	while (ifs >> citta >> t0 >> t6 >> t12 >> t18)
	{
		double media = (t0 + t6 + t12 + t18) / 4;
		std::cout << citta << " " << media << "\n";
	}
	
	return 0;
}
