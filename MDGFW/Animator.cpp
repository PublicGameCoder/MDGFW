#include <MDGFW\Animator.h>

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::Play() {
	this->_playing = true;
}

void Animator::Pause() {
	this->_paused = true;
}

void Animator::Resume() {
	this->_paused = false;
}

void Animator::Stop() {
	this->_playing = false;
}

bool Animator::isPlaying() {
	return this->_playing;
}

bool Animator::isPaused() {
	return this->_paused;
}