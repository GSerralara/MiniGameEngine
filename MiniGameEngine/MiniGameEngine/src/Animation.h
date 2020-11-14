#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
	public:
		unsigned int index;
		unsigned int frames;
		unsigned int animationSpeed;
		Animation();
		Animation(int index, int frames, int animationSpeed);
};

#endif
