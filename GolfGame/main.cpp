#include "Game.h"
#include "Wind.h"
#include <iostream>

void printWind(Wind& wind)
{
	std::cout << "Wind magnitude: " << wind.GetMagnitude() << " m/s" << std::endl;
	std::cout << "Wind direction: " << wind.GetDirection().x << ", " << wind.GetDirection().y << ", " << wind.GetDirection().z << std::endl;
	std::cout << "Wind speed: " << wind.GetSpeed().x << ", " << wind.GetSpeed().y << ", " << wind.GetSpeed().z << std::endl
	<< std::endl;
}

void testWind()
{
	Wind wind;

	std::cout << "--- Wind tests ---" << std::endl << std::endl;
	std::cout << "NO_WIND:" << std::endl;
	wind.Initialize(WindSpeed::NO_WIND);
	printWind(wind);

	std::cout << "LIGHT_WIND:" << std::endl;
	wind.Initialize(WindSpeed::LIGHT_WIND);
	printWind(wind);

	std::cout << "MODERATE_WIND:" << std::endl;
	wind.Initialize(WindSpeed::MODERATE_WIND);
	printWind(wind);

	std::cout << "STRONG_WIND:" << std::endl;
	wind.Initialize(WindSpeed::STRONG_WIND);
	printWind(wind);

	std::cout << "VERY_STRONG_WIND:" << std::endl;
	wind.Initialize(WindSpeed::VERY_STRONG_WIND);
	printWind(wind);

	std::cout << "STORM_WIND:" << std::endl;
	wind.Initialize(WindSpeed::STORM_WIND);
	printWind(wind);

	std::cout << "HURRICANE_WIND:" << std::endl;
	wind.Initialize(WindSpeed::HURRICANE_WIND);
	printWind(wind);

	std::cout << "RANDOM_WIND:" << std::endl;
	wind.Initialize(WindSpeed::RANDOM_WIND);
	printWind(wind);
}

int main()
{
	//Game* game = new Game({1000, 0, 1000}, {0, 0, 0}, 1.0f, 50, 0.1f);

	//game->Run();
	//game->RepeatPlay();

	//delete game;

	testWind();

	return 0;
}