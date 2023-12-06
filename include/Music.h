#pragma once
#include <SFML\Audio.hpp>
#include <array>
#include <random>

class GameMusic
{
	static const int _count_game_music = 9;
	std::array<sf::Music, _count_game_music> _game_musics;

public:
	GameMusic();
	~GameMusic() = default;
	void Music_play(int index);
	void Music_stop(int index);
	void Music_set_volume_all(int volume);
	void Music_pause(int index);
	void Music_return(int index);
	int Random_music(int min, int max);
	void Music_stop_all();
	void Music_pause_all();
	void Music_play_always(int index);
};