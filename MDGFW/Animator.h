#ifndef ANIMATOR_H
#define ANIMATOR_H

class Animator
{
public:
	Animator();
	~Animator();

	void Play();
	void Pause();
	void Resume();
	void Stop();

	bool isPlaying();
	bool isPaused();
private:
	bool _playing;
	bool _paused;
};

#endif // !ANIMATOR_H
