
#include "pokemons.h"

bool Pokemons::reload()
{
	loaded = false;
	scriptInterface.reset();
	return loadPokemons(true);
}

bool Pokemons::loadPokemons(bool reloading /*= false*/)
{
	PokemonType* pType = nullptr;
	bool new_pType = true;
	std::string file = "data/pokes.xml";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());

	if (!result) {
		printXMLError("Error - Pokemons::loadPokemons", file, result);
		return false;
	}

	loaded = true;

	for (auto pokemonNode : doc.child("pokes").children()) {

		std::string name = std::string(pokemonNode.attribute("name").as_string());
		std::string level = std::string(pokemonNode.attribute("level").as_string());
		std::string type = std::string(pokemonNode.attribute("type").as_string());

		if (reloading) {
			pType = getPokemonType(asLowerCaseString(name));
			if (pType != nullptr) {
				new_pType = false;
			}
		}

		if (new_pType) {
			pType = &pokemons[asLowerCaseString(name)];
	    }

		pType->name = name;
		pType->level = level;
		pType->type = type;
	}
	return true;
}

PokemonType* Pokemons::getPokemonType(const std::string& name)
{
	auto it = pokemons.find(asLowerCaseString(name));

	if (it == pokemons.end()) {
		return nullptr;
	}
	return &it->second;
}