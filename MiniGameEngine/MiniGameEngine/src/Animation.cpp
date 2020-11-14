#include "Animation.h"
Animation::Animation() {

}
Animation::Animation(int index, int numFrames, int animationSpeed) {
	this->animationSpeed = animationSpeed;
	this->frames = numFrames;
	this->index = index;
}