#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define PATH_TO_DATA "../data/messages.html"
#define PATH_TO_WHITE "../data/white.txt"
#define PATH_TO_BLACK "../data/black.txt"

int main() 
{
	enum class Found { white, black, not_found };

	std::ifstream cards_file;
	std::ofstream white_cards;
	std::ofstream black_cards;

	std::string line;
	
	// No queremos modificar el 'case' de la cadena original, por lo que especificamos 
	// todos los casos en las keywords.
	std::vector<std::string> white_keywords = {"Blanca: ", "blanca: "};
	std::vector<std::string> black_keywords = {"Negra: ", "negra: "};

	cards_file.open(PATH_TO_DATA);  
	white_cards.open(PATH_TO_WHITE);
	black_cards.open(PATH_TO_BLACK);

	if(cards_file.is_open())
	{
		while(!cards_file.eof())
		{
			// Por defecto, en la frase no hay keyword.
			Found found = Found::not_found;

			std::getline(cards_file, line);
			
			// Comprobamos si es carta negra
			for(auto it = black_keywords.begin(); it != black_keywords.end(); ++it)
			{
				if(size_t pos = (line.find(*it)) != std::string::npos)
				{
					found = Found::black;

					// Eliminamos el keyword de la frase.
					line.replace(0, it->length(), "");
				}
			}

			// Comprobamos si es carta blanca
			for(auto it = white_keywords.begin(); it != white_keywords.end(); ++it)
			{
				if(size_t pos = (line.find(*it)) != std::string::npos)
				{
					found = Found::white;
					
					// Eliminamos el keyword de la frase.
					line.replace(0, it->length(), "");
				}
			}

			if (found == Found::black)
			{
				std::string old_value = "&lt;blank&gt;";
				std::size_t replace_pos = line.find(old_value);

				// reemplazamos todos los blanks
				while (replace_pos != std::string::npos)
				{
					std::string new_value = "<blank>";	// Cambiar a la cadena que se quiere mostrar como blank.

					// Sustituimos blank por la cadena especificada.
					line.replace(line.find(old_value), old_value.length(), new_value);
					replace_pos = line.find(old_value);
				}

				black_cards << line << '\n';
			}
			else if(found == Found::white)
			{
				white_cards << line << '\n';
			}
		}

		cards_file.close();
		white_cards.close();
		black_cards.close();

		std::cout << "El archivo se ha terminado de procesar." << '\n';
	}
	else
	{
		std::cout << "Error al abrir el archivo con los mensajes." << '\n';
	}

	return 0;
}