#include "creature.h"

class PokemonType
{
	public:
		PokemonType() = default;

		// non-copyable
		PokemonType(const PokemonType&) = delete;
		PokemonType& operator=(const PokemonType&) = delete;

		std::string name;
		std::string level;
		std::string type;
};

class Pokemons
{
	public:
		Pokemons() = default;

		// non-copyable
		Pokemons(const Pokemons&) = delete;
		Pokemons& operator=(const Pokemons&) = delete;
        
		bool loadPokemons(bool reloading = false);
		bool isLoaded() const {
			return loaded;
		}

		bool reload();
		PokemonType* getPokemonType(const std::string& name);

	private:
		std::map<std::string, PokemonType> pokemons;
		std::unique_ptr<LuaScriptInterface> scriptInterface;

		bool loaded = false;
};
